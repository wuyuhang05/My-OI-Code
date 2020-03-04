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
int n,T,R;
struct Node{
    int s,p,t,id;
    bool operator < (const Node &t) const {
        return s < t.s;
    }
}a[MAXN];
LL f[MAXN][MAXN];
bool g[MAXN][MAXN];
// 前i 个 花j天

int main(){
    scanf("%d%d%d",&n,&T,&R);
    FOR(i,1,n) scanf("%d%d%d",&a[i].s,&a[i].p,&a[i].t),a[i].id = i;
    std::sort(a+1,a+n+1);
    f[0][0] = R;
    FOR(i,0,n-1){
        FOR(j,0,T){
            if(f[i][j] > f[i+1][j]){
                f[i+1][j] = f[i][j];
                g[i+1][j] = false;
            }
            if(f[i][j] >= a[i+1].s && j+a[i+1].t <= T && f[i][j]+a[i+1].p > f[i+1][j+a[i+1].t]){
                f[i+1][j+a[i+1].t] = f[i][j]+a[i+1].p;
                g[i+1][j+a[i+1].t] = true;
            }
        }
    }
    LL ans = 0;
    FOR(i,0,T) ans = std::max(ans,f[n][i]);
    printf("%lld\n",ans);
    FOR(i,0,T){
        if(f[n][i] != ans) continue;
        int pos = i;std::vector<int> ans;
        ROF(j,n,1){
            // DEBUG(g[j][pos]);
            if(g[j][pos]){
                pos -= a[j].t;
                ans.pb(a[j].id);
            }
        }
        std::reverse(all(ans));
        for(auto x:ans) printf("%d ",x);puts("");
        return 0;
    }
    return 0;
}