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

const int MAXN = 2e5 + 5;
const int ha = 1e9 + 7;
const int inv2 = 500000004;
const int inv6 = 166666668;
const int inv24 = 41666667;
int n,a[MAXN];

#define lc ((x)<<1)
#define rc ((x)<<1|1)

inline int qpow(int a,int n=ha-2){
    int res = 1;
    while(n){
        if(n & 1) res = 1ll*res*a%ha;
        a = 1ll*a*a%ha;
        n >>= 1;
    }
    return res;
}

inline int binom(int n,int m){
    if(n < m) return 0;
    if(m == 2) return 1ll*n*(n-1)%ha*inv2%ha;
    if(m == 3) return 1ll*n*(n-1)%ha*(n-2)%ha*inv6%ha;
    if(m == 4) return 1ll*n*(n-1)%ha*(n-2)%ha*(n-3)%ha*inv24%ha;
    return 0;
}

struct Node{
    int l,r,sm,ls,rs,ans;
    Node(int l=0,int r=0,int sm=0,int ls=0,int rs=0,int ans=0) : l(l),r(r),sm(sm),ls(ls),rs(rs),ans(ans) {}

    inline Node operator + (const Node &t) const {
        Node res;
        res.sm = ((sm+t.sm)%ha+1ll*rs*t.ls%ha)%ha;
        res.ls = ls;res.rs = t.rs;
        if(ls == r-l+1) res.ls = (ls+t.ls)%ha;
        if(t.rs == t.r-t.l+1) res.rs = (t.rs+rs)%ha;
        int len = (rs+t.ls)%ha,cl = (sm+ha-1ll*rs*(rs+1)%ha*inv2%ha)%ha,cr = (t.sm+ha-1ll*t.ls*(t.ls+1)%ha*inv2%ha)%ha;
        (res.ans += (ans+t.ans)%ha) %= ha;
        (res.ans += 1ll*sm*t.sm%ha) %= ha;
        (res.ans += 1ll*(cl+cr)*rs%ha*t.ls%ha) %= ha;
        int de = (binom(rs,3)+binom(t.ls,3))%ha;de = (ha-de)%ha;
        (res.ans += (de+binom(len,3))%ha) %= ha;
        de = ((binom(rs,4)+binom(t.ls,4))%ha+1ll*binom(rs,2)*binom(t.ls,2)%ha)%ha;de = (ha-de)%ha;
        (res.ans += (de+binom(len,4))%ha)%=ha;
        // (res.ans += ((binom(len,4)+2ll*binom(len,3)%ha)%ha+binom(len,2))%ha)%=ha;
        res.l = l;res.r = t.r;
        // printf("%d %d %d %d %d %d\n",l,r,sm,ls,rs,ans);
        // printf("%d %d %d %d %d %d\n",t.l,t.r,t.sm,t.ls,t.rs,t.ans);
        // printf("%d %d %d %d %d %d\n",res.l,res.r,res.sm,res.ls,res.rs,res.ans);
        // puts("");
        return res;
    }
}sm[MAXN<<2];

inline void build(int x,int l,int r){
    sm[x] = Node(l,r,0,0,0,0);
    if(l == r) return;
    int mid = (l + r) >> 1;
    build(lc,l,mid);build(rc,mid+1,r);
}

inline void update(int x,int l,int r,int p){
    if(l == r){
        sm[x].ls = sm[x].rs = sm[x].sm = 1;return;
    }
    int mid = (l + r) >> 1;
    if(p <= mid) update(lc,l,mid,p);
    else update(rc,mid+1,r,p);
    sm[x] = sm[lc]+sm[rc];
}

std::vector<int> S,SS[MAXN];

int main(){
    // DEBUG(1);DEBUG(binom(1,4));DEBUG(binom(1,3));DEBUG(binom(1,2));
    scanf("%d",&n);
    FOR(i,1,n) scanf("%d",a+i),S.pb(a[i]);
    std::sort(all(S));S.erase(std::unique(all(S)),S.end());int MX = S.size();
    FOR(i,1,n) a[i] = std::lower_bound(all(S),a[i])-S.begin()+1,SS[a[i]].pb(i);
    int ans = 0;build(1,1,n);
    // update(1,1,n,1);update(1,1,n,2);update(1,1,n,3);update(1,1,n,4);
    // DEBUG(sm[1].ans);
    // exit(0);
    ROF(i,MX,1){
        for(auto x:SS[i]) update(1,1,n,x);
        int gx = sm[1].ans;//DEBUG(gx);
        gx = 1ll*gx*(i==1 ? S[0] : (S[i-1]-S[i-2]))%ha;
        (ans += gx) %= ha;
    }
    printf("%d\n",ans);
    return 0;
}
/*
5
8 10 4 9 1 
*/