#include <algorithm>
#include <iostream>
#include <cstring>
#include <climits>
#include <cstdlib>
#include <cstdio>
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

const int MAXN = 200000+5;
int n;
int a[MAXN],fa[MAXN];

std::vector<int> G[MAXN];
int dfn[MAXN],tp[MAXN];
std::priority_queue<int> q[MAXN];


inline void dfs(int v){
    static int ts = 0;
    dfn[v] = ++ts;
    for(auto to:G[v]){
        if(to == fa[v]) continue;
        dfs(to);
        if(q[dfn[v]].size() < q[dfn[to]].size()) std::swap(q[dfn[v]],q[dfn[to]]);
        int sz = q[dfn[to]].size();
        FOR(i,1,sz){
            tp[i] = std::max(q[dfn[v]].top(),q[dfn[to]].top());
            q[dfn[to]].pop();q[dfn[v]].pop();
        }
        FOR(i,1,sz) q[dfn[v]].push(tp[i]);
    }
    q[dfn[v]].push(a[v]);
}

int main(){
    scanf("%d",&n);
    FOR(i,1,n) scanf("%d",a+i);
    FOR(i,2,n) scanf("%d",fa+i);
    FOR(i,2,n) G[i].pb(fa[i]),G[fa[i]].pb(i);
    dfs(1);LL ans = 0ll;
    while(!q[dfn[1]].empty()) ans += q[dfn[1]].top(),q[dfn[1]].pop();
    printf("%lld\n",ans);
    return 0;
}
