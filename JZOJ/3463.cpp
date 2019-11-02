/*
 * Author: RainAir
 * Time: 2019-10-30 16:01:20
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

const int MAXN = 1e5 + 5;

int mn[MAXN<<2],tag[MAXN<<2];
#define lc ((x)<<1)
#define rc ((x)<<1|1)

inline void pushup(int x){
    mn[x] = std::min(mn[lc],mn[rc]);
}

inline void cover(int x,int d){
    mn[x] += d;
    tag[x] += d;
}

inline void pushdown(int x){
    if(tag[x]){
        cover(lc,tag[x]);
        cover(rc,tag[x]);
        tag[x] = 0;
    }
}

inline void build(int x,int l,int r){
    tag[x] = mn[x] = 0;
    if(l == r) return;
    int mid = (l + r) >> 1;
    build(lc,l,mid);build(rc,mid+1,r);
}

inline void modify(int x,int l,int r,int L,int R,int d){
    if(L > R) return;
    if(l == L && r == R){
        cover(x,d);
        return;
    }
    int mid = (l + r) >> 1;
    pushdown(x);
    if(R <= mid) modify(lc,l,mid,L,R,d);
    else if(L > mid) modify(rc,mid+1,r,L,R,d);
    else modify(lc,l,mid,L,mid,d),modify(rc,mid+1,r,mid+1,R,d);
    pushup(x);
}

inline int query(int x,int l,int r,int L,int R){
    if(L > R) return 1e9;
    if(l > r) return 1e9;
    if(l == L && r == R) return mn[x];
    int mid = (l + r) >> 1;
    pushdown(x);
    if(R <= mid) return query(lc,l,mid,L,R);
    if(L > mid) return query(rc,mid+1,r,L,R);
    return std::min(query(lc,l,mid,L,mid),query(rc,mid+1,r,mid+1,R));
}

int n,lim,h[MAXN],g[MAXN],sm[MAXN];

inline int calc(int R,int d){
    int l = 1,r = R,ans = R;
    while(l <= r){
        int mid = (l + r) >> 1;
        if(sm[R]-sm[mid] <= d) ans = mid,r = mid-1;
        else l = mid+1;
    }
    return ans;
}

int f[MAXN];

inline bool chk(int k){
    std::deque<int> q;
    f[1] = 0;q.pb(1);
    build(1,1,n+1);
    FOR(i,2,n+1){
        int ps = calc(i,k);
        while(!q.empty() && q.front() < ps) q.pop_front();
        while(!q.empty() && h[q.back()] <= h[i]){
            bool flag = q.size() == 1;
            if(flag) modify(1,1,n+1,1,q.back()-1,-h[q.back()]);
            else modify(1,1,n+1,q[q.size()-2],q.back()-1,-h[q.back()]);
            q.pop_back();
        }
        if(q.empty()) modify(1,1,n+1,1,i-1,h[i]);
        else modify(1,1,n+1,q.back(),i-1,h[i]);
        q.pb(i);
        f[i] = query(1,1,n+1,ps,i-1);
        modify(1,1,n+1,i,i,f[i]);
    }
    return f[n+1] <= lim;
}

int main(){
    scanf("%d%d",&n,&lim);
    FOR(i,2,n+1) scanf("%d%d",h+i,g+i),sm[i] = sm[i-1]+g[i];
    int l = 0,r = sm[n+1],ans = -1;
    while(l <= r){
        int mid = (l + r) >> 1;
        if(chk(mid)) ans = mid,r = mid-1;
        else l = mid+1;
    }
    printf("%d\n",ans);
    return 0;
}
