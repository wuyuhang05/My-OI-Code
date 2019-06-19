#include <algorithm>
#include <iostream>
#include <cstring>
#include <climits>
#include <cstdlib>
#include <cstdio>
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

const int MAXN = 500000+5;

#define lc (x<<1)
#define rc (x<<1|1)
int min[MAXN<<2],tag[MAXN<<2];

inline void pushup(int x){
    min[x] = std::min(min[lc],min[rc]);
}

inline void cover(int x,int delta){
    min[x] += delta;tag[x] += delta;
}

inline void pushdown(int x){
    if(tag[x]){
        cover(lc,tag[x]);
        cover(rc,tag[x]);
        tag[x] = 0;
    }
}

void build(int x,int l,int r){
    if(l == r){
        min[x] = l;return;
    }
    int mid = (l + r) >> 1;
    build(lc,l,mid);build(rc,mid+1,r);
    pushup(x);
}

inline void modify(int x,int l,int r,int L,int R,int delta){
    if(l == L && r == R){
        cover(x,delta);
        return;
    }
    pushdown(x);
    int mid = (l + r) >> 1;
    if(R <= mid) modify(lc,l,mid,L,R,delta);
    else if(L > mid) modify(rc,mid+1,r,L,R,delta);
    else modify(lc,l,mid,L,mid,delta),modify(rc,mid+1,r,mid+1,R,delta);
    pushup(x);
}

inline int query(int x,int l,int r,int k){
    if(l == r) return min[x] >= k ? l : l+1;
    pushdown(x);
    int mid = (l + r) >> 1;
    if(k <= min[rc]) return query(lc,l,mid,k);
    return query(rc,mid+1,r,k);
}

int n;double k;
int d[MAXN],cnt[MAXN],fa[MAXN],size[MAXN],ans[MAXN];

int main(){
    scanf("%d%lf",&n,&k);
    FOR(i,1,n) scanf("%d",d+i);
    std::sort(d+1,d+n+1,[](int a,int b)->bool{return a > b;});
    ROF(i,n-1,1) cnt[i] = d[i] == d[i+1] ? cnt[i+1]+1 : 0;
    FOR(i,1,n) fa[i] = std::floor(1.0*i/k),size[i] = 1;
    ROF(i,n,1) size[fa[i]] += size[i];
    build(1,1,n);
    FOR(i,1,n){
        if(fa[i] && fa[i] != fa[i-1]) modify(1,1,n,ans[fa[i]],n,size[fa[i]]-1);
        int x = query(1,1,n,size[i]);
        x += cnt[x];cnt[x]++;x -= (cnt[x]-1);ans[i] = x;
        modify(1,1,n,x,n,-size[i]);
    }
    FOR(i,1,n) printf("%d ",d[ans[i]]);
    return 0;
}
