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
int n,k,a[MAXN],ans = 0;

std::vector<int> G[MAXN];
int dep[MAXN],mxd[MAXN];
bool vis[MAXN];int mx = 0;

inline void dfs2(int v,int fa=0,int dep=0){
    mx = std::max(mx,dep);
    for(auto x:G[v]){
        if(x == fa || vis[x]) continue;
        dfs2(x,v,dep+1);
    }
}

inline int dfs(int v,int fa=0){
    int dep = -1;
    for(auto x:G[v]){
        if(x == fa) continue;
        dep = std::max(dep,dfs(x,v));
    }
    dep++;
    if(dep == k-1){
        if(fa > 1)ans++;
        return -1;
    }
    return dep;
}

int main(){
    scanf("%d%d",&n,&k);
    FOR(i,1,n) scanf("%d",a+i);
    if(a[1] != 1) ans++,a[1] = 1;
    FOR(i,2,n) G[a[i]].pb(i);
    dfs(1);
    printf("%d\n",ans);
    return 0;
}
