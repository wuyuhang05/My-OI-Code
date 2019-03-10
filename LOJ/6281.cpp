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

const int MAXN = 100000+5;
int a[MAXN],bel[MAXN],flag[MAXN],sum[MAXN],n,blo;

inline void solve(int x){
    if(flag[x]) return;
    flag[x] = 1;sum[x] = 0;
    FOR(i,(x-1)*blo+1,x*blo){
        a[i] = std::sqrt(a[i]);
        sum[x] += a[i];
        if(a[i] > 1) flag[x] = 0;
    }
}

inline void modify(int l,int r){
    if(bel[l] == bel[r]){
        FOR(i,l,r){
            sum[bel[i]] -= a[i];
            a[i] = std::sqrt(a[i]);
            sum[bel[i]] += a[i];
        }
        return;
    }
    FOR(i,l,bel[l]*blo){
        sum[bel[i]] -= a[i];
        a[i] = std::sqrt(a[i]);
        sum[bel[i]] += a[i];
    }
    FOR(i,bel[l]+1,bel[r]-1) solve(i);
    FOR(i,(bel[r]-1)*blo+1,r){
        sum[bel[i]] -= a[i];
        a[i] = std::sqrt(a[i]);
        sum[bel[i]] += a[i];
    }
}

int query(int l,int r){
    int ans = 0;
    if(bel[l] == bel[r]){
        FOR(i,l,r) ans += a[i];
        return ans;
    }
    FOR(i,l,bel[l]*blo) ans += a[i];
    FOR(i,bel[l]+1,bel[r]-1) ans += sum[i];
    FOR(i,(bel[r]-1)*blo+1,r) ans += a[i];
    return ans;
}

signed main(){
    scanf("%lld",&n);blo = std::sqrt(n);
    FOR(i,1,n){
        scanf("%lld",a+i);
        sum[(bel[i] = (i-1)/blo + 1)] += a[i];
    }
    FOR(i,1,n){
        int opt,l,r,c;
        scanf("%lld%lld%lld%lld",&opt,&l,&r,&c);
        if(!opt) modify(l,r);
        else printf("%lld\n",query(l,r));
    }
    return 0;
}