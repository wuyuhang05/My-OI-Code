/*
 * Time: 2019-11-12 08:55:39
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
#define int LL
const int MAXN = 2e5 + 5;
int a[MAXN];
char opt[MAXN];
char str[MAXN];
int n;
int f[MAXN],sm[MAXN],suf[MAXN],suff[MAXN];

signed main(){
    scanf("%lld%lld",&n,a+1);sm[0] = 0;sm[1] = a[1];
    FOR(i,2,n){
        scanf("%s",str+1);
        opt[i] = str[1];
        scanf("%lld",a+i);
        sm[i] = sm[i-1]+a[i]*(opt[i]=='+' ? 1 : -1);
    }
    opt[1] = '+';
    suf[n+1] = suff[n+1] = 0;
    ROF(i,n,1){
        suf[i] = (opt[i+1]=='+')*suf[i+1]+a[i];
        suff[i] = suff[i+1]+a[i];
    }
//    FOR(i,1,n) DEBUG(suf[i]);
    int ans = 0;
    FOR(l,2,n){
        if(opt[l] == '+') continue;
        int gx = sm[l-1];
        gx += suff[l];
        gx -= suf[l]*2;
        ans = std::max(ans,gx);
    }
    printf("%lld\n",ans);
    return 0;
}
