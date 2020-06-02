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

const int MAXN = 2e5 + 5;

int n,m;
int c[MAXN];
int f[MAXN][2];//  0 向上 1 向下
int dis[MAXN],ps[MAXN];
#define lc ((v)<<1)
#define rc ((v)<<1|1)

inline void update(int v){
    dis[v] = 1e9;
    int ls = dis[lc]+(f[lc][1]?-1:1),rs = dis[rc]+(f[rc][1]?-1:1);
    if(ls < rs) dis[v] = ls,ps[v] = ps[lc];
    else dis[v] = rs,ps[v] = ps[rc];
    if(c[v] && dis[v] > 0) dis[v] = 0,ps[v] = v;
}

int main(){
    scanf("%d%d",&n,&m);
    FOR(i,1,n) scanf("%d",c+i);
    CLR(dis,0x3f);
    ROF(i,n,1){
        if(c[i]){
            dis[i] = 0;ps[i] = i;
        }
        if(i>>1){
            if(dis[i>>1] > dis[i]+1){
                dis[i>>1] = dis[i]+1;ps[i>>1]=ps[i];
            }
        }
    }
    LL ans = 0;
    FOR(i,1,m){
        int u;scanf("%d",&u);
        int mn = 1e9,lca = -1,t = 0;
        for(int v=u;v;v>>=1){
            if(mn > dis[v]+t){
                mn = dis[v]+t;
                lca = v;
            }
            if(f[v][0]) t--;
            else t++;
        }
        int to;c[to=ps[lca]]--;
        ans += mn;printf("%lld ",ans);
        for(int v=u;v!=lca;v>>=1){
            if(f[v][0]) f[v][0]--;
            else f[v][1]++;
        }
        for(int v=to;v != lca;v>>=1){
            if(f[v][1]) f[v][1]--;
            else f[v][0]++;
        }
        for(int v=u;v;v >>= 1) update(v);
        for(int v=to;v;v >>= 1) update(v);
    }puts("");
    return 0;
}
