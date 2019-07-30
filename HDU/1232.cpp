/*
 * Author: RainAir
 * Time: 2019-07-25 14:45:51
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
#define Re register
#define LL long long
#define pb push_back
#define MP std::make_pair
#define all(x) x.begin(),x.end()
#define CLR(i,a) memset(i,a,sizeof(i))
#define FOR(i,a,b) for(Re int i = a;i <= b;++i)
#define ROF(i,a,b) for(Re int i = a;i >= b;--i)
#define DEBUG(x) std::cerr << #x << '=' << x << std::endl

const int MAXN = 1000+5;
int f[MAXN],n,m;

inline int find(int x){
    return f[x] == x ? x : f[x] = find(f[x]);
}

std::set<int> S;
inline void Solve(){
    scanf("%d",&m);
    FOR(i,1,n) f[i] = i;
    FOR(i,1,m){
        int u,v;scanf("%d%d",&u,&v);
        int fu = find(u),fv = find(v);
        f[fu] = fv;
    }S.clear();
    FOR(i,1,n) S.insert(find(i));
    printf("%d\n",((int)S.size())-1);
}

int main(){
    while(~scanf("%d",&n) && (n)) Solve();
    return 0;
}
