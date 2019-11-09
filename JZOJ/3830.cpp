/*
 * Author: RainAir
 * Time: 2019-11-08 15:00:39
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

const int MAXN = 1e6 + 5;
const int ha = 1e9 + 7;
const int BASE = 31;
char str[MAXN];

inline int qpow(int a,int n=ha-2){
    int res = 1;
    while(n){
        if(n & 1) res = 1ll*res*a%ha;
        a = 1ll*a*a%ha;
        n >>= 1;
    }
    return res;
}

int pw[MAXN],ipw[MAXN];
int hsh[MAXN];

inline int calc(int l,int r){
    return 1ll*(hsh[r]-1ll*hsh[l-1]*pw[r-l+1]%ha+ha)%ha;
}

int f[MAXN],n;

inline int calc(int p1,int p2,int k){
    int ans = k;
    ROF(i,k,1){
        int l1 = p1,r1 = p1+i-1;
        int r2 = p2,l2 = p2-i+1;
        if(r1 >= l2) continue;
        if(calc(l1,r1) == calc(l2,r2)) return i;
    }
    return 0;
}

inline void Solve(){
    scanf("%s",str+1);n = strlen(str+1);
    FOR(i,1,n) hsh[i] = (1ll*hsh[i-1]*BASE%ha+(str[i]-'a'+1))%ha;
//    if(str[1] == str[n]) f[1] = calc(1,n,0);
    int ans = 0;
    f[n/2+1] = n;
    ROF(i,n/2,1){
        f[i] = calc(i+1,n-i,f[i+1]+2);
        if(calc(1,i) == calc(n-i+1,n)) ans = std::max(ans,i+f[i]);
    }
    printf("%d\n",ans);
    CLR(f,0);
}

int main(){
    int T;scanf("%d",&T);
    pw[0] = 1;
    FOR(i,1,MAXN-1) pw[i] = 1ll*pw[i-1]*BASE%ha;
    ipw[MAXN-1] = qpow(pw[MAXN-1]);
    ROF(i,MAXN-2,0) ipw[i] = 1ll*ipw[i+1]*BASE%ha;
    while(T--) Solve();
    return 0;
}
