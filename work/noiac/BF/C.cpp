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

const int MAXN = 20+5;

struct Edge{
    int to,nxt;
}e[MAXN<<1];
int head[MAXN],cnt;

inline void add(int u,int v){
    e[++cnt] = (Edge){v,head[u]};head[u] = cnt;
    e[++cnt] = (Edge){u,head[v]};head[v] = cnt;
}

int n,dep[MAXN];

inline void dfs(int v,int fa=0){
    dep[v] = dep[fa]+1;
    for(int i = head[v];i;i = e[i].nxt){
        if(e[i].to == fa) continue;
        dfs(e[i].to,v);
    }
}
int sm[21],dis[21];
int main(){
    scanf("%d",&n);
    FOR(i,2,n){
        int u,v;scanf("%d%d",&u,&v);
        add(u,v);
    }
    dfs(1);int ans = 1e9;
    FOR(S,0,(1<<n)-1){
        if(S&1) continue;
        FOR(i,1,n) sm[i] = dis[i] = 0;
        int now = 0;
        FOR(i,0,n-1){
            if((S>>i)&1) sm[dep[i+1]]++,dis[i+1] = -1,now = std::max(now,dep[i+1]);
        }
        FOR(i,1,n) sm[i] += sm[i-1];bool flag = 1;
        FOR(i,1,n) if(sm[i] >= i) {flag = 0;break;}
        if(!flag) continue;
        now--;
        std::queue<int> q;q.push(1);dis[1] = 1;
        while(!q.empty()){
            int v = q.front();q.pop();
            for(int i = head[v];i;i = e[i].nxt){
                if(dis[e[i].to] || e[i].to==1) continue;
                dis[e[i].to] = dis[v] + 1;q.push(e[i].to);
            }
        }
        FOR(i,1,n) now = std::max(now,dis[i]);
        ans = std::min(ans,now);
    }
    printf("%d\n",ans);
    return 0;
}
