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
const int MAXN = 1e5 + 5;

int k[MAXN<<2],b[MAXN<<2];
bool flag[MAXN<<2];
#define lc ((x)<<1)
#define rc ((x)<<1|1)

inline void update(int x,int l,int r,int K,int B){
    if(!flag[x]){
        k[x] = K;b[x] = B;flag[x] = 1;return;
    }
    int mid = (l + r) >> 1;
    int l1 = K*l+B,r1 = K*r+B,l2 = k[x]*l+b[x],r2 = k[x]*r+b[x];
    if(l1 >= l2 && r1 >= r2) return;
    if(l1 < l2 && r1 < r2){
        k[x] = K;b[x] = B;return;
    }
    double ps = (b[x]-B)/(K-k[x]);
    if(l1 < l2){
        if(ps > mid) update(rc,mid+1,r,k[x],b[x]),k[x] = K,b[x] = B;
        else update(lc,l,mid,K,B);
    }
    else{
        if(ps <= mid) update(lc,l,mid,k[x],b[x]),k[x] = K,b[x] = B;
        else update(rc,mid+1,r,K,B);
    }
}

inline int query(int x,int l,int r,int p){
    if(!flag[x]) return 1e18;
    int t = k[x]*p+b[x];
    if(l == r) return t;
    int mid = (l + r) >> 1;
    if(p <= mid) return std::min(t,query(lc,l,mid,p));
    else return std::min(t,query(rc,mid+1,r,p));
}
int w[MAXN],h[MAXN],f[MAXN],pre[MAXN];
int n,m;
signed main(){
    // DEBUG(1);
    scanf("%lld",&n);
    FOR(i,1,n) scanf("%lld",h+i),m = std::max(m,h[i]);
    FOR(i,1,n) scanf("%lld",pre+i),pre[i] += pre[i-1];
    f[1] = 0;update(1,0,m,-2*h[1],h[1]*h[1]+f[1]-pre[1]);
    FOR(i,2,n){
        // DEBUG(query(1,0,m,h[i]));
        f[i] = pre[i-1]+h[i]*h[i]+query(1,0,m,h[i]);
        update(1,0,m,-2*h[i],h[i]*h[i]+f[i]-pre[i]);
    }
    // FOR(i,1,n) DEBUG(f[i]);
    printf("%lld\n",f[n]);
    return 0;
}
/*
C = pre[i-1]+h[i]^2
F[i] = h[j]^2+f[j]-pre[j]
f[i] = (hi-hj)^2+fj+pre[i-1]-prej
=hi^2+hj^2-2hihj+fj+pre[i-1]-prej
=-2hihj+F[j]+C
*/