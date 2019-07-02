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

const int MAXN = 3e5 + 5;

int ans[MAXN],size[MAXN],son[MAXN];
std::vector<int> G[MAXN];
int n,fa[MAXN],q;

inline void dfs(int v){
    size[v] = 1;
    ans[v] = v;
    for(auto x:G[v]){
        if(x == fa[v]) continue;
        dfs(x);size[v] += size[x];
        if(size[son[v]] < size[x]) son[v] = x;
    }
    if(size[son[v]]*2 > size[v]){
        int t = ans[son[v]];
        while((size[v]-size[t])*2 > size[v]) t = fa[t];
        ans[v] = t;
    }
}

int main(){
    scanf("%d%d",&n,&q);
    FOR(i,2,n){
        scanf("%d",fa+i);
        G[fa[i]].pb(i);G[i].pb(fa[i]);
    }
    dfs(1);
    FOR(i,1,q){
        int x;scanf("%d",&x);
        printf("%d\n",ans[x]);
    }
    return 0;
}
