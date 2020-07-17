#include <algorithm>
#include <iostream>
#include <cstring>
#include <climits>
#include <cstdlib>
#include <cstdio>
#include <bitset>
#include <vector>
#include <cmath>
#include <ctime>
#include <queue>
#include <stack>
#include <map>
#include <set>

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

struct Edge{
    int to,w,nxt;
}e[MAXN<<1];
int head[MAXN],cnt;

inline void add(int u,int v,int w){
    e[++cnt] = (Edge){v,w,head[u]};head[u] = cnt;
    e[++cnt] = (Edge){u,w,head[v]};head[v] = cnt;
}

inline void upmax(LL &x,LL y){
    if(x < y) x = y;
}

int n,L,R,cs;

namespace BF{
//public:
    LL f[2005][2005][2],t[MAXN][2];
    int sz[MAXN];

    inline void merge(int x,int y,int w){
        FOR(i,0,sz[x]) FOR(j,0,1) t[i][j] = f[x][i][j],f[x][i][j] = -1e18;
        FOR(i,0,sz[x]){
            FOR(j,0,sz[y]){
                if(t[i][0] != -1e18){
                    if(f[y][j][0] != -1e18){
                        upmax(f[x][i+j+1][1],t[i][0]+f[y][j][0]+w);
                        upmax(f[x][i+j][0],t[i][0]+f[y][j][0]);
                    }
                    if(f[y][j][1] != -1e18) upmax(f[x][i+j][0],t[i][0]+f[y][j][1]);
                }
                if(t[i][1] != -1e18){
                    if(f[y][j][0] != -1e18) upmax(f[x][i+j][1],t[i][1]+f[y][j][0]);
                    if(f[y][j][1] != -1e18) upmax(f[x][i+j][1],t[i][1]+f[y][j][1]);
                }
            }
        }
        sz[x] += sz[y];
    }

    inline void dfs(int v,int fa=0){
        sz[v] = 1;f[v][0][0] = 0;
        for(int i = head[v];i;i = e[i].nxt){
            if(e[i].to == fa) continue;
            dfs(e[i].to,v);merge(v,e[i].to,e[i].w);
        }
    }

    inline void Solve(){
        FOR(i,0,n) FOR(j,0,n) FOR(k,0,1) f[i][j][k] = -1e18;
        dfs(1);
        FOR(i,L,R){
            LL gx = std::max(f[1][i][0],f[1][i][1]);
            if(gx == -1e18) printf("- ");
            else printf("%lld ",gx);
        }
        puts("");
    }
}

namespace Subtask1{
//public:

    LL f[MAXN][2],t[2],ext;
    int g[MAXN][2],tt[2];

    inline void dfs(int v,int fa=0){
        f[v][0] = 0;f[v][1] = -1e18;
        for(int i = head[v];i;i = e[i].nxt){
            if(e[i].to == fa) continue;
            dfs(e[i].to,v);
            t[0] = f[v][0],t[1] = f[v][1];
            tt[0] = g[v][0];tt[1] = g[v][1];
            if(t[0] != -1e18){
                if(f[e[i].to][0] != -1e18){
                    if(f[v][0] < t[0]+f[e[i].to][0]){
                        f[v][0] = t[0]+f[e[i].to][0];
                        g[v][0] = tt[0]+g[e[i].to][0];
                    }
                }
                if(f[e[i].to][1] != -1e18){
                    if(f[v][0] < t[0]+f[e[i].to][1]){
                        f[v][0] = t[0]+f[e[i].to][1];
                        g[v][0] = tt[0]+g[e[i].to][1];
                    }
                }
            }
            if(t[1] != -1e18){
                if(f[e[i].to][0] != -1e18){
                    if(f[v][1] < t[1]+f[e[i].to][0]){
                        f[v][1] = t[1]+f[e[i].to][0];
                        g[v][1] = tt[1]+g[e[i].to][0];
                    }
                    if(f[v][1] < t[0]+f[e[i].to][0]+e[i].w+ext){
                        f[v][1] = t[0]+f[e[i].to][0]+e[i].w+ext;
                        g[v][1] = tt[0]+g[e[i].to][0]+1;
                    }
                }
                if(f[e[i].to][1] != -1e18){
                    if(f[v][1] < t[1]+f[e[i].to][1]){
                        f[v][1] = t[1]+f[e[i].to][1];
                        g[v][1] = tt[1]+g[e[i].to][1];
                    }
                }
            }
        }
    }

    inline int chk(LL k){
        ext = k;
        FOR(i,1,n) f[i][0] = f[i][1] = -1e18,g[i][0] = g[i][1] = 0;
        dfs(1);
        if(f[1][0] < f[1][1]) return g[1][1];
        return g[1][0];
    }

    inline void Solve(){
        FOR(i,L,R){
            LL l = -1e10,r = 1e10,ans = -1e18;
            while(l <= r){
                LL mid = (l + r) >> 1;
                if(chk(mid) <= i) ans = mid,l = mid+1;
                else r = mid-1;
            }
            chk(ans);
            if(ans == -1e18) printf("- ");
            else printf("%lld ",std::max(f[1][0],f[1][1]));
        }
        puts("");
    }
}

int main(){
    freopen("C4.in","r",stdin);
    freopen("C.out","w",stdout);
    scanf("%d%d%d%d",&cs,&n,&L,&R);
    FOR(i,2,n){
        int u,v,w;scanf("%d%d%d",&u,&v,&w);
        add(u,v,w);
    }
    if(cs <= 5) BF::Solve();
    Subtask1::Solve();
    return 0;
}

