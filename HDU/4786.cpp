/*
 * Author: RainAir
 * Time: 2019-08-29 08:03:04
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
#define P std::pair
#define LL long long
#define pb push_back
#define MP std::make_pair
#define all(x) x.begin(),x.end()
#define CLR(i,a) memset(i,a,sizeof(i))
#define FOR(i,a,b) for(int i = a;i <= b;++i)
#define ROF(i,a,b) for(int i = a;i >= b;--i)
#define DEBUG(x) std::cerr << #x << '=' << x << std::endl

const int MAXN = 1e5 + 5;
int n,m;

struct Edge{
    int u,v,w;
}e[MAXN];

inline bool cmp1(const Edge &a,const Edge &b){
    return a.w < b.w;
}

inline bool cmp2(const Edge &a,const Edge &b){
    return a.w > b.w;
}

int f[MAXN];

inline int find(int x){
    return x == f[x] ? x : f[x] = find(f[x]);
}

inline int Kruskal(){
    int cnt = 0,sm = 0;
    FOR(i,1,n) f[i] = i;
    FOR(i,1,m){
        int u = e[i].u,v = e[i].v,w = e[i].w;
        int fu = find(u),fv = find(v);
        if(fu == fv) continue;
        f[fv] = fu;sm += w;
        if(++cnt == n-1) return sm;
    }
    return -1;
}

int fib[MAXN],cs;

inline void Solve(){
    printf("Case #%d: ",++cs);

    scanf("%d%d",&n,&m);
    FOR(i,1,m){
        scanf("%d%d%d",&e[i].u,&e[i].v,&e[i].w);
    }
    std::sort(e+1,e+m+1,cmp1);
    int l = Kruskal();
    std::sort(e+1,e+m+1,cmp2);
    int r = Kruskal();
    if(l == -1 || r == -1){
        puts("No");return;
    }
    fib[1] = 1;fib[0] = 0;
    FOR(i,2,n){
        fib[i] = fib[i-1]+fib[i-2];
        if(l <= fib[i] && fib[i] <= r){
            puts("Yes");return;
        }
        if(r <= fib[i]) break;
    }
    puts("No");
}

int main(){
    int T;scanf("%d",&T);
    while(T--) Solve();
    return 0;
}
