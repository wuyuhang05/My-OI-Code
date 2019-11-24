/*
 * Time: 2019-11-12 08:23:31
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
#define P std::pair<LL,LL>
#define LL long long
#define pb push_back
#define MP std::make_pair
#define all(x) x.begin(),x.end()
#define CLR(i,a) memset(i,a,sizeof(i))
#define FOR(i,a,b) for(LL i = a;i <= b;++i)
#define ROF(i,a,b) for(LL i = a;i >= b;--i)
#define DEBUG(x) std::cerr << #x << '=' << x << std::endl
#define int LL
const int MAXN = 6e5 + 5;
std::vector<P> qu[MAXN];
int n,a[MAXN],q;
LL ans[MAXN];
LL sm[MAXN];

signed main(){
 //   freopen("a.in","r",stdin);
    scanf("%lld",&n);
    FOR(i,1,n) scanf("%lld",a+i);
    scanf("%lld",&q);
    FOR(i,1,q){
        int x,y;scanf("%lld%lld",&y,&x);
        qu[x].pb(MP(y,i));
    }
    int qq = std::sqrt(1.0*n);
    FOR(i,1,n){
        if(qu[i].empty()) continue;
        if(i <= qq){
            sm[n+i] = 0;
            ROF(j,n,1){
                sm[j] = sm[i+j]+a[j];
            }
            FOR(j,0,(int)qu[i].size()-1){
                ans[qu[i][j].se] += sm[qu[i][j].fi];
            }
        }
        else{
            FOR(j,0,(int)qu[i].size()-1){
                for(int x = qu[i][j].fi;x <= n;x += i){
                    ans[qu[i][j].se] += a[x];
                }
            }
        }
    }
    FOR(i,1,q) printf("%lld\n",ans[i]);
    return 0;
}
