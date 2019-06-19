#include <algorithm>
#include <iostream>
#include <cstring>
#include <climits>
#include <cstdlib>
#include <cstdio>
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
#define Re register
#define LL long long
#define pb push_back
#define MP std::make_pair
#define all(x) x.begin(),x.end()
#define CLR(i,a) memset(i,a,sizeof(i))
#define FOR(i,a,b) for(Re int i = a;i <= b;++i)
#define ROF(i,a,b) for(Re int i = a;i >= b;--i)
#define DEBUG(x) std::cerr << #x << '=' << x << std::endl

const int MAXN = 200000+5;

int a[MAXN],pre[MAXN],f[MAXN][32][2],lc[MAXN<<5],rc[MAXN<<5],root[MAXN],tot;
LL sum[MAXN<<5],tag[MAXN<<5];

inline int calc(int x){
    ROF(i,30,0){
        if((1<<i)&x) return i;
    }
    return 0;
}

inline void update(int prev,int &x,int l,int r,int L,int R){
    x = ++tot;lc[x] = lc[prev];rc[x] = rc[prev];tag[x] = tag[prev];sum[x] = sum[prev]+R-L+1;
    if(l == L && r == R){
        tag[x]++;
        return;
    }
    int mid = (l + r) >> 1;
    if(R <= mid) update(lc[prev],lc[x],l,mid,L,R);
    else if(L > mid) update(rc[prev],rc[x],mid+1,r,L,R);
    else update(lc[prev],lc[x],l,mid,L,mid),update(rc[prev],rc[x],mid+1,r,mid+1,R);
}

inline LL query(int x,int y,int l,int r,int L,int R){
    if(L <= l && r <= R) return sum[y]-sum[x];
    int mid = (l + r) >> 1;LL ans = (tag[y]-tag[x])*(R-L+1);
    if(R <= mid) ans += query(lc[x],lc[y],l,mid,L,R);
    else if(L > mid) ans += query(rc[x],rc[y],mid+1,r,L,R);
    else ans += query(lc[x],lc[y],l,mid,L,mid) + query(rc[x],rc[y],mid+1,r,mid+1,R);
    return ans;
}

inline bool chk(int l,int r){
    FOR(i,0,30)
        if(f[r][i][(pre[l-1]>>i)&1] > f[l-1][i][(pre[l-1]>>i)&1]) return false;
    return true;
}

int n,m;LL la;

int main(){
    scanf("%d",&n);
    FOR(i,1,n){
        scanf("%d",a+i),pre[i] = pre[i-1]^a[i];
        FOR(j,0,30) f[i][j][0] = f[i-1][j][0],f[i][j][1] = f[i-1][j][1];
        if(a[i]) f[i][calc(a[i])][(pre[i]>>calc(a[i]))&1]++;
    }
    FOR(i,1,n){
        int l = i,r = n;
        while(l < r){
            int mid = (l + r) >> 1;
            if(chk(i,mid+1)) l = mid+1;
            else r = mid;
        }
        update(root[i-1],root[i],1,n,i,l);
    }
    scanf("%d",&m);
    FOR(i,1,m){
        int l,r;scanf("%d%d",&l,&r);
        l = (l+la)%n+1,r = (r+la)%n+1;
        if(l > r) std::swap(l,r);
        printf("%lld\n",la = query(root[l-1],root[r],1,n,l,r));
    }
    return 0;
}
