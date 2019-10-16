/*
 * Author: RainAir
 * Time: 2019-10-10 11:25:49
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
const int MAXN = 1e6 + 5;

int mx[MAXN<<2],tag[MAXN<<2];
#define lc ((x)<<1)
#define rc ((x)<<1|1)

inline void pushup(int x){
    mx[x] = std::max(mx[lc],mx[rc]);
}

inline void cover(int x,int d){
    mx[x] += d;
    tag[x] += d;
}

inline void pushdown(int x){
    if(tag[x]){
        cover(lc,tag[x]);
        cover(rc,tag[x]);
        tag[x] = 0;
    }
}

inline void modify(int x,int l,int r,int L,int R,int d){
    if(L > R) return;
    if(l == L && r == R){
        cover(x,d);
        return;
    }
    int mid = (l + r) >> 1;
    pushdown(x);
    if(R <= mid) modify(lc,l,mid,L,R,d);
    else if(L > mid) modify(rc,mid+1,r,L,R,d);
    else modify(lc,l,mid,L,mid,d),modify(rc,mid+1,r,mid+1,R,d);
    pushup(x);
}

inline int query(int x,int l,int r,int L,int R){
    if(l == L && r == R) return mx[x];
    int mid = (l + r) >> 1;
    pushdown(x);
    if(R <= mid) return query(lc,l,mid,L,R);
    if(L > mid) return query(rc,mid+1,r,L,R);
    return std::max(query(lc,l,mid,L,mid),query(rc,mid+1,r,mid+1,R));
}

int f[MAXN],w[MAXN];
int nxt[MAXN],ps[MAXN];
int n,m,ans;
int vis[MAXN];

signed main(){
    scanf("%lld%lld",&n,&m);
    FOR(i,1,n) scanf("%lld",f+i);
    FOR(i,1,m) scanf("%lld",w+i);
    ROF(i,n,1) nxt[i] = ps[f[i]],ps[f[i]] = i;
    FOR(i,1,n) if(!nxt[i]) nxt[i] = n+1;
    FOR(i,1,m) modify(1,1,n,ps[i],nxt[ps[i]]-1,w[i]);
    FOR(i,1,n){
        ans = std::max(ans,query(1,1,n,i,n));
        modify(1,1,n,i,nxt[i]-1,-w[f[i]]);
        modify(1,1,n,nxt[i],nxt[nxt[i]]-1,w[f[i]]);
    }
    printf("%lld\n",ans);
    return 0;
}
