/*
 * Author: RainAir
 * Time: 2019-10-10 10:31:50
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
#define P std::pair<int,int>
#define LL long long
#define pb push_back
#define MP std::make_pair
#define all(x) x.begin(),x.end()
#define CLR(i,a) memset(i,a,sizeof(i))
#define FOR(i,a,b) for(int i = a;i <= b;++i)
#define ROF(i,a,b) for(int i = a;i >= b;--i)
#define DEBUG(x) std::cerr << #x << '=' << x << std::endl

const int MAXN = 2e6 + 5;

struct Edge{
    int to,nxt;
}e[MAXN<<1];
int head[MAXN],cnt;
int c[MAXN],sz[MAXN],n,W;

inline void add(int u,int v){
    e[++cnt] = (Edge){v,head[u]};head[u] = cnt;
    e[++cnt] = (Edge){u,head[v]};head[v] = cnt;
}

int ans = 0;

inline void dfs(int v,int fa=0){
    for(int i = head[v];i;i = e[i].nxt){
        if(e[i].to == fa) continue;
        dfs(e[i].to,v);
    }
    std::vector<P> q;
    for(int i = head[v];i;i = e[i].nxt){
        if(e[i].to == fa) continue;
     //   if(v == 2) DEBUG(e[i].to);
        q.pb(MP(c[e[i].to]+sz[e[i].to],e[i].to));
    }
    std::sort(all(q));
    FOR(i,0,(int)q.size()-1){
        P x = q[i];
        if(x.fi + c[v] + sz[v]-1  <= W){
            sz[v] += sz[x.se]-1;
            c[v] += c[x.se];
            ans++;
        }
    }
}

int main(){
    scanf("%d%d",&n,&W);
    FOR(i,1,n) scanf("%d",c+i);
    FOR(i,1,n){
        int k;scanf("%d",&k);sz[i] = k;
        FOR(j,1,k){
            int x;scanf("%d",&x);++x;
            add(i,x);
        }
    }
    dfs(1);
    printf("%d\n",ans);
    return 0;
}
