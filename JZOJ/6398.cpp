/*
 * Author: RainAir
 * Time: 2019-11-01 15:36:47
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
const int MAXN = 2e5 + 5;
int n,q;
int p[MAXN];

struct Node{
    int opt,l,r,d,id,ts;
    // id:输入的位置
    // ans: 影响
    // ts: 插入的时间
    bool operator < (const Node &t) const {
        return id < t.id;
    }
}a[MAXN],tmp[MAXN];

struct SegmentTree{
    #define lc ((x)<<1)
    #define rc ((x)<<1|1)
    int sm[MAXN<<2],tag[MAXN<<2];

    inline void pushup(int x){
        sm[x] = sm[lc] + sm[rc];
    }

    inline void cover(int x,int l,int r,int d){
        sm[x] += (r-l+1)*d;
        tag[x] += d;
    }

    inline void pushdown(int x,int l,int r){
        if(tag[x]){
            int mid = (l + r) >> 1;
            cover(lc,l,mid,tag[x]);
            cover(rc,mid+1,r,tag[x]);
            tag[x] = 0;
        }
    }

    inline void modify(int x,int l,int r,int L,int R,int d){
        if(l == L && r == R){
            cover(x,l,r,d);
            return;
        }
        int mid = (l + r) >> 1;
        pushdown(x,l,r);
        if(R <= mid) modify(lc,l,mid,L,R,d);
        else if(L > mid) modify(rc,mid+1,r,L,R,d);
        else modify(lc,l,mid,L,mid,d),modify(rc,mid+1,r,mid+1,R,d);
        pushup(x);
    }

    inline int query(int x,int l,int r,int L,int R){
        if(l == L && r == R) return sm[x];
        int mid = (l + r) >> 1;
        pushdown(x,l,r);
        if(R <= mid) return query(lc,l,mid,L,R);
        if(L > mid) return query(rc,mid+1,r,L,R);
        return query(lc,l,mid,L,mid)+query(rc,mid+1,r,mid+1,R);
    }
}seg;
// seg1: 修改
// seg2: 查询

int ans[MAXN];

struct Opt{
    int l,r,d;
    Opt(int l=0,int r=0,int d=0) : l(l),r(r),d(d) {}
};

inline void work1(int l,int r){ // 统计修改的影响(询问->修改)
    if(l == r){
        return;
    }
    int mid = (l + r) >> 1;
    work1(l,mid);work1(mid+1,r);
    std::vector<Opt> del;
    int p1 = l,p2 = mid+1,sz = l-1;
    while(p1 <= mid && p2 <= r){
        if(a[p1].ts < a[p2].ts){
            tmp[++sz] = a[p1];
            if(a[p1].opt == 2) seg.modify(1,1,n,a[p1].l,a[p1].r,1),del.pb(Opt(a[p1].l,a[p1].r,1));
            ++p1;
        }
        else{
            tmp[++sz] = a[p2];
            if(a[p2].opt == 1){
                ans[a[p2].ts] += seg.query(1,1,n,a[p2].l,a[p2].r)*a[p2].d;
            }p2++;
        }
    }
    FOR(i,p1,mid) tmp[++sz] = a[i];
    FOR(i,p2,r){
        tmp[++sz] = a[i];
        if(a[i].opt == 1) ans[a[i].ts] += seg.query(1,1,n,a[i].l,a[i].r)*a[i].d;
    }
    FOR(i,l,r) a[i] = tmp[i];
    FOR(i,0,(int)del.size()-1) seg.modify(1,1,n,del[i].l,del[i].r,-del[i].d);
    del.clear();
}

inline void work2(int l,int r){ // 统计询问的影响(修改->询问)
    if(l == r){
        return;
    }
    int mid = (l + r) >> 1;
    work2(l,mid);work2(mid+1,r);
    int p1 = l,p2 = mid+1,sz = l-1;
    std::vector<Opt> del;
    while(p1 <= mid && p2 <= r){
        if(a[p1].ts < a[p2].ts){
            if(a[p1].opt == 1){
                seg.modify(1,1,n,a[p1].l,a[p1].r,a[p1].d);
                del.pb(Opt(a[p1].l,a[p1].r,a[p1].d));
            }
            tmp[++sz] = a[p1];
            p1++;
        }
        else{
            if(a[p2].opt == 2){
                ans[a[p2].ts] += seg.query(1,1,n,a[p2].l,a[p2].r);
            }
            tmp[++sz] = a[p2];
            p2++;
        }
    }
    FOR(i,p1,mid) tmp[++sz] = a[i];
    FOR(i,p2,r){
        tmp[++sz] = a[i];
        if(a[i].opt == 2) ans[a[i].ts] += seg.query(1,1,n,a[i].l,a[i].r);
    }
    FOR(i,l,r) a[i] = tmp[i];
    FOR(i,0,(int)del.size()-1) seg.modify(1,1,n,del[i].l,del[i].r,-del[i].d);
    del.clear();
}

signed main(){
    freopen("generator.in","r",stdin);
    freopen("generator.out","w",stdout);
//    freopen("3.in","r",stdin);
//    freopen("3.out","w",stdout);
    scanf("%lld%lld",&n,&q);
    FOR(i,2,q){
        scanf("%lld",p+i);
        a[p[i]].ts = i;
    }
    FOR(i,1,q){
        scanf("%lld%lld%lld",&a[i].opt,&a[i].l,&a[i].r);
        if(a[i].opt == 1) scanf("%lld",&a[i].d);
        a[i].id = i;
        if(!a[i].ts) a[i].ts = 1;
    }
    std::reverse(a+1,a+q+1);
    work1(1,q);
    std::sort(a+1,a+q+1);
    work2(1,q);
    FOR(i,2,q) ans[i] += ans[i-1];
    FOR(i,1,q) printf("%lld\n",ans[i]);
    return 0;
}
