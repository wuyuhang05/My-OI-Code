/*
 * Author: RainAir
 * Time: 2019-09-05 21:48:26
 */
#include <algorithm>
#include <iostream>
#include <assert.h>
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
#define int LL
const int MAXN = 5e6 + 5;
int n,m;
int a[MAXN],sm[MAXN];
int _L,_R;

inline bool chk(int k){
    sm[0] = a[0];LL res = 0;
    FOR(i,1,m) sm[i] = sm[i-1] + (i >= k ? a[i] : -a[i]);
    FOR(l,_L,_R){
        int L = l,R = std::min(k-1,_R),ans = -1; // 单调升
        while(L <= R){
            int mid = (L + R) >> 1;
            if(sm[m]-(sm[mid]-sm[l-1]) >= 0) ans = mid,R = mid-1;
            else L = mid+1;
        }
        if(ans != -1) res += std::min(k-1,_R)-ans+1;
        L = std::max(l,k),R = std::min(m,_R),ans = -1; // 单调降
        while(L <= R){
            int mid = (L + R) >> 1;
            if(sm[m]-(sm[mid]-sm[l-1]) >= 0) ans = mid,L = mid+1;
            else R = mid-1;
        }
        if(ans != -1) res += ans-std::max(l,k)+1;
    }
    int len = (_R - _L + 1);
    return 1ll*len*(len+1) <= 4ll*res;
}

signed main(){
    scanf("%lld%lld%lld%lld",&n,&m,&_L,&_R);
    FOR(i,1,n){
        int x;scanf("%lld",&x);++a[x];
    }
    int L = 1,R = m,ans = -19260817;
    while(L <= R){
        int mid = (L + R) >> 1;
        if(chk(mid)) ans = mid,L = mid + 1;
        else R = mid - 1;
    }
    assert(ans != -19260817);
    printf("%lld\n",ans);
    return 0;
}
