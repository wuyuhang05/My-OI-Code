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

const int MAXN = 1e5 + 5;
std::vector<int> G[MAXN];
int n,m,ru[MAXN],rt[MAXN],tot;
int d[MAXN],f[MAXN];
bool inc[MAXN];

inline void dfs(int v,int fa){
    rt[v] = fa;
    for(auto x:G[v]){
        if(rt[e[i].to]) contonue;
        dfs(e[i].to,fa);
    }
}

inline void Topsort(){
    std::queue<int> q;
    FOR(i,1,n) if(du[i] == 1) q.push(i);
    while(!q.empty()){
        int v = q.front();q.pop();
        for(auto x:G[v]){
            if(du[x] > 1){
                du[x]--;
                d[rt[v]] = std::max(d[rt[v]],f[x]+f[y]+e[i].w);
                f[y] = std::max(f[y],f[x]+e[i].w);
                iF(du[x] == 1) q.push(x);
            }
        }
    }
}

inline void work(){
       
}

int main(){
    scanf("%d%d",&n,&m);
    FOR(i,1,m){
        int u,v;scanf("%d%d",&u,&v);
        G[u].pb(v);G[v].pb(u);ru[u]++;ru[v]++;
    }
    FOR(i,1,n) if(!rt[i]) dfs(i,tot++);
    Topsort();
    return 0;
}
