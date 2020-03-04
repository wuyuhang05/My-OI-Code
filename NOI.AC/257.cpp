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
#define P std::pair<int,int>
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
P sm[MAXN<<2];
int tag[MAXN<<2];

inline P operator + (const P &a,const P &b){
    return a.fi > b.fi ? a : b;
}

inline void cover(int x,int d){
    sm[x].fi += d;tag[x] += d;
}

inline void build(int x,int l,int r){
    if(l == r) {sm[x] = MP(l,l);return;}
    int mid = (l + r) >> 1;
    build(lc,l,mid);build(rc,mid+1,r);
    sm[x] = sm[lc]+sm[rc];
}

inline void pushdown(int x){
    if(tag[x]){
        cover(lc,tag[x]);cover(rc,tag[x]);
        tag[x] = 0;
    }
}

inline void modify(int x,int l,int r,int L,int R){
    if(l == L && r == R) {cover(x,1);return;}
    int mid = (l + r) >> 1;pushdown(x);
    if(R <= mid) modify(lc,l,mid,L,R);
    else if(L > mid) modify(rc,mid+1,r,L,R);
    else modify(lc,l,mid,L,mid),modify(rc,mid+1,r,mid+1,R);
    sm[x] = sm[lc]+sm[rc];
}

inline P query(int x,int l,int r,int L,int R){
    if(l == L && r == R) return sm[x];
    int mid = (l + r) >> 1;pushdown(x);
    if(R <= mid) return query(lc,l,mid,L,R);
    if(L > mid) return query(rc,mid+1,r,L,R);
    return query(lc,l,mid,L,mid)+query(rc,mid+1,r,mid+1,R);
}

int a[MAXN],ps[MAXN];
int n;
std::vector<P> q[MAXN];
std::set<P> S;
P ans[MAXN];

inline bool chk(P i,int j){
    P x = query(1,1,n,1,-i.fi);
    // DEBUG(x.fi);DEBUG(j);
    if(x.fi == j){
        ans[i.se] = MP(x.se,j);
        return true;
    }
    return false;
}

int main(){
    scanf("%d",&n);
    FOR(i,1,n) scanf("%d",a+i),ps[a[i]] = i;
    int m;scanf("%d",&m);
    FOR(i,1,m){
        int l,r;scanf("%d%d",&l,&r);q[r].pb(MP(-l,i));
    }
    build(1,1,n);
    FOR(i,1,n){
        for(auto x:q[i]) S.insert(x);
        if(a[i] > 1 && ps[a[i]-1] <= i) modify(1,1,n,1,ps[a[i]-1]);
        if(a[i] < n && ps[a[i]+1] <= i) modify(1,1,n,1,ps[a[i]+1]);
        while(!S.empty()){
            if(chk(*S.begin(),i)) S.erase(S.begin());
            else break;
        }
    }
    FOR(i,1,m) printf("%d %d\n",ans[i].fi,ans[i].se);
    return 0;
}
/*
对于这种区间连续的问题有一种**转化套路**，就是 [l,r] 连续**等价于[l,r] 区间存在 r-l 对形如(a[i],a[i+1])** 的区间（要求 i,i+1 都在区间里）
接下来就好做了。我们把询问离线下来 考虑枚举一个右端点同时维护出所有的左端点到这个点的数对个数，只需要查找满足条件的即可。
但是这里没有要求右端点一定在这里，怎么办？
我们可以考虑每次拿出当前询问序列中左端点最大的一个（选择区间最多），如果这个都不可以 剩下的一定不可以。
*/