/*
 * Author: RainAir
 * Time: 2019-08-12 11:14:06
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
const int MAXN = 1e5 + 5;
const int ha = 1e9 + 7;

#define lc ((x)<<1)
#define rc ((x)<<1|1)

int sm[MAXN<<2],L[MAXN<<2],R[MAXN<<2],S[MAXN<<2];

inline void pushup(int x){
    sm[x] = sm[lc]+sm[rc]+1;
    L[x] += L[lc]+L[rc];
    R[x] += R[lc]+R[rc];
    S[x] += S[lc]+S[rc];
}

inline void build(int x,int l,int r){
    if(l == r){
        sm[x] = 0;return;
    }
    L[x] = l;R[x] = r;S[x] = l*r%ha;
    int mid = (l + r) >> 1;
    build(lc,l,mid);build(rc,mid+1,r);
    pushup(x);
}

inline int B(int x,int l,int r,int L,int R){
    if(L <= l && r <= R){
        int Lx = L-1,Rx = R+1;
        int a = (1ll*sm[x]*Lx%ha*Rx%ha+S[x])%ha;
        int b = (1ll*::L[x]*Rx%ha+::R[x]*Lx%ha)%ha;
        return (b-a+ha)%ha;
    }
    int mid = (l + r) >> 1,sm = 0;
    if(L <= mid) (sm += B(lc,l,mid,L,R))%=ha;
    if(R > mid) (sm += B(rc,mid+1,r,L,R))%=ha;
    return sm;
}

inline int query(int x,int l,int r,int L,int R){ //  单次询问 B
    if(L > R) return 0;
    if(l == L && r == R) return sm[x];
    int mid = (l + r) >> 1;
    if(R <= mid) return query(lc,l,mid,L,R);
    if(L > mid) return query(rc,mid+1,r,L,R);
    return query(lc,l,mid,L,mid)+query(rc,mid+1,r,mid+1,R);
}

int pre[MAXN],suf[MAXN],prei[MAXN],presuf[MAXN];
int n,q,N,inv2,inv6;

inline int qpow(int a,int n=ha-2){
    int res = 1;
    while(n){
        if(n & 1) res = 1ll*res*a%ha;
        a = 1ll*a*a%ha;
        n >>= 1;
    }
    return res;
}

inline int C(int l,int r){
    if(l > r) return 0;
    int len = r-l+1;int nn = inv2*N%ha*len%ha*(len+1)%ha;
    int res = 0;
    /*FOR(i,l,r){
        FOR(j,i,r){
            //DEBUG(i);DEBUG(j);DEBUG(N-(query(1,1,n,1,i-1)+query(1,1,n,i+1,n)));
            res += query(1,1,n,1,i-1)+query(1,1,n,j+1,n);
        }
    }*/
    int cp = res;res = 0;
    res = (r+1)*(pre[r-1]-pre[std::max(0ll,l-2)]+ha)%ha;
    res = (res-(prei[r-1]-prei[std::max(0ll,l-2)]+ha)%ha+ha)%ha;
    int t = suf[r+1]*(r-l+1)%ha;
    t = (t-(presuf[r]-presuf[l-1]+ha)%ha+ha)%ha;
    res = (res+t)%ha;
    return (nn-res+ha)%ha;
}

inline int calc(int l,int r){
    int res= (ha-inv6)*(l-r-1+ha)%ha;
    int t = (l*l%ha-l*(2*r+5)%ha+r*r%ha+5*r%ha+6+ha)%ha;
    return res*t%ha;
}



signed main(){inv2 = qpow(2);inv6 = qpow(6);
    scanf("%lld%lld",&n,&q);build(1,1,n);
    N = query(1,1,n,1,n);//总量
    FOR(i,1,n){
        pre[i] = query(1,1,n,1,i);
        suf[i] = query(1,1,n,i,n);
        prei[i] = pre[i]*(i+1)%ha;
    }
    FOR(i,1,n) (suf[i] += suf[i-1])%=ha,(pre[i] += pre[i-1])%=ha,(prei[i] += prei[i-1])%=ha;
    FOR(i,1,n) presuf[i] = presuf[i-1]+suf[i];
    suf[n+1] = suf[n];
    while(q--){
        int l,r;scanf("%lld%lld",&l,&r);int len = r-l+1;
        int b = B(1,1,n,l,r),c = C(l,r);//DEBUG(b);DEBUG(c);
        int ans = (c-2*b%ha+ha)%ha;
        ans = (ans+calc(l,r))%ha;
        printf("%lld\n",ans);
    }
    return 0;
}


