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

const int MAXN = 1e5 + 5;
const double EPS = 1e-10;
const double pi = acos(-1);

inline int sgn(double x){
    if(std::fabs(x) <= EPS) return 0;
    if(x > 0) return 1;
    return -1;
}

struct Node{
    double x,y;
    Node(double x=0,double y=0) : x(x),y(y) {}

    inline Node operator + (const Node &t) const {
        return Node(x+t.x,y+t.y);
    }

    inline Node operator - (const Node &t) const {
        return Node(x-t.x,y-t.y);
    }

    inline Node operator * (const Node &t) const {
        return Node(x*t.x-y*t.y,x*t.y+y*t.x);
    }

    inline Node operator * (const double &d) const {
        return Node(x*d,y*d);
    }

    inline bool operator == (const Node &t) const {
        return sgn(x-t.x) == 0 && sgn(y-t.y) == 0;
    }

    friend bool operator != (const Node &a,const Node &b){
        return !(a==b);
    }
}sm[MAXN<<2],tag[MAXN<<2],mul[MAXN<<2],a[MAXN];
#define lc ((x)<<1)
#define rc ((x)<<1|1)

inline void cover1(int x,int l,int r,Node d){
    sm[x] = sm[x]+d*(r-l+1);tag[x] = tag[x]+d;
}

inline void cover2(int x,Node d){
    sm[x] = sm[x]*d;mul[x] = mul[x]*d;tag[x] = tag[x]*d;
}

inline void pushdown(int x,int l,int r){
    int mid = (l + r) >> 1;
    if(mul[x] != Node(1,0)){
        cover2(lc,mul[x]);cover2(rc,mul[x]);
        mul[x] = Node(1,0);
    }
    if(tag[x] != Node(0,0)){
        cover1(lc,l,mid,tag[x]);cover1(rc,mid+1,r,tag[x]);
        tag[x] = Node(0,0);
    }
}

inline void build(int x,int l,int r){
    mul[x] = Node(1,0);
    if(l == r){sm[x] = a[l];return;}
    int mid = (l + r) >> 1;
    build(lc,l,mid);build(rc,mid+1,r);
    sm[x] = sm[lc]+sm[rc];
}

inline void modify1(int x,int l,int r,int L,int R,Node d){
    if(l == L && r == R){cover1(x,l,r,d);return;}
    int mid = (l + r) >> 1;pushdown(x,l,r);
    if(R <= mid) modify1(lc,l,mid,L,R,d);
    else if(L > mid) modify1(rc,mid+1,r,L,R,d);
    else modify1(lc,l,mid,L,mid,d),modify1(rc,mid+1,r,mid+1,R,d);
    sm[x] = sm[lc]+sm[rc];
}

inline void modify2(int x,int l,int r,int L,int R,Node d){
    if(l == L && r == R){cover2(x,d);return;}
    int mid = (l+r)>>1;pushdown(x,l,r);
    if(R <= mid) modify2(lc,l,mid,L,R,d);
    else if(L > mid) modify2(rc,mid+1,r,L,R,d);
    else modify2(lc,l,mid,L,mid,d),modify2(rc,mid+1,r,mid+1,R,d);
    sm[x] = sm[lc]+sm[rc];
}

inline Node query(int x,int l,int r,int L,int R){
    if(l == L && r == R) return sm[x];
    int mid = (l + r) >> 1;pushdown(x,l,r);
    if(R <= mid) return query(lc,l,mid,L,R);
    if(L > mid) return query(rc,mid+1,r,L,R);
    return query(lc,l,mid,L,mid)+query(rc,mid+1,r,mid+1,R);
}

Node ans[MAXN];

inline void fin(int x,int l,int r){
    if(l == r){
        ans[l] = sm[x];
        return;
    }
    int mid = (l + r) >> 1;pushdown(x,l,r);
    fin(lc,l,mid);fin(rc,mid+1,r);
}

int n,q;

int main(){
    scanf("%d%d",&n,&q);
    FOR(i,1,n) scanf("%lf%lf",&a[i].x,&a[i].y);
    build(1,1,n);
    FOR(i,1,q){
        int l,r;scanf("%d%d",&l,&r);
        Node t = query(1,1,n,l,r)*(1.0/(r-l+1));
        printf("%.10lf %.10lf\n",t.x,t.y);
        modify1(1,1,n,l,r,t*(-1));
        modify2(1,1,n,l,r,Node(cos(pi/3),sin(pi/3)));
        modify1(1,1,n,l,r,t);
    }
    fin(1,1,n);
    FOR(i,1,n) printf("%.10lf %.10lf\n",ans[i].x,ans[i].y);
    return 0;
}
