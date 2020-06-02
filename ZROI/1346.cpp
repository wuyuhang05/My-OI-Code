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
#include <cassert>
const int MAXN = 5e5 + 5;

// 维护所有非 0 位置的信息
// 补集转换后维护所有 0 位置的信息

struct Node{
    int cnt,mn,sm;
    Node(int cnt=0,int mn=1e9,int sm=0) : cnt(cnt),mn(mn),sm(sm) {}

    friend Node operator + (const Node &x,const Node &y){
        Node res;res.mn = std::min(x.mn,y.mn);
        if(res.mn == x.mn){
            res.cnt += x.cnt;
            res.sm ^= x.sm;
        }
        if(res.mn == y.mn){
            res.cnt += y.cnt;
            res.sm ^= y.sm;
        }
        return res;
    }
}sm[MAXN<<5];
#define lc ((x)<<1)
#define rc ((x)<<1|1)
std::vector<int> S;
int tag[MAXN<<2];

#define lowbit(x) ((x)&(-(x)))

inline int sf(int n){
    return n^(n>>1);
}

inline void build(int x,int l,int r){
    if(l == r){
        sm[x].cnt = S[l-1]-((l-2<0)?0:S[l-2]);
        sm[x].mn = 0;
        sm[x].sm = sf(S[l-1])^sf((l-2<0)?0:S[l-2]);
        return;
    }
    int mid = (l + r) >> 1;
    build(lc,l,mid);build(rc,mid+1,r);
    sm[x] = sm[lc] + sm[rc];
}

inline void cover(int x,int d){
    sm[x].mn += d;tag[x] += d;
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
    sm[x] = sm[lc]+sm[rc];
}

inline Node query(int x,int l,int r,int L,int R){
    if(l == L && r == R) return sm[x];
    int mid = (l + r) >> 1;pushdown(x);
    if(R <= mid) return query(lc,l,mid,L,R);
    if(L > mid) return query(rc,mid+1,r,L,R);
    return query(lc,l,mid,L,mid)+query(rc,mid+1,r,mid+1,R);
}

int k,n;

struct _{
    int l,r,opt;
    _(int l=0,int r=0,int opt=0) : l(l),r(r),opt(opt) {}
};
std::vector<_> G[MAXN];
int X1[MAXN],Y1[MAXN],X2[MAXN],Y2[MAXN];

int main(){
//    freopen("ex_B2.in","r",stdin);
    scanf("%d%d%*d",&k,&n);
    FOR(i,1,k){
        scanf("%d%d%d%d",X1+i,Y1+i,X2+i,Y2+i);
        S.pb(Y1[i]);S.pb(Y2[i]);
        if(Y1[i] > 1) S.pb(Y1[i]-1);
        if(Y2[i] > 1) S.pb(Y2[i]-1);
    }
    FOR(i,1,n+1) S.pb(i);
    std::sort(all(S));S.erase(std::unique(all(S)),S.end());int m = S.size();build(1,1,m);
    FOR(i,1,k){
        Y1[i] = std::lower_bound(all(S),Y1[i])-S.begin()+1;
        Y2[i] = std::lower_bound(all(S),Y2[i])-S.begin()+1;
        G[X1[i]].pb(_(Y1[i],Y2[i],1));G[X2[i]].pb(_(Y1[i],Y2[i],-1));
    }
    int ans = 0;
    FOR(i,1,n){
        for(auto x:G[i]){
            if(x.opt == 1) modify(1,1,m,x.l,x.r,1);
        }
        // y <= x
        int p = std::upper_bound(all(S),i)-S.begin();
        Node t = query(1,1,m,1,i);int occ = i;
        if(t.mn == 0) occ -= t.cnt;
        if(occ&1) ans ^= lowbit(i);
        // y > x
        p++;t = query(1,1,m,i+1,m);int sm = sf(S[m-1])^sf(i);
        if(t.mn == 0) sm ^= t.sm;
        ans ^= sm;
        for(auto x:G[i]){
            if(x.opt == -1) modify(1,1,m,x.l,x.r,-1);
        }
    }
    printf("%d\n",ans);
    return 0;
}
