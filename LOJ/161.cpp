/*
 * Author: RainAir
 * Time: 2019-07-18 14:13:53
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
#define SIZE 1000001
inline char nc(){
    static char buf[SIZE],*p1 = buf+SIZE,*p2 = buf+SIZE;
    if(p1 == p2){
        p1 = buf;p2 = buf+fread(buf,1,SIZE,stdin);
        if(p1 == p2) return -1;
    }
    return *p1++;
}

inline void read(LL &x){
    x = 0;char ch = nc();bool flag = 0;
    while(!isdigit(ch)){
        if(ch == '-') flag = true;
        ch = nc();
    }
    while(isdigit(ch)){
        x = (x<<1) + (x<<3) + (ch^'0');
        ch = nc();
    }
    if(flag) x = -x;
}

const int MAXN = 5000000+5;
const int ha = 1e9 + 7;
int n,a[MAXN],pre[MAXN],prei[MAXN],inv[MAXN];

inline int qpow(int a,int n=ha-2){
    int res = 1;
    while(n){
        if(n & 1) res = 1ll*res*a%ha;
        a = 1ll*a*a%ha;
        n >>= 1;
    }
    return res;
}

inline void init(){
    pre[0] = 1;
    FOR(i,1,n) pre[i] = 1ll*pre[i-1]*a[i]%ha;
    prei[n] = qpow(pre[n]);
    ROF(i,n-1,1) prei[i] = 1ll*prei[i+1]*a[i+1]%ha;
    FOR(i,1,n) inv[i] = 1ll*prei[i]*pre[i-1]%ha;
}

signed main(){
    read(n);
    FOR(i,1,n) read(a[i]);
    init();
    int ans = 0;
    FOR(i,1,n){
        ans = (1ll*ans*998244353%ha + inv[i])%ha;
    }
    printf("%lld\n",ans);
    return 0;
}
