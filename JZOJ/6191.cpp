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

inline char nc(){
    #define SIZE 1000000+3
    static char buf[SIZE],*p1 = buf+SIZE,*p2 = buf+SIZE;
    if(p1 == p2){
        p1 = buf;p2 = buf+fread(buf,1,SIZE,stdin);
        if(p1 == p2) return -1;
    }
    return *p1++;
    #undef SIZE
}

template <typename T>
inline void read(T &x){
    x = 0;int flag = 0;char ch = nc();
    while(!isdigit(ch)){
        if(ch == '-') flag = 1;
        ch = nc();
    }
    while(isdigit(ch)){
        x = (x<<1) + (x<<3) + (ch^'0');
        ch = nc();
    }
    if(flag) x = -x;
}

const int MAXN = 2e6 + 5;
int mx[MAXN<<2],tag[MAXN<<2];
#define lc ((x)<<1)
#define rc ((x)<<1|1)

inline void cover(int x,int d){
    mx[x] += d;tag[x] += d;
}

inline void pushdown(int x){
    if(tag[x]){
        cover(lc,tag[x]);
        cover(rc,tag[x]);
        tag[x] = 0;
    }
}

inline void modify(int x,int l,int r,int L,int R,int d){
    if(l == L && r == R) {cover(x,d);return;}
    int mid = (l + r) >> 1;pushdown(x);
    if(R <= mid) modify(lc,l,mid,L,R,d);
    else if(L > mid) modify(rc,mid+1,r,L,R,d);
    else modify(lc,l,mid,L,mid,d),modify(rc,mid+1,r,mid+1,R,d);
    mx[x] = std::max(mx[lc],mx[rc]);
}

inline int query(int x,int l,int r,int L,int R){
    if(l == L && r == R) return mx[x];
    int mid = (l + r) >> 1;pushdown(x);
    if(R <= mid) return query(lc,l,mid,L,R);
    if(L > mid) return query(rc,mid+1,r,L,R);
    return std::max(query(lc,l,mid,L,mid),query(rc,mid+1,r,mid+1,R));
}

std::vector<int> G[MAXN];
int n,m,las[MAXN];
int a[MAXN];
int L[MAXN],R[MAXN];
int nxt[MAXN];

inline void dfs(int v){
    for(auto x:G[v]){
        dfs(x);
        L[v] = std::min(L[v],L[x]);
        R[v] = std::max(R[v],R[x]);
    }
}

std::vector<P> q[MAXN];
int ans[MAXN];

int main(){
#ifndef RainAir
    freopen("exchange.in","r",stdin);
    freopen("exchange.out","w",stdout);
#endif
    read(n);read(m);
    FOR(i,1,n) read(a[i]);
    nxt[n+1] = n+1;a[n+1] = 1e9;
    ROF(i,n,1){
        nxt[i] = i+1;
        while(a[i] >= a[nxt[i]]) nxt[i] = nxt[nxt[i]];
    }
    FOR(i,1,m){
        int l,r;read(l);read(r);
        q[r].pb(MP(l,i));
    }
    FOR(i,1,n) G[nxt[i]].pb(i);
    FOR(i,1,n+1) L[i] = R[i] = i;
    dfs(n+1);
    FOR(i,1,n){
        modify(1,1,n,L[i],R[i],1);
        for(auto x:q[i]){
            ans[x.se] = query(1,1,n,x.fi,i);
        }
    }
    FOR(i,1,m) printf("%d\n",ans[i]);
    return 0;
}
