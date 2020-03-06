#include<bits/stdc++.h>

#define fi first
#define se second
#define U unsigned
#define P std::pair<int,int>
#define LL long long
#define pb push_back
#define MP std::make_pair
#define all(x) x.begin(),x.end()
#define CLR(i,a) memset(i,a,sizeof(i))
#define FOR(i,a,b) for(int i = a;i <= b;++i)
#define ROF(i,a,b) for(int i = a;i >= b;--i)
#define DEBUG(x) std::cerr << #x << '=' << x << std::endl

const int MAXN = 3e5 + 5;

struct SAM{
    int ch[MAXN][26],len[MAXN],fail[MAXN],las = 1,tot = 1;
    inline int insert(int c){
        int p = las,np = las = ++tot;len[np] = len[p]+1;
        for(;p&&!ch[p][c];p=fail[p])ch[p][c]=np;
        if(!p) fail[np] = 1;
        else{
            int q = ch[p][c];
            if(len[q]==len[p]+1)fail[np]=q;
            else{
                int nq=++tot;FOR(i,0,25)ch[nq][i]=ch[q][i];len[nq]=len[p]+1;fail[nq]=fail[q];fail[q]=fail[np]=nq;
                for(;p&&ch[p][c]==q;p=fail[p])ch[p][c]=nq;
            }
        }
        return np;
    }

    bool vis[MAXN];
    int sg[MAXN];

    inline void clr(){
        FOR(i,1,tot){
            vis[i] = 0;sg[i] = len[i] = 0;
            FOR(j,0,25) ch[i][j] = 0;
        }
        tot = las = 1;
    }

    inline void dfs(int v){
        vis[v] = 1;
        FOR(i,0,25){
            if(ch[v][i] && !vis[ch[v][i]]) dfs(ch[v][i]);
        }
        std::set<int> S;
        FOR(i,0,25){
            if(ch[v][i]){
                S.insert(sg[ch[v][i]]);
 //               printf("%d %d\n",v,ch[v][i]);
            }
        }
        FOR(i,0,2333){
            if(!S.count(i)){
                sg[v] = i;break;
            }
        }
    }
}sam;

int n;char str[MAXN];

int main(){
    while(~scanf("%s",str+1)){
        int n = strlen(str+1);sam.clr();
        FOR(i,1,n) sam.insert(str[i]-'a');
        int T;scanf("%d",&T);int ans = 0;sam.dfs(1);
        while(T--){
            scanf("%s",str+1);n = strlen(str+1);
            int v = 1;FOR(i,1,n) v = sam.ch[v][str[i]-'a'];
//            DEBUG(v);
            ans ^= sam.sg[v];
        }
        puts(ans?"Alice":"Bob");
    }
    return 0;
}
