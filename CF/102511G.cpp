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

const int MAXN = 3e6 + 5;

struct SAM{
    int ch[MAXN][26],tot=1,fail[MAXN],len[MAXN];LL sm[MAXN];
    std::vector<int> G[MAXN];

    inline void copy(int x,int y){
        FOR(i,0,25) ch[x][i] = ch[y][i];fail[x] = fail[y];len[x] = len[y];
    }

    inline int work(int p,int c){
        int q = ch[p][c],nq = ++tot;copy(nq,q);len[nq] = len[p]+1;fail[q] = nq;
        for(;p&&ch[p][c]==q;p=fail[p]) ch[p][c] = nq;return nq;
    }

    inline int insert(int p,int c){
        int q = ch[p][c];
        if(q){
            if(len[q] == len[p]+1) return q;
            return work(p,c);
        }
        int np = ++tot;len[np] = len[p]+1;
        for(;p&&!ch[p][c];p=fail[p]) ch[p][c] = np;
        if(!p) fail[np] = 1;
        else{
            q = ch[p][c];
            if(len[q]==len[p]+1) fail[np] = q;
            else fail[np] = work(p,c);
        }
        return np;
    }

    inline void dfs(int v){
        for(auto x:G[v]) dfs(x),sm[v] += sm[x];
    }

    inline void build(){
        FOR(i,1,tot) G[fail[i]].pb(i);
        dfs(1);
    }
}sam;

std::vector<P> G[MAXN];
int n,m;

inline void dfs(int v,int fa=0,int now=1){
    for(auto x:G[v]){
        if(x.fi == fa) continue;
        int t = sam.insert(now,x.se);sam.sm[t]++;
        dfs(x.fi,v,t);
    }
}
char str[MAXN];
int main(){
    scanf("%d%d",&n,&m);
    int rt=0;
    FOR(i,1,n){
        int p;scanf("%s%d",str,&p);
        if(i == 1) rt = sam.insert(1,str[0]-'A');
        else G[p].pb(MP(i,str[0]-'A'));
    }
    ++sam.sm[rt];dfs(1,0,rt);
    sam.build();
//    FOR(i,1,sam.tot) DEBUG(sam.sm[i]);
    while(m--){
        scanf("%s",str+1);int len = strlen(str+1);
        int v = 1;
        ROF(i,len,1){
            v = sam.ch[v][str[i]-'A'];
            if(!v) break;
        }
        printf("%lld\n",sam.sm[v]);
    }
    return 0;
}
