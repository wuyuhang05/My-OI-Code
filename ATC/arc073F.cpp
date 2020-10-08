#include<bits/stdc++.h>

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

const int MAXN = 2e5 + 5;

#define lc ((x)<<1)
#define rc ((x)<<1|1)
LL mn[MAXN<<2],tag[MAXN<<2];
LL mn1[MAXN<<2],mn2[MAXN<<2];

inline void pushup(int x){
    mn[x] = std::min(mn[lc],mn[rc]);
    mn1[x] = std::min(mn1[lc],mn1[rc]);
    mn2[x] = std::min(mn2[lc],mn2[rc]);
}

inline void cover(int x,LL d){
    mn[x] += d;mn1[x] += d;mn2[x] += d;tag[x] += d;
}

inline void pushdown(int x){
    if(tag[x]){
        cover(lc,tag[x]);
        cover(rc,tag[x]);
        tag[x] = 0;
    }
}

inline void update(int x,int l,int r,int p,LL d){
    if(l == r){
        mn[x] = std::min(mn[x],d);
        mn1[x] = std::min(mn1[x],d+l);
        mn2[x] = std::min(mn2[x],d-l);
        return;
    }
    pushdown(x);
    int mid = (l + r) >> 1;
    if(p <= mid) update(lc,l,mid,p,d);
    else update(rc,mid+1,r,p,d);
    pushup(x);
}

inline void modify(int x,int l,int r,int L,int R,LL d){
    if(l == L && r == R) {cover(x,d);return;}
    int mid = (l + r) >> 1;pushdown(x);
    if(R <= mid) modify(lc,l,mid,L,R,d);
    else if(L > mid) modify(rc,mid+1,r,L,R,d);
    else modify(lc,l,mid,L,mid,d),modify(rc,mid+1,r,mid+1,R,d);
    pushup(x);
}

inline void build(int x,int l,int r){
    tag[x] = 0;
    if(l == r){
        mn[x] = 0;mn1[x] = l;mn2[x] = -l;return;
    }
    int mid = (l + r) >> 1;
    build(lc,l,mid);build(rc,mid+1,r);
    pushup(x);
}

inline LL query1(int x,int l,int r,int L,int R){
    if(L > R) return 1e18;
    if(l == L && r == R) return mn1[x];
    int mid = (l + r) >> 1;pushdown(x);
    if(R <= mid) return query1(lc,l,mid,L,R);
    if(L > mid) return query1(rc,mid+1,r,L,R);
    return std::min(query1(lc,l,mid,L,mid),query1(rc,mid+1,r,mid+1,R));
}

inline LL query2(int x,int l,int r,int L,int R){
    if(L > R) return 1e18;
    if(l == L && r == R) return mn2[x];
    int mid = (l + r) >> 1;pushdown(x);
    if(R <= mid) return query2(lc,l,mid,L,R);
    if(L > mid) return query2(rc,mid+1,r,L,R);
    return std::min(query2(lc,l,mid,L,mid),query2(rc,mid+1,r,mid+1,R));
}

int n,q,A,B;
int x[MAXN];

int main(){
    scanf("%d%d%d%d",&n,&q,&A,&B);
    FOR(i,1,q) scanf("%d",x+i);
    build(1,1,n);
    FOR(i,1,n) modify(1,1,n,i,i,std::min(std::abs(A-x[1])+std::abs(B-i),std::abs(B-x[1])+std::abs(A-i)));
    FOR(i,2,q){
        LL t = std::min(query1(1,1,n,x[i]+1,n)-x[i],query2(1,1,n,1,x[i])+x[i]);
        modify(1,1,n,1,n,std::abs(x[i]-x[i-1]));
        update(1,1,n,x[i-1],t);
    }
    printf("%lld\n",mn[1]);
    return 0;
}
/*
f[i][j] 表示处理了前 i 个操作 棋子分别在 x[i] 和 j 上
将 x[i-1] 移动到 x[i] 上
f[i][j] = f[i-1][j]+|x[i]-x[i-1]|
将 j 移动到 x[i] 上
f[i][x[i-1]] = min{ f[i-1][j]+|j-x[i]| }

线段树基本操作
*/
