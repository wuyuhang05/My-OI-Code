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

const int MAXN = 1e5 + 5;
const int MAXM = 16;

struct Edge{
    int to,nxt;
}e[MAXN<<1];
int head[MAXN],cnt;

inline void add(int u,int v){
    e[++cnt] = (Edge){v,head[u]};head[u] = cnt;
}

int n,m;
int f[MAXN][MAXM+1],dep[MAXN];
int a[MAXN],b[MAXN];
LL sma[MAXN],smb[MAXN];
LL ra[MAXN],rb[MAXN];

inline void dfs(int v,int fa=0){
    f[v][0] = fa;dep[v] = dep[fa]+1;
    FOR(i,1,MAXM) f[v][i] = f[f[v][i-1]][i-1];
    sma[v] = sma[fa]+a[v];
    smb[v] = smb[fa]+b[v];
    ra[v] = ra[fa]+a[v]*smb[fa];
    rb[v] = rb[fa]+b[v]*sma[fa];
    for(int i = head[v];i;i = e[i].nxt){
        if(e[i].to == fa) continue;
        dfs(e[i].to,v);
    }
}

inline int lca(int x,int y){
    if(dep[x] != dep[y]){
        if(dep[x] < dep[y]) std::swap(x,y);
        int d = dep[x]-dep[y];
        FOR(i,0,MAXM){
            if((d>>i)&1) x = f[x][i];
        }
    }
    if(x == y) return x;
    ROF(i,MAXM,0){
        if(f[x][i] == f[y][i]) continue;
        x = f[x][i],y = f[y][i];
    }
    return f[x][0];
}

int main(){
    scanf("%d%d",&n,&m);
    FOR(i,2,n){
        int f;scanf("%d",&f);add(f,i);
    }
    FOR(i,1,n) scanf("%d",a+i);
    FOR(i,1,n) scanf("%d",b+i);
    dfs(1);
    FOR(i,1,m){
        int x,y;scanf("%d%d",&x,&y);
        int l = lca(x,y);
        LL ans = (sma[x]-sma[l])*(smb[y]-smb[l]);
        ans += ra[x]+rb[y]-ra[f[l][0]]-rb[f[l][0]];
        ans -= (sma[x]-sma[f[l][0]])*smb[f[l][0]];
//        DEBUG(ans);
        ans -= (smb[y]-smb[f[l][0]])*sma[f[l][0]];
        printf("%lld\n",ans);
    }
    return 0;
}