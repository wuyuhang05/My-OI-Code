/*
 * Author: RainAir
 * Time: 2019-07-25 15:30:44
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
#define P std::pair<LL,LL>
#define Re register
#define LL long long
#define pb push_back
#define MP std::make_pair
#define all(x) x.begin(),x.end()
#define CLR(i,a) memset(i,a,sizeof(i))
#define FOR(i,a,b) for(Re int i = a;i <= b;++i)
#define ROF(i,a,b) for(Re int i = a;i >= b;--i)
#define DEBUG(x) std::cerr << #x << '=' << x << std::endl
#define int LL

const int MAXN = 1e6 + 10;
int n,m,p,q;
int f[MAXN];
int ans[MAXN];

inline int find(int x){
    return x == f[x] ? x : f[x] = find(f[x]);
}

signed main(){
    scanf("%lld%lld%lld%lld",&n,&m,&p,&q);
    FOR(i,1,n+5) f[i] = i;
    ROF(i,m,1){
        int l = (i*p+q)%n+1,r = (i*q+p)%n+1;
        if(l > r) std::swap(l,r);
        int v = find(l);
        while(v <= r){
            ans[v] = i,f[v] = f[v+1];
            v = find(v);
        }
    }
    FOR(i,1,n) printf("%lld\n",ans[i]);
    return 0;
}
