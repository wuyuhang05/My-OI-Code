/*
 * Author: RainAir
 * Time: 2019-09-13 21:38:19
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

const int MAXN = 1e5 + 5;

#define lc ((x)<<1)
#define rc ((x)<<1|1)

int sm[MAXN<<2],tag[MAXN<<2];

inline void pushup(int x){
    sm[x] = sm[lc]&sm[rc];
}

inline void cover(int x,int d){
    sm[x] |= d;tag[x] |= d;
}

inline void pushdown(int x){
    if(tag[x]){
        cover(lc,tag[x]);
        cover(rc,tag[x]);
        tag[x] = 0;
    }
}

inline void build(int x,int l,int r){
    sm[x] = tag[x] = 0;
    if(l == r) return;
    int mid = (l + r) >> 1;
    build(lc,l,mid);
    build(rc,mid+1,r);
    pushup(x);
}

inline void modify(int x,int l,int r,int L,int R,int d){
    if(l == L && r == R){
        cover(x,d);
        return;
    }
    pushdown(x);
    int mid = (l + r) >> 1;
    if(R <= mid) modify(lc,l,mid,L,R,d);
    else if(L > mid) modify(rc,mid+1,r,L,R,d);
    else modify(lc,l,mid,L,mid,d),modify(rc,mid+1,r,mid+1,R,d);
    pushup(x);
}

inline int query(int x,int l,int r,int L,int R){
    if(l == L && r == R) return sm[x];
    pushdown(x);
    int mid = (l + r) >> 1;
    if(R <= mid) return query(lc,l,mid,L,R);
    if(L > mid) return query(rc,mid+1,r,L,R);
    return query(lc,l,mid,L,mid)&query(rc,mid+1,r,mid+1,R);
}

int l[MAXN],r[MAXN],q[MAXN];
int n,m;

inline bool chk(int k){
    build(1,1,n);
    FOR(i,1,k) modify(1,1,n,l[i],r[i],q[i]);
    FOR(i,1,k){
        if((query(1,1,n,l[i],r[i])|q[i]) != q[i]) return false;
        // 必须为 1 的位置 含于 这次出现的数
    }
    return true;
}

int main(){
    scanf("%d%d",&n,&m);
    FOR(i,1,m) scanf("%d%d%d",l+i,r+i,q+i);
    int l = 1,r = m,ans = 0;
    while(l <= r){
        int mid = (l + r) >> 1;
        if(chk(mid)) l = mid+1,ans = mid;
        else r = mid-1;
    }
    FOR(i,1,ans) puts("XianDuanShuNaLiNan");
    FOR(i,ans+1,m) puts("MoNiCaiBiaoSuan");
    return 0;
}
