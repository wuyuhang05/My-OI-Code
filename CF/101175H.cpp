/*
 * Author: RainAir
 * Time: 2019-10-11 14:52:28
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

const int MAXN = 5e4 + 5;
int n,m;

std::vector<int> G[MAXN],bcc[MAXN];
int dfn[MAXN],low[MAXN];
int st[MAXN],tp,tot;
bool tag[MAXN]; // 割点

inline void clear(){
    FOR(i,1,n) G[i].clear();
    FOR(i,1,tot) bcc[i].clear();
    FOR(i,1,n) dfn[i] = low[i] = st[i] = tag[i] = 0;
    tp = tot = 0;
}

inline void dfs(int v,int fa=0){
    static int ts = 0;
    dfn[v] = low[v] = ++ts;st[++tp] = v;
    int deg = 0;
    for(auto x:G[v]){
        if(!dfn[x]){
            dfs(x,v);deg++;
            low[v] = std::min(low[v],low[x]);
            if(low[x] >= dfn[v]){
                tag[v] = true;
                ++tot;int t = 0;
                do{
                    t = st[tp--];
                    bcc[tot].pb(t);
                }while(t != x);
                bcc[tot].pb(v);
            }
        }
        else low[v] = std::min(low[v],dfn[x]);
    }
    if(!fa && deg == 1) tag[v] = 0;
}
int cs;
inline void Solve(){
    printf("Case %d: ",++cs);
    FOR(i,1,m){
        int u,v;scanf("%d%d",&u,&v);
        n = std::max(n,std::max(u,v));
        G[u].pb(v);G[v].pb(u);
    }
    dfs(1);
    if(tot == 1){
        int sz = bcc[1].size();
        printf("2 %lld\n",1ll*sz*(sz-1)/2);
        clear();
        return;
    }
    int ans = 0;LL ans2 = 1;
   /* FOR(i,1,tot){
        for(auto x:bcc[i]) printf("%d ",x);
        puts("");
    }*/
    FOR(i,1,tot){
        int cnt = 0;
        for(auto x:bcc[i]){
            if(tag[x]) cnt++;
            if(cnt >= 2) break;
        }
        if(cnt == 1) ++ans,ans2 *= 1ll*((LL)bcc[i].size()-1);
    }
    printf("%d %lld\n",ans,ans2);
    clear();
}

int main(){
    while(~scanf("%d",&m) && m) Solve();
    return 0;
}
