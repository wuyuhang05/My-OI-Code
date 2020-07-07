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
#define db double
#define U unsigned
#define P std::pair<int,int>
#define LL long long
#define pb push_back
#define MP std::make_pair
#define all(x) x.begin(),x.end()
#define CLR(i,a) memset(i,a,sizeof(i))
#define FOR(i,a,b) for(int i = a;i <= b;++i)
#define ROF(i,a,b) for(int i = a;i >= b;--i)
#define DEBUG(x) std::cerr << #x << '=' << x << std::endl

const int MAXN = 2e5 + 5;

int mn[MAXN<<2],tag[MAXN<<2];
#define lc ((x)<<1)
#define rc ((x)<<1|1)

inline void pushup(int x){
    mn[x] = std::min(mn[lc],mn[rc]);
}

inline void cover(int x,int d){
    mn[x] += d;tag[x] += d;
}

inline void pushdown(int x){
    if(tag[x]){
        cover(lc,tag[x]);cover(rc,tag[x]);tag[x] = 0;
    }
}

inline void modify(int x,int l,int r,int L,int R,int d){
    if(l == L && r == R){cover(x,d);return;}
    int mid = (l + r) >> 1;pushdown(x);
    if(R <= mid) modify(lc,l,mid,L,R,d);
    else if(L > mid) modify(rc,mid+1,r,L,R,d);
    else modify(lc,l,mid,L,mid,d),modify(rc,mid+1,r,mid+1,R,d);
    pushup(x);
}

int a[MAXN];

struct BIT{
    #define lowbit(x) ((x)&(-(x)))
    int tree[MAXN];

    inline void add(int pos,int d){
        for(;pos < MAXN;pos += lowbit(pos)) tree[pos] += d;
    }

    inline int query(int pos){
        int res=0;
        for(;pos;pos -= lowbit(pos)) res += tree[pos];
        return res;
    }
}bit;

inline void build(int x,int l,int r){
    if(l == r){
        mn[x] = l-1;
        return;
    }
    int mid = (l + r) >> 1;
    build(lc,l,mid);build(rc,mid+1,r);
    pushup(x);
}
int ps[MAXN];
int main(){
    int n;scanf("%d",&n);n>>=1;
    LL ans = 0;
    FOR(i,1,n){
        scanf("%d",a+i);ps[a[i]] = i;
        ans += bit.query(2*n)-bit.query(a[i]);bit.add(a[i],1);
    }
    build(1,1,n+1);
    FOR(i,1,n){
        ans += mn[1];
        modify(1,1,n+1,1,ps[i*2],1);
        modify(1,1,n+1,ps[i*2]+1,n+1,-1);
    }
    printf("%lld\n",ans);
    return 0;
}
