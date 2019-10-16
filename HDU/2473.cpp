/*
 * Author: RainAir
 * Time: 2019-09-19 21:15:53
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

const int MAXN = 2e6 + 5;
int n,m,f[MAXN],p[MAXN],cnt,cs;

inline int find(int x){
    return x == f[x] ? x : f[x] = find(f[x]);
}

inline void Solve(){
    FOR(i,0,n-1) p[i] = f[i] = i;cnt = n-1;
    FOR(i,1,m){
        char opt[sizeof("ORZ")];
        scanf("%s",opt+1);
        if(opt[1] == 'M'){
            int x,y;scanf("%d%d",&x,&y);
            x = p[x],y = p[y];
            int fx = find(x),fy = find(y);
            if(fx != fy) f[fy] = fx;
        }
        else{
            int x;scanf("%d",&x);
            p[x] = ++cnt;f[p[x]] = p[x];
        }
    }
    int ans = 0;
    std::set<int> S;
    FOR(i,0,n-1) S.insert(find(p[i]));//if(find(p[i]) == p[i]) ans++;
    printf("Case #%d: %d\n",++cs,(int)S.size());
}

int main(){
    while(~scanf("%d%d",&n,&m) && (n+m)) Solve();
    return 0;
}
