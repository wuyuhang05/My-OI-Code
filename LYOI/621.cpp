#include <algorithm>
#include <iostream>
#include <cstring>
#include <climits>
#include <cstdio>
#include <vector>
#include <cstdlib>
#include <ctime>
#include <cmath>
#include <queue>
#include <stack>
#include <map>
#include <set>

#define Re register
#define LL long long
#define U unsigned
#define FOR(i,a,b) for(Re int i = a;i <= b;++i)
#define ROF(i,a,b) for(Re int i = a;i >= b;--i)
#define SFOR(i,a,b,c) for(Re int i = a;i <= b;i+=c)
#define SROF(i,a,b,c) for(Re int i = a;i >= b;i-=c)
#define CLR(i,a) memset(i,a,sizeof(i))
#define BR printf("--------------------\n")
#define DEBUG(x) std::cerr << #x << '=' << x << std::endl
#define int LL
const int MAXN = 2e5 + 10;

struct Query{
    int pos,x,y;

    bool operator < (const Query &t) const {
        return x*t.y < t.x*y;
    }
}q[MAXN];
int x1[MAXN],x2[MAXN],yy1[MAXN],yy2[MAXN],Q,cnt;
int id[MAXN];

struct SegmentTree{
    #define lc (x<<1)
    #define rc (x<<1|1)
    struct Node{
        int dis,id;
    }t[MAXN];

    Node upd(const Node &a,const Node &b){
        return a.dis == b.dis ? (a.id > b.id ? a : b) : (a.dis < b.dis ? a : b);
    }

    inline void build(int x,int l,int r){
        t[x] = (Node){INT_MAX,0};
        if(l == r) return;
        int mid = (l + r) >> 1;
        build(lc,l,mid);build(rc,mid+1,r);
    }

    inline void modify(int x,int l,int r,int L,int R,const Node &d){
        // DEBUG(l);DEBUG(r);DEBUG(L);DEBUG(R);DEBUG(x);getchar();
        if(l == L && r == R){
            t[x] = upd(t[x],d);
            return;
        }
        int mid = (l + r) >> 1;
        if(R <= mid) modify(lc,l,mid,L,R,d);
        else if(L > mid) modify(rc,mid+1,r,L,R,d);
        else modify(lc,l,mid,L,mid,d),modify(rc,mid+1,r,mid+1,R,d);
    }

    Node query(int x,int l,int r,int pos){
        if(l == r) return t[x];
        int mid = (l + r) >> 1;
        Node tn = pos <= mid ? query(lc,l,mid,pos) : query(rc,mid+1,r,pos);
        return upd(tn,t[x]);
    }
}T1,T2;

LL calc1(int x,int y){
    int L = 1,R = cnt,ans = cnt+1;
    while(L <= R){
        int mid = (L + R) >> 1;
        if(y*q[mid].x >= x*q[mid].y) ans = mid,R = mid - 1;
        else L = mid + 1;
    }
    return ans;
}

LL calc2(int x,int y){
    int L = 1,R = cnt,ans = 0;
    while(L <= R){
        int mid = (L + R) >> 1;
        if(y*q[mid].x <= x*q[mid].y) ans = mid,L = mid+1;
        else R = mid-1;
    }
    return ans;
}

SegmentTree::Node ans1[MAXN],ans2[MAXN];

signed main(){
    scanf("%lld",&Q);
    FOR(i,1,Q){
        int opt;scanf("%lld",&opt);
        if(opt & 1) scanf("%lld%lld%lld%lld",x1+i,yy1+i,x2+i,yy2+i);
        else q[++cnt].pos = i,scanf("%lld%lld",&q[cnt].x,&q[cnt].y);
    }
    std::sort(q+1,q+cnt+1);FOR(i,1,cnt) id[q[i].pos] = i;
    T1.build(1,1,cnt);T2.build(1,1,cnt);
    FOR(i,1,Q){
        if(id[i]){
            ans1[i] = T1.query(1,1,cnt,id[i]);
            ans2[i] = T2.query(1,1,cnt,id[i]);
            //DEBUG(ans1[i].id);DEBUG(ans2[i].id);
        }
        else{
            int l = calc1(x1[i],yy2[i]),r = calc2(x1[i],yy1[i]);
            //DEBUG(l);DEBUG(r);
            if(l <= r) T1.modify(1,1,cnt,l,r,(SegmentTree::Node){x1[i],i});
            l = calc1(x1[i],yy1[i]),r = calc2(x2[i],yy1[i]);
            if(l <= r) T2.modify(1,1,cnt,l,r,(SegmentTree::Node){yy1[i],i});
        }
    }
    FOR(i,1,Q){
        if(id[i]){
            LL d1 = ans1[i].dis*q[id[i]].y,d2 = ans2[i].dis*q[id[i]].x,ans;
            if(!q[id[i]].y){
                printf("%lld\n",ans1[i].id);
                continue;
            }
            if(!q[id[i]].x){
                printf("%lld\n",ans2[i].id);
                continue;
            }
            if(d1 == d2) ans = std::max(ans1[i].id,ans2[i].id);
            else ans = d1 < d2 ? ans1[i].id : ans2[i].id;
            printf("%lld\n",ans);
        }
    }
    return 0;
}
/*
10
1 3 3 10 4 
1 4 2 5 6 
2 6 2
1 2 8 4 10 
1 0 6 3 9 
2 5 2 
2 8 6 
2 2 9 
2 4 7
1 5 7 10 10
*/