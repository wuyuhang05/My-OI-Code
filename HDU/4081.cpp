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
#define U unsigned
#define P std::pair
#define Re register
#define LL long long
#define pb push_back
#define MP std::make_pair
#define all(x) x.begin(),x.end()
#define CLR(i,a) memset(i,a,sizeof(i))
#define FOR(i,a,b) for(Re int i = a;i <= b;++i)
#define ROF(i,a,b) for(Re int i = a;i >= b;--i)
#define DEBUG(x) std::cerr << #x << '=' << x << std::endl

const int MAXN = 1000+5;
const double EPS = 1e-6;

inline int sgn(double x){
    return std::abs(x) <= EPS ? 0 : (x > 0 ? 1 : -1);
}

struct Node{
    double x,y,p;
}a[MAXN];
int n;

inline double dis(const Node &a,const Node &b){
    return std::sqrt(1.0*(a.x-b.x)*(a.x-b.x) + 1.0*(a.y-b.y)*(a.y-b.y));
}

int pre[MAXN];
double d[MAXN];
bool used[MAXN][MAXN],vis[MAXN];
double G[MAXN][MAXN],p[MAXN][MAXN],B;

inline void prim(){
    FOR(i,1,n){
        d[i] = G[i][1];
        pre[i] = 1;
    }vis[1] = 1;
    FOR(i,1,n-1){
        int u = -1;
        FOR(j,1,n){
            if(!vis[j] && (u == -1 || d[u] > d[j])) u = j;
        }
        used[pre[u]][u] = used[u][pre[u]] = true;
        B += G[pre[u]][u];vis[u] = true;
        FOR(j,1,n){
            if(vis[j] && j != u) p[u][j] = p[j][u] = std::fmax(p[j][pre[u]],d[u]);
            if(!vis[j]) if(d[j] > G[u][j]){
                d[j] = G[u][j];pre[j] = u;
            }
        }
    }
}

inline void init(){
    B = 0;CLR(pre,0);CLR(d,0);CLR(used,0);
    CLR(vis,0);CLR(G,0);CLR(p,0);CLR(a,0);
}

inline void Solve(){
    scanf("%d",&n);init();
    FOR(i,1,n) scanf("%lf%lf%lf",&a[i].x,&a[i].y,&a[i].p);
    FOR(i,1,n) FOR(j,1,n) G[i][j] = dis(a[i],a[j]);   
    prim();double ans = -1;//printf("%f\n",B);
    FOR(i,1,n){
        FOR(j,1,n){
            if(i != j){
                if(used[i][j]){
                    ans = std::fmax(ans,(a[i].p+a[j].p)/(B-G[i][j]));
                }
                else{
                    ans = std::fmax(ans,(a[i].p+a[j].p)/(B-p[i][j]));
                }
            }
        }
    }
    printf("%.2lf\n",ans);
}

int main(){
    int T;scanf("%d",&T);
    while(T--) Solve();
    return 0;
}
