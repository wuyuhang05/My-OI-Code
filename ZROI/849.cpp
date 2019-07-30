/*
 * Author: RainAir
 * Time: 2019-07-17 17:46:08
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
#define P std::pair<LL,LL>
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
const int inv2 = 500000004;

inline void add(LL &a,LL b){
    a += b;while(a > ha) a -= ha;
    while(a < 0) a += ha;
}

int sm[MAXN<<2],cm[MAXN<<2],tag[MAXN<<2];
#define lc ((x)<<1)
#define rc ((x)<<1|1)

inline void pushup(int x){
    sm[x] = (sm[lc] + sm[rc])%ha;
    cm[x] = (cm[lc] + cm[rc])%ha;
}

inline void cover(int x,int l,int r,int k){
    (cm[x] += 1ll*(r-l+1)*k%ha*(k-1)%ha*inv2%ha + 1ll*sm[x]*k%ha)%=ha;
    (sm[x] += 1ll*(r-l+1)*k%ha) %= ha;
    add(tag[x],k);
}

inline void pushdown(int x,int l,int r){
    if(tag[x]){
        int mid = (l + r) >> 1;
        cover(lc,l,mid,tag[x]);
        cover(rc,mid+1,r,tag[x]);
        tag[x] = 0;
    }
}

inline void build(int x,int l,int r){
    tag[x] = 0;sm[x] = cm[x] = 0;
    if(l == r){
        return;
    }
    int mid = (l + r) >> 1;
    build(lc,l,mid);build(rc,mid+1,r);
    pushup(x);
}

inline void modify(int x,int l,int r,int L,int R,int k){
    if(L > R) return;
    if(l == L && r == R){
        cover(x,l,r,k);
        return;
    }
    int mid = (l + r) >> 1;pushdown(x,l,r);
    if(R <= mid) modify(lc,l,mid,L,R,k);
    else if(L > mid) modify(rc,mid+1,r,L,R,k);
    else modify(lc,l,mid,L,mid,k),modify(rc,mid+1,r,mid+1,R,k);
    pushup(x);
}

inline int query(int x,int l,int r,int L,int R){
    if(L > R) return 0;
    if(l == L && r == R) return cm[x];
    pushdown(x,l,r);
    int mid = (l + r) >> 1;
    if(R <= mid) return query(lc,l,mid,L,R);
    if(L > mid) return query(rc,mid+1,r,L,R);
    return query(lc,l,mid,L,mid)+query(rc,mid+1,r,mid+1,R);
}

int w,h,n,m;
int ans;
std::vector<P> t;
int v[MAXN],cnt;

signed main(){
    scanf("%lld%lld%lld%lld",&w,&h,&n,&m);
    FOR(i,1,n){
        int c;scanf("%lld",&c);
        v[++cnt] = c;t.pb(MP(c,INT_MAX));
    }
    std::sort(v+1,v+cnt+1);
    FOR(i,1,m){
        int d;scanf("%lld",&d);
        int p1 = std::abs(d);
        int p2 = std::min(2ll*h+d,2ll*w-d);
        // (w,w-c) (h+c,h)
        // (2w-c,-c) (2h+c,c)
        t.pb(MP(p1,p2));
    }
    std::sort(all(t));
    build(1,1,n);
    for(auto tt:t){
        int x = tt.fi,y = tt.se;
        if(y == INT_MAX){ // query
            int p = std::lower_bound(v+1,v+n+1,x)-v;
            if(p < n) (ans += query(1,1,n,p+1,n)) %= ha;
        }
        else{ // add
            int p = std::upper_bound(v+1,v+n+1,y)-v;p--; 
            if(p >= 1) modify(1,1,n,1,p,1);
        }
    }
    printf("%lld\n",ans);
    return 0;
}

