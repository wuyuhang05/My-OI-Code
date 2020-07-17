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
#define P std::pair<LL,int>
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

LL a[MAXN];
namespace Subtask1{
//public:
    std::priority_queue<P> q;
    LL ans[MAXN];
    int L[MAXN],R[MAXN];
    inline void Solve(){
        FOR(i,2,n) L[i] = i-1,R[i] = i+1,q.push(MP(a[i],i)),ans[i] = -1e18;
        a[1] = a[n+1] = -1e18;R[1] = 2;L[n+1] = n;
        L[1] = 1;R[n+1] = n+1;
        FOR(i,1,n/2){
            while(q.top().se != R[L[q.top().se]] || q.top().se != L[R[q.top().se]]) q.pop();
            P v = q.top();q.pop();
            ans[i] = ans[i-1]+v.fi;
            a[v.se] = a[L[v.se]]+a[R[v.se]]-a[v.se];
            q.push(MP(a[v.se],v.se));
            L[v.se] = L[L[v.se]];R[L[v.se]] = v.se;
            R[v.se] = R[R[v.se]];L[R[v.se]] = v.se;
        }
        FOR(i,::L,::R){
            if(ans[i] == -1e18) printf("- ");
            else printf("%lld ",ans[i]);
        }
        puts("");
    }
}

namespace Subtask2{
//public:
    LL f[MAXN][105][2],t[105][2];
    int sz[MAXN];

    inline void merge(int x,int y,int w){
        FOR(i,0,std::min(sz[x],R)) FOR(j,0,1) t[i][j] = f[x][i][j],f[x][i][j] = -1e18;
        FOR(i,0,std::min(sz[x],R)){
            FOR(j,0,std::min(sz[y],R)){
                if(i+j > R) break;
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
        FOR(i,0,n) FOR(j,0,R) FOR(k,0,1) f[i][j][k] = -1e18;
        dfs(1);
        FOR(i,L,R){
            LL gx = std::max(f[1][i][0],f[1][i][1]);
            if(gx == -1e18) printf("- ");
            else printf("%lld ",gx);
        }
        puts("");
    }
}

int main(){
//    freopen("C.in","r",stdin);
//    freopen("C.out","w",stdout);
    scanf("%d%d%d%d",&cs,&n,&L,&R);
    FOR(i,2,n){
        int u,v,w;scanf("%d%d%d",&u,&v,&w);
        add(u,v,w);
        a[i] = w;
    }
    if(cs <= 5) BF::Solve();
    else if(cs <= 8) Subtask2::Solve();
    else if(cs <= 14)Subtask1::Solve();
    else printf("%d\n",0);
    return 0;
}
