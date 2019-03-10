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

#define int LL
#define fi first
#define lc (x<<1)
#define se second
#define U unsigned
#define rc (x<<1|1)
#define Re register
#define LL long long
#define MP std::make_pair
#define CLR(i,a) memset(i,a,sizeof(i))
#define FOR(i,a,b) for(Re int i = a;i <= b;++i)
#define ROF(i,a,b) for(Re int i = a;i >= b;--i)
#define SFOR(i,a,b,c) for(Re int i = a;i <= b;i+=c)
#define SROF(i,a,b,c) for(Re int i = a;i >= b;i-=c)
#define DEBUG(x) std::cerr << #x << '=' << x << std::endl

const int MAXN = 50000+5;
int a[MAXN],tag[MAXN],bel[MAXN],sum[MAXN];
int n,blo;

inline void modify(int l,int r,int c){
    if(bel[l] == bel[r]){
        FOR(i,l,r) a[i] += c,sum[bel[i]] += c;
        return;
    }
    FOR(i,l,bel[l]*blo) a[i] += c,sum[bel[i]] += c;
    FOR(i,bel[l]+1,bel[r]-1) tag[i] += c;
    FOR(i,(bel[r]-1)*blo+1,r) a[i] += c,sum[bel[i]] += c;
}

inline int query(int l,int r){
    int res = 0;
    if(bel[l] == bel[r]){
        FOR(i,l,r) res += a[i]+tag[bel[i]];
        return res;
    }
    FOR(i,l,bel[l]*blo) res += a[i]+tag[bel[i]];
    FOR(i,bel[l]+1,bel[r]-1) res += sum[i]+tag[i]*blo;
    FOR(i,(bel[r]-1)*blo+1,r) res += a[i]+tag[bel[i]];
    return res;
}

signed main(){
    scanf("%lld",&n);blo = std::sqrt(n);
    FOR(i,1,n) scanf("%lld",a+i);
    FOR(i,1,n) bel[i] = (i-1)/blo + 1;
    FOR(i,1,n) sum[bel[i]] += a[i];
    FOR(i,1,n){
        int opt,l,r,c;
        scanf("%lld%lld%lld%lld",&opt,&l,&r,&c);
        if(!opt) modify(l,r,c);
        else printf("%lld\n",query(l,r)%(c+1));
    }
    return 0;
}