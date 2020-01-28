/*
 * Time: 2019-11-29 16:57:47
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

const int MAXN = 1e5 + 5;
const int BLO = 500;
LL a[MAXN],n,sm[MAXN];
double alpha;

int main(){
//    freopen("a.in","r",stdin);
    scanf("%lld%lf",&n,&alpha);
    FOR(i,1,n) scanf("%lld",a+i),sm[i] += sm[i-1]+a[i];
    FOR(i,1,n){
        int j = (1.0*alpha*i+1e-8);
        double ans = 0;
        if(!j){
            printf("%.10f\n",ans);
            continue;
        }
        if(j <= BLO){
            FOR(k,1,j) ans += 1.0*(a[i]*a[k])/(i-k);
            printf("%.10f\n",ans);
            continue;
        }
        int l = 1,r = BLO;
        for(;r <= j;l = r+1,r += BLO){
            ans += 1.0*(sm[r]-sm[l-1])/(i-((l+r)/2.0));
        }
        FOR(k,l,j) ans += 1.0*a[k]/(i-k);
        ans *= a[i];
        printf("%.10f\n",ans);
    }
    return 0;
}
