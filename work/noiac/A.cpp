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
#define int LL
const int MAXN = 20+5;
LL a[MAXN];
int n,m;
int cnt[MAXN];

inline int C(int n,int m){
    LL ans = 1;
    FOR(i,1,n) ans *= i;
    FOR(i,1,m) ans /= i;
    FOR(i,1,n-m) ans /= i;
    return ans;
}

signed main(){
    scanf("%lld%lld",&n,&m);LL ss = 0;
    FOR(i,0,n-1) scanf("%lld",a+i),ss += a[i];
    int ans = 0;
    FOR(S,0,(1<<n)-1){
        LL sm = 0;
        FOR(i,0,n-1){
            if((S>>i)&1) sm += a[i];
        }
        if(sm >= m) continue;
        bool flag = 1;
        FOR(i,0,n-1){
            if((S>>i)&1) continue;
            if(sm+a[i]<m){
                flag = 0;break;
            }
        }
        if(flag) ans++;
    }
    printf("%lld\n",ans);
    return 0;
}
