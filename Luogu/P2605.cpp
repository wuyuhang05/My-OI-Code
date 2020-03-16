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
#define int LL
const int MAXN = 20000+5;

#define lc ((x)<<1)
#define rc ((x)<<1|1)
int mn[MAXN<<2],tag[MAXN<<2];
int f[2][MAXN],now;
int n,k;

inline void cover(int x,int d){
    mn[x] += d;tag[x] += d;
}

inline void pushdown(int x){
    if(tag[x]){
        cover(lc,tag[x]);
        cover(rc,tag[x]);
        tag[x] = 0;
    }
}

inline void modify(int x,int l,int r,int L,int R,int d){
//    L = std::max(L,1ll);R = std::min(R,n);
    if(L > R) return;
    if(l == L && r == R){
        cover(x,d);return;
    }
    int mid = (l + r) >> 1;
    pushdown(x);
    if(R <= mid) modify(lc,l,mid,L,R,d);
    else if(L > mid) modify(rc,mid+1,r,L,R,d);
    else modify(lc,l,mid,L,mid,d),modify(rc,mid+1,r,mid+1,R,d);
    mn[x] = std::min(mn[lc],mn[rc]);
}

inline int query(int x,int l,int r,int L,int R){
//    L = std::max(L,1ll);R = std::min(R,n);
    if(L > R) return 1e18;
    if(l == L && r == R) return mn[x];
    int mid = (l + r) >> 1;pushdown(x);
    if(R <= mid) return query(lc,l,mid,L,R);
    if(L > mid) return query(rc,mid+1,r,L,R);
    return std::min(query(lc,l,mid,L,mid),query(rc,mid+1,r,mid+1,R));
}

inline void build(int x,int l,int r){
    tag[x] = 0;
    if(l == r){
        mn[x] = f[now^1][l];return;
    }
    int mid = (l+r)>>1;
    build(lc,l,mid);build(rc,mid+1,r);
    mn[x] = std::min(mn[lc],mn[rc]);
}

int D[MAXN],C[MAXN],S[MAXN],W[MAXN];
int pre[MAXN],suf[MAXN];
std::vector<int> G[MAXN];

signed main(){
    scanf("%lld%lld",&n,&k);
    FOR(i,2,n) scanf("%lld",D+i);FOR(i,1,n) scanf("%lld",C+i);FOR(i,1,n) scanf("%lld",S+i);FOR(i,1,n) scanf("%lld",W+i);
    D[++n] = 1e18;++k;
    FOR(i,1,n){
        // D[p] >= -S[i]+D[i]
        int p = std::lower_bound(D+1,D+n+1,D[i]-S[i])-D;
        pre[i] = p;
        // D[p] <= S[i]+D[i]
        p = std::upper_bound(D+1,D+n+1,D[i]+S[i])-D;
        suf[i] = p-1;
        G[suf[i]].pb(i);
    }
    int ans = 0;
    FOR(i,1,n) ans += W[i];
    int sm = 0;
    FOR(i,1,n){
        f[now^1][i] = C[i]+sm;
        for(auto x:G[i]) sm += W[x];
//        DEBUG(f[now^1][i]);
    }
    FOR(j,2,k){
        CLR(f[now],0);build(1,1,n);
        FOR(i,1,j-1) for(auto x:G[i]) modify(1,1,n,1,pre[x]-1,W[x]);
        FOR(i,1,j-1) f[now][i] = 1e18;
        FOR(i,j,n){
            f[now][i] = query(1,1,n,1,i-1)+C[i];
            for(auto x:G[i]) modify(1,1,n,1,pre[x]-1,W[x]);
        }
  //      FOR(i,1,n) DEBUG(f[now][i]);
        ans = std::min(ans,f[now][n]);
        now ^= 1;
    }
    printf("%lld\n",ans);
    return 0;
}
/*
 * f[i][j]: 考虑前 i 个村庄 建了 j 个最后一个建在 i
 * f[i][j] = f[k][j-1]+cost(k+1,i-1)+C[i]
 * F[i] = min(G[j]+cost(j+1,i-1))+C[i]
 *  对于每一个点 i 预处理出他能覆盖的区间[pre[i],suf[i]]
 *   当 suf[j] < i 时 就 add(1,pre[j]-1,f[j])
 */
