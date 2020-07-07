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

const int MAXN = 4e5 + 5;

struct Node{
    int opt,x,y,id;
    Node(int opt=0,int x=0,int y=0,int id=0) : opt(opt),x(x),y(y),id(id) {}

    bool operator < (const Node &t) const {
        return id < t.id;
    }
}a[MAXN];
int q,n;

int now = 0;
int sm[MAXN<<2],mn[MAXN<<2],ts[MAXN<<2];
#define lc ((x)<<1)
#define rc ((x)<<1|1)

inline void jzm(int x){
    if(ts[x] != now) mn[x] = 1e9,ts[x] = now;
}

inline void build(int x,int l,int r,int d=0){
    mn[x] = 1e9;
    sm[x] = (r-l+1)*d;
    if(l == r) return;
    int mid = (l + r) >> 1;
    build(lc,l,mid,d);build(rc,mid+1,r,d);
    sm[x] = sm[lc]+sm[rc];
}

inline void update(int x,int l,int r,int pos,int d){
    jzm(x);jzm(lc);jzm(rc);
    if(l == r) {sm[x] = mn[x] = d;return;}
    int mid = (l + r) >> 1;
    if(pos <= mid) update(lc,l,mid,pos,d);
    else update(rc,mid+1,r,pos,d);
    sm[x] = sm[lc]+sm[rc];
    mn[x] = std::min(mn[lc],mn[rc]);
}

inline int query(int x,int l,int r,int L,int R){
    if(L > R) return 1e9;
    jzm(x);jzm(lc);jzm(rc);
    if(l == L && R == r) return mn[x];
    int mid = (l + r) >> 1;
    if(R <= mid) return query(lc,l,mid,L,R);
    if(L > mid) return query(rc,mid+1,r,L,R);
    return std::min(query(lc,l,mid,L,mid),query(rc,mid+1,r,mid+1,R));
}

inline int find(int x,int l,int r,int k){
    if(l == r) return l;
    int mid = (l + r) >> 1;
    if(k <= sm[lc]) return find(lc,l,mid,k);
    else return find(rc,mid+1,r,k-sm[lc]);
}

int ans[MAXN];
std::set<int> S[MAXN];

inline void work(int l,int r,int L,int R){
    if(L > R) return;
    if(l == r){
        FOR(i,L,R) if(a[i].opt == 2) ans[a[i].id] = l;
        return;
    }
    int mid = (l + r) >> 1;now++;
    std::vector<Node> toL,toR;
    bool flag = 0;
    FOR(i,L,R) flag |= a[i].opt==2;
    FOR(i,l,mid) S[i].clear(),S[i].insert(0),S[i].insert(n+i),update(1,0,2*n,n+i,0);
    FOR(i,L,R){
        if(a[i].opt == 1){
            if(a[i].x <= mid) toL.pb(a[i]);
            else toR.pb(a[i]);
            if(a[i].x <= mid){
                auto p = S[a[i].x].insert(a[i].y).fi;
                ++p;
                if(p != S[a[i].x].end()){
                    update(1,0,2*n,*p,a[i].y);
                }
                --p;
                if(p == S[a[i].x].begin()) update(1,0,2*n,a[i].y,0);
                else{
                    --p;
                    update(1,0,2*n,a[i].y,*p);
                }
            }
        }
        if(a[i].opt == 2){
            int t = query(1,0,2*n,a[i].y+1,2*n);
            if(t < a[i].x) toL.pb(a[i]);
            else toR.pb(a[i]);
        }
    }
    int tot = L-1,ps;
    for(auto x:toL) a[++tot] = x;
    ps = tot;
    for(auto x:toR) a[++tot] = x;
    work(l,mid,L,ps);
    work(mid+1,r,ps+1,R);
}

int main(){
    scanf("%d",&q);
    FOR(i,1,q) scanf("%d%d%d",&a[i].opt,&a[i].x,&a[i].y),n += (a[i].opt == 1),a[i].id = i;
    build(1,1,n,1);
    ROF(i,q,1){
        if(a[i].opt == 1){
            int p = find(1,1,n,a[i].y+1);
            update(1,1,n,p,0);
            a[i].y = p;
        }
        else{
            a[i].x = find(1,1,n,a[i].x);
            a[i].y = find(1,1,n,a[i].y);
        }
    }
    work(1,n+1,1,q);
    std::sort(a+1,a+q+1);
    FOR(i,1,q) if(a[i].opt == 2) printf("%d\n",ans[i]);
    return 0;
}
