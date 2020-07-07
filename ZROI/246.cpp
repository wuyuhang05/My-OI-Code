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
#define int LL
const int MAXN = 2e6 + 5;

int lc[MAXN<<2],rc[MAXN<<2],cnt0[MAXN<<2],cnt1[MAXN<<2],cov[MAXN<<2],tag[MAXN<<2];
int rt;

inline void pushup(int x,int l,int r){
    cnt0[x] = cnt1[x] = 0;
    if(l == r){
        if(cov[x]){
            if(__builtin_popcount(l)&1) cnt1[x] = 1;
            else cnt0[x] = 1;
        }
    }
    else{
        if(cov[x]){
            cnt1[x] = cnt0[x] = (r-l+1)/2;
        }
        else{
            cnt1[x] = cnt1[lc[x]]+cnt1[rc[x]];
            cnt0[x] = cnt0[lc[x]]+cnt0[rc[x]];
        }
    }
}
int tot;
inline void modify(int &x,int l,int r,int L,int R,int d){
    if(!x) x = ++tot;
    if(l == L && r == R){
        cov[x] += d;
        pushup(x,l,r);
        return;
    }
    int mid = (l + r) >> 1;
    if(R <= mid) modify(lc[x],l,mid,L,R,d);
    else if(L > mid) modify(rc[x],mid+1,r,L,R,d);
    else modify(lc[x],l,mid,L,mid,d),modify(rc[x],mid+1,r,mid+1,R,d);
    pushup(x,l,r);
}

int n;

signed main(){
    scanf("%lld",&n);
    FOR(i,1,n){
        int l,r;scanf("%lld%lld",&l,&r);
        modify(rt,0,(1ll<<32)-1,l,r,1);
        printf("%lld\n",1ll*cnt0[1]*cnt1[1]);
    }
    return 0;
}
