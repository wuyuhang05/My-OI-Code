/*
 * Author: RainAir
 * Time: 2019-11-02 16:56:49
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

struct DS{
    #define lc ((x)<<1)
    #define rc ((x)<<1|1)
    int a[MAXN<<2],b[MAXN<<2],ans[MAXN<<2];

    inline void pushup(int x){
        int t = std::min(a[lc],b[rc]);
        a[x] = a[lc] + a[rc] - t;
        b[x] = b[lc] + b[rc] - t;
        ans[x] = ans[lc] + ans[rc] + t;
    }

    inline void update1(int x,int l,int r,int ps,int d){
        if(l == r){
            a[x] += d;
            return;
        }
        int mid = (l + r) >> 1;
        if(ps <= mid) update1(lc,l,mid,ps,d);
        else update1(rc,mid+1,r,ps,d);
        pushup(x);
    }

    inline void update2(int x,int l,int r,int ps,int d){
        if(l == r){
            b[x] += d;
            return;
        }
        int mid = (l + r) >> 1;
        if(ps <= mid) update2(lc,l,mid,ps,d);
        else update2(rc,mid+1,r,ps,d);
        pushup(x);
    }

    inline int query(int x,int l,int r,int L,int R){
        if(l == L && r == R) return ans[x];
        int mid = (l + r) >> 1;
        if(R <= mid) return query(lc,l,mid,L,R);
        if(L > mid) return query(rc,mid+1,r,L,R);
        return query(lc,l,mid,L,mid) + query(rc,mid+1,r,mid+1,R);
    }
}seg;

int n,a[MAXN],b[MAXN],N,base;
int ans[MAXN];
std::multiset<int> S;

inline int calc(int l,int r,int add){
    int ans = -1;
    while(l <= r){
        int mid = (l + r) >> 1;
        if(S.lower_bound(mid) == S.end()){
            r = mid-1;
            continue;
        }
        int v = *S.lower_bound(mid);
        seg.update2(1,1,N,v,-1);
        if(seg.query(1,1,N,1,N)+add == base) ans = mid,l = mid+1;
        else r = mid-1;
        seg.update2(1,1,N,v,1);
    }
    return ans;
}

int main(){
    freopen("game.in","r",stdin);
    freopen("game.out","w",stdout);
    scanf("%d",&n);
    FOR(i,1,n) scanf("%d",a+i),N = std::max(N,a[i]);
    FOR(i,1,n) scanf("%d",b+i),N = std::max(N,b[i]);
    FOR(i,1,n) seg.update1(1,1,N,a[i],1),seg.update2(1,1,N,b[i],1);
    base = seg.query(1,1,N,1,N);
    FOR(i,1,n) S.insert(b[i]);
    FOR(i,1,n){
        seg.update1(1,1,N,a[i],-1);
        int ps = calc(a[i]+1,N,1);
        if(ps != -1) --base;
        else ps = calc(1,a[i],0);
        seg.update2(1,1,N,ps,-1);
        printf("%d ",ps);
        S.erase(S.find(ps));
    }
    puts("");
    return 0;
}
