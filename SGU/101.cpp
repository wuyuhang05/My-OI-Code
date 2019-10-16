/*
 * Author: RainAir
 * Time: 2019-09-03 20:05:35
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

const int MAXN = 1000+5;

struct Edge{
    int to,nxt,id;
}e[MAXN<<1];
int head[MAXN],cnt,du[MAXN];

inline void add(int u,int v,int id){
    e[++cnt] = (Edge){v,head[u],id};head[u] = cnt;
//    e[++cnt] = (Edge){u,head[v],id};head[v] = cnt;
}

int m;
bool vis[MAXN];
std::vector<int> ans;

void dfs(int v){
    for(int i = head[v];i;i = e[i].nxt){
        int id = e[i].id;
        if(!vis[std::abs(id)]){
            vis[std::abs(id)] = true;
            dfs(e[i].to);
            ans.pb(id);//DEBUG(id);
        }
    }
}

int main(){
    scanf("%d",&m);
    FOR(i,1,m){
        int u,v;scanf("%d%d",&u,&v);
        ++u;++v;add(u,v,i);add(v,u,-i);
        ++du[u];++du[v];
    }
    int sm = 0,s = -1;
    FOR(i,1,7) if(du[i]&1) {s = i;sm++;};
    if(sm > 2 || sm == 1){
        puts("No solution");
        return 0;
    }
    if(s == -1){
    FOR(i,1,7) if(du[i] > 0){s = i;break;}
    }
    dfs(s);
    FOR(i,1,m) if(!vis[i]){
        puts("No solution");
        return 0;
    }
    std::reverse(all(ans));
    for(auto x:ans){
        if(x > 0) printf("%d +\n",x);
        else printf("%d -\n",-x);
    }
    return 0;
}
