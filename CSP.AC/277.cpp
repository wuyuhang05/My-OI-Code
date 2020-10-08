#include <bits/stdc++.h>

#define fi first
#define se second
#define db double
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

const int MAXN = 2e5 + 5;

std::vector<int> G[MAXN];

struct Edge{
    int u,v,w;

    inline bool operator < (const Edge &t) const {
        return w < t.w;
    }
}e[MAXN];

int n,m;
int dfn[MAXN],low[MAXN],ts;
bool ins[MAXN];
int stk[MAXN],tp;
int t = 0;

inline void dfs(int v){
    dfn[v] = low[v] = ++ts;ins[v] = 1;stk[++tp] = v;
    for(auto x:G[v]){
        if(!dfn[x]){
            dfs(x);
            low[v] = std::min(low[v],low[x]);
        }
        else if(ins[x]) low[v] = std::min(low[v],dfn[x]);
    }
    if(low[v] == dfn[v]){
        ++t;int y = -1;
        do{
            y = stk[tp--];
            ins[y] = 0;
        }while(y != v);
    }
}

inline bool chk(int k){
    FOR(i,1,n) G[i].clear(),ins[i] = dfn[i] = low[i] = 0;
    FOR(i,1,k) G[e[i].u].pb(e[i].v);
    ts = t = 0;dfs(1);bool flag = 1;
    FOR(i,1,n) flag &= (dfn[i] != 0);
    return t == 1 && flag;
}

int main(){
//    freopen("A.in","r",stdin);
    scanf("%d%d",&n,&m);
    FOR(i,1,m) scanf("%d%d%d",&e[i].u,&e[i].v,&e[i].w);
    std::sort(e+1,e+m+1);
    int l = 1,r = m,ans = -1;
    while(l <= r){
        int mid = (l + r) >> 1;
        if(chk(mid)) ans = mid,r = mid-1;
        else l = mid+1;
    }
    printf("%d\n",ans==-1?ans:e[ans].w);
    return 0;
}