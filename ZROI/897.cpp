/*
 * Author: RainAir
 * Time: 2019-08-11 21:44:27
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
const int ha = 998244353;

inline int qpow(int a,int n=ha-2){
    int res = 1;
    while(n){
        if(n & 1) res = 1ll*res*a%ha;
        a = 1ll*a*a%ha;
        n >>= 1;
    }
    return res;
}

#define lc ((x)<<1)
#define rc ((x)<<1|1)
int sm[MAXN<<2],sm2[MAXN<<2],tag[MAXN<<2];
int n,m;

inline void pushup(int x){
    sm[x] = (sm[lc]+sm[rc])%ha;
    sm2[x] = (sm2[lc]+sm2[rc])%ha;
}
//(a+d)^2 = a^2+d^2+2ad
inline void cover(int x,int l,int r,int d){
    (sm2[x] += (d*d%ha*(r-l+1)%ha+2*d%ha*sm[x]%ha)%ha) %= ha;
    (sm[x] += (r-l+1)*d%ha) %= ha;
    (tag[x] += d) %= ha;
}

inline void pushdown(int x,int l,int r){
    if(!tag[x]) return;
    int mid = (l + r) >> 1;
    cover(lc,l,mid,tag[x]);
    cover(rc,mid+1,r,tag[x]);
    tag[x] = 0;
}

inline void modify(int x,int l,int r,int L,int R,int d){
    if(l == L && r == R){
        cover(x,l,r,d);return;
    }
    int mid = (l + r) >> 1;
    pushdown(x,l,r);
    if(R <= mid) modify(lc,l,mid,L,R,d);
    else if(L > mid) modify(rc,mid+1,r,L,R,d);
    else modify(lc,l,mid,L,mid,d),modify(rc,mid+1,r,mid+1,R,d);
    pushup(x);
}

inline int querysum(int x,int l,int r,int L,int R){
    if(l == L && r == R) return sm[x];
    int mid = (l + r) >> 1;pushdown(x,l,r);
    if(R <= mid) return querysum(lc,l,mid,L,R);
    if(L > mid) return querysum(rc,mid+1,r,L,R);
    return (querysum(lc,l,mid,L,mid)+querysum(rc,mid+1,r,mid+1,R))%ha;
}

inline int query1(int l,int r){
    int x = querysum(1,1,n,l,r);
    return x*x%ha;
}

inline int query2(int x,int l,int r,int L,int R){
    if(l == L && r == R) return sm2[x];
    int mid = (l + r) >> 1;pushdown(x,l,r);
    if(R <= mid) return query2(lc,l,mid,L,R);
    if(L > mid) return query2(rc,mid+1,r,L,R);
    return (query2(lc,l,mid,L,mid)+query2(rc,mid+1,r,mid+1,R))%ha;
}

int fac[MAXN],inv[MAXN],pw[MAXN],ii[MAXN];
int A[MAXN],B[MAXN],C[MAXN];

inline void prework(int n){
    fac[0] = pw[0] = 1;
    FOR(i,1,n) fac[i] = 1ll*fac[i-1]*i%ha;
    inv[n] = qpow(fac[n]);
    ROF(i,n-1,0) inv[i] = 1ll*inv[i+1]*(i+1)%ha;
    FOR(i,1,n) ii[i] = fac[i-1]*inv[i]%ha; // 1/i
    FOR(i,1,n) pw[i] = pw[i-1]*2ll%ha;
    FOR(i,1,n) A[i] = (pw[i]-1+ha)%ha*ii[i]%ha;
    FOR(i,1,n) B[i] = (B[i-1]+(pw[i]-1+ha)%ha*ii[i]%ha)%ha;
    FOR(i,1,n) B[i] = B[i]*ii[i]%ha;
    FOR(i,1,n) C[i] = (C[i-1]+((i-1)*ii[i]%ha+(pw[i-1]-1+ha)%ha-ii[i]*(pw[i]-2+ha)%ha+ha)%ha)%ha;
    FOR(i,1,n) C[i] = C[i]*ii[i]%ha*ii[i-1]%ha;
}
/*
inline int C(int n,int m){
    if(n < m) return 0;
    return fac[n]*inv[m]%ha*inv[n-m]%ha;
}
*/
inline int query(int l,int r){
    int s1 = query1(l,r),s2 = query2(1,1,n,l,r);
    int x1 = 1ll*s2*A[r-l+1]%ha;
    int x2 = 1ll*s2*B[r-l+1]%ha;
    int x3 = 1ll*s2*C[r-l+1]%ha;
    int x4 = 1ll*s1*C[r-l+1]%ha;
    int ans = (x1-x2+ha)%ha;
    (ans += x3) %= ha;
    ans = (ans-x4+ha)%ha;
    return ans;
    return (x1-x2+x3-x4+ha+ha)%ha;
}

signed main(){
    scanf("%lld%lld",&n,&m);prework(n+2);
    FOR(i,1,m){
        int opt,l,r,a;scanf("%lld%lld%lld",&opt,&l,&r);
        if(opt == 1){scanf("%lld",&a);
            modify(1,1,n,l,r,a);
        }
        else{
            printf("%lld\n",query(l,r));
        }
    }
    return 0;
}
