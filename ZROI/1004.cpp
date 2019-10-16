/*
 * Author: RainAir
 * Time: 2019-09-22 08:32:24
 */
#include <unordered_map>
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
#define int LL
const int MAXN = 1e5 + 5;
int a[MAXN],b[MAXN],n,p;
LL ans = 0;
std::unordered_map<int,int> S;

inline int qpow(int a,int n=p-2){
    int res = 1;
    while(n){
        if(n & 1) res = 1ll*res*a%p;
        a = 1ll*a*a%p;
        n >>= 1;
    }
    return res;
}
int s[MAXN];
signed main(){
    scanf("%lld%lld",&n,&p);
    FOR(i,1,n){
        int x;scanf("%lld",&x);
        x %= p;s[i] = x;
        a[i] = 1ll*x*x%p;
        b[i] = 4ll*x%p;
    }
    FOR(i,1,n) if(s[i]) S[a[i]]++;
    FOR(i,1,n){
        if(!s[i]) continue;
        int flag = 0;
        if(qpow(b[i]) == a[i]) flag = 1;
        ans += S[qpow(b[i])] - flag;
    }
    printf("%lld\n",ans);
    return 0;
}
