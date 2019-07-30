/*
 * Author: RainAir
 * Time: 2019-07-23 14:16:00
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
#define Re register
#define LL long long
#define pb push_back
#define MP std::make_pair
#define all(x) x.begin(),x.end()
#define CLR(i,a) memset(i,a,sizeof(i))
#define FOR(i,a,b) for(Re int i = a;i <= b;++i)
#define ROF(i,a,b) for(Re int i = a;i >= b;--i)
#define DEBUG(x) std::cerr << #x << '=' << x << std::endl
#define int LL
const int MAXN = 5e6 + 5;
int n,Sa,Sb,Sc,Sd,ha;
int a[MAXN];

inline int F(int x){
    return (1ll*Sa*x%ha*x%ha*x%ha+Sb*x%ha*x%ha+Sc*x%ha+Sd) % ha;
}

inline void gen(){
    scanf("%lld%lld%lld%lld%lld%lld%lld",&n,&Sa,&Sb,&Sc,&Sd,a+1,&ha);
    a[0] = 0;
    FOR(i,2,n){
        a[i] = (F(a[i-1])+F(a[i-2]))%ha;
    }
}

inline bool chk(int k){
    int least = std::max(1ll,a[1]-k);
    FOR(i,2,n){
        if(a[i] < least){
            if(least-a[i] > k) return false;
        }
        else{
            least = std::max(least,a[i]-k);
        }
    }
    return true;
}

signed main(){
    gen();
    bool flag = true;
    FOR(i,2,n) if(a[i-1] > a[i]){
        flag = false;break;
    }
    if(flag){
        puts("0");return 0;
    }
   // FOR(i,1,n) DEBUG(a[i]);
    int l = 0,r = 1e9,ans;
    while(l <= r){
        int mid = (l + r) >> 1;
        if(chk(mid)) r = mid-1,ans = mid;
        else l = mid+1;
    }
    printf("%lld\n",ans);
    return 0;
}
