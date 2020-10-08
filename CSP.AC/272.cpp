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
LL a[MAXN];int n;

struct Edge{
    int to,nxt;
}e[MAXN<<1];
int head[MAXN],cnt;

inline void add(int u,int v){
    e[++cnt] = (Edge){v,head[u]};head[u] = cnt;
    e[++cnt] = (Edge){u,head[v]};head[v] = cnt;
}

LL f[MAXN][4],g[MAXN][4];

inline LL calc(LL s1,LL s2,LL s3){
    return s1*s1*s1-s2*s1*3+s3*2;
}

inline LL calc2(LL s1,LL s2){
    return s1*s1-s2;
}

int main(){
    scanf("%d",&n);
    FOR(i,1,n) scanf("%lld",a+i);
    FOR(i,2,n){
        int u,v;scanf("%d%d",&u,&v);
        add(u,v);
    }
    FOR(v,1,n) for(int i = head[v];i;i = e[i].nxt){
        LL val = a[e[i].to];
        FOR(j,1,3){
            f[v][j] += val;
            val = val*a[e[i].to];
        }
    }
    FOR(v,1,n) for(int i = head[v];i;i = e[i].nxt){
        g[v][1] += f[e[i].to][1]-a[v];
        g[v][2] += f[e[i].to][2]-a[v]*a[v];
        g[v][3] += f[e[i].to][3]-a[v]*a[v]*a[v];
    }
    LL ans = 0;
    FOR(i,1,n) ans += calc(g[i][1],g[i][2],g[i][3]);//,DEBUG(calc(g[i][1],g[i][2],g[i][3]));
    FOR(v,1,n){
        LL gx = 0,sm = 0;
        for(int i = head[v];i;i = e[i].nxt) sm += f[e[i].to][1]-a[v];
        for(int i = head[v];i;i = e[i].nxt){
            gx += calc(f[e[i].to][1]-a[v],f[e[i].to][2]-a[v]*a[v],f[e[i].to][3]-a[v]*a[v]*a[v]);
            ans -= calc(f[e[i].to][1]-a[v],f[e[i].to][2]-a[v]*a[v],f[e[i].to][3]-a[v]*a[v]*a[v]);
            LL t = calc2(f[e[i].to][1]-a[v],f[e[i].to][2]-a[v]*a[v]);
            sm -= f[e[i].to][1]-a[v];
            ans -= t*sm*3;
            sm += f[e[i].to][1]-a[v];
        }
//        DEBUG(gx);
    }
//    assert(ans%6==0);
    ans /= 6;
    printf("%lld\n",ans);
    return 0;
}