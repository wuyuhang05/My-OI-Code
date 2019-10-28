/*
 * Author: RainAir
 * Time: 2019-10-27 15:07:46
 */
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
#define LL long long
#define pb push_back
#define MP std::make_pair
#define all(x) x.begin(),x.end()
#define CLR(i,a) memset(i,a,sizeof(i))
#define FOR(i,a,b) for(int i = a;i <= b;++i)
#define ROF(i,a,b) for(int i = a;i >= b;--i)
#define DEBUG(x) std::cerr << #x << '=' << x << std::endl

const int MAXN = 3000+5;

struct Node{
    int l,r,w;
    bool operator < (const Node &t) const {
        return r == t.r ? l < t.l : r < t.r;
    }
}a[MAXN];
int n,m;
int f[MAXN][MAXN],g[MAXN][MAXN],h[MAXN][MAXN];
// f:f g:min h:pos

inline void Solve(){
    scanf("%d%d",&n,&m);
    FOR(i,1,n) scanf("%d%d%d",&a[i].l,&a[i].r,&a[i].w);
    std::sort(a+1,a+n+1);
    FOR(i,0,n+1) FOR(j,0,m+1) f[i][j] = g[i][j] = 1e9,h[i][j] = -1;
  //  FOR(i,1,n){
 //       printf("%d %d %d\n",a[i].l,a[i].r,a[i].w);
 //   }
    FOR(i,1,n){
        if(a[i].l == 1) f[i][1] = a[i].w;
        FOR(j,1,i-1){
            if(a[j].l >= a[i].l) continue;
            if(a[j].r == a[i].r) continue;
            if(a[j].r >= a[i].l){
    //            if(a[j].r+1 == 16 && i == n) DEBUG(j);
                f[i][a[j].r+1] = std::min(f[i][a[j].r+1],std::max(a[i].w+a[j].w,g[j][a[i].l]));
            }
            else{
                if(a[j].r+1 == a[i].l){
                    if(h[j][a[j].r] != -1){
                        f[i][h[j][a[j].r]] = std::min(f[i][h[j][a[j].r]],std::max(a[i].w,g[j][a[j].r]));
                    }
                }
            }
        }
//        if(i == 12) {FOR(j,1,m) printf("%d ",f[i][j]);puts("");}
        FOR(j,1,a[i].r){
            g[i][j] = g[i][j-1],h[i][j] = h[i][j-1];
            if(f[i][j] < g[i][j]){
                g[i][j] = f[i][j];
                h[i][j] = j;
            }
        }
    }
    int ans = 1e9;
    //FOR(i,1,n) if(a[i].r == m) DEBUG(g[i][m]);
    FOR(i,1,n) if(a[i].r == m) ans = std::min(ans,g[i][m]);
    printf("%d\n",ans == 1e9 ? -1 : ans);
//    exit(0);
}

int main(){
    freopen("intervals.in","r",stdin);
    freopen("intervals.out","w",stdout);
    int T;scanf("%d",&T);
    while(T--) Solve();
    return 0;
}
