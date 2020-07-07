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

const int MAXN = 2e5 + 5;
LL sm[MAXN<<2];
int mx[MAXN<<2];
#define lc ((x)<<1)
#define rc ((x)<<1|1)

inline LL calc(int x,int l,int r,int d){
    if(l == r) return std::max(d,mx[x]);
    int mid = (l + r) >> 1;
    if(mx[lc] <= d) return 1ll*(mid-l+1)*d+calc(rc,mid+1,r,d);
    return calc(lc,l,mid,d)+sm[x]-sm[lc];
}

inline void pushup(int x,int l,int r){
    mx[x] = std::max(mx[lc],mx[rc]);
    int mid = (l + r) >> 1;
    sm[x] = sm[lc]+calc(rc,mid+1,r,mx[lc]);
}

inline void update(int x,int l,int r,int p,int d){
    if(l == r) {mx[x] = sm[x] = d;return;}
    int mid = (l + r) >> 1;
    if(p <= mid) update(lc,l,mid,p,d);
    else update(rc,mid+1,r,p,d);
    pushup(x,l,r);
}

int a[MAXN],n;
std::set<int> S[MAXN];

inline int pre(int x){
    auto p = S[a[x]].find(x);
    if(p == S[a[x]].begin()) return 0;--p;
    return *p;
}

inline int suf(int x){
    auto p = S[a[x]].find(x);++p;
    if(p == S[a[x]].end()) return 1e9;
    return *p;
}

int main(){
    scanf("%d",&n);
    FOR(i,1,n) scanf("%d",a+i),S[a[i]].insert(i);
    FOR(i,1,n) update(1,1,n,i,pre(i));int q;scanf("%d",&q);
    FOR(i,1,q){
        int opt;scanf("%d",&opt);
        if(opt == 0){
            printf("%lld\n",1ll*n*(n+1)/2-sm[1]);
        }
        else{
            int x,d;scanf("%d%d",&x,&d);
            int sf = suf(x),pr = pre(x);
            if(sf != 1e9) update(1,1,n,sf,pr);
            S[a[x]].erase(x);
            a[x] = d;
            S[a[x]].insert(x);
            sf = suf(x),pr = pre(x);
            if(sf != 1e9) update(1,1,n,sf,x);
            update(1,1,n,x,pr);
        }
    }
    return 0;
}
