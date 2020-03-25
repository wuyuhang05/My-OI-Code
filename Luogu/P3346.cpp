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

const int MAXN = 20*500000+5;
std::vector<int> G[MAXN];
int n,c,col[MAXN];

struct SAM{
    int fail[MAXN],len[MAXN],tot=1,rt=1;
    int ch[MAXN][10];

    inline void copy(int x,int y){
        FOR(i,0,9) ch[x][i] = ch[y][i];len[x] = len[y];fail[x] = fail[y];
    }

    inline int work(int p,int c){
        int q = ch[p][c],nq = ++tot;
        copy(nq,q);len[nq] = len[p]+1;fail[q] = nq;
        for(;p&&ch[p][c]==q;p=fail[p]) ch[p][c] = nq;
        return nq;
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
           if(len[q] == len[p]+1) fail[np] = q;
           else fail[np] = work(p,c);
       }
       return np;
    }
}sam;
bool vis[MAXN];
inline void dfs(int v,int fa,int lst){
    int now = sam.insert(lst,col[v]);vis[v] = 1;
    for(auto x:G[v]){
        if(x == fa) continue;
        dfs(x,v,now);
    }
}

int main(){
    scanf("%d%*d",&n);
    FOR(i,1,n) scanf("%d",col+i);
    FOR(i,2,n){
        int u,v;scanf("%d%d",&u,&v);
        G[u].pb(v);G[v].pb(u);
    }
    FOR(i,1,n) if(G[i].size() == 1) dfs(i,0,sam.rt);
    LL ans = 0;FOR(i,1,sam.tot) ans += sam.len[i]-sam.len[sam.fail[i]];
    printf("%lld\n",ans);
    return 0;
}
