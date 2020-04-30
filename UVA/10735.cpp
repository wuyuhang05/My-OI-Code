#include<bits/stdc++.h>

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

const int MAXN = 5000+5;
int n,m;

namespace Flow{
    struct Edge{
        int to,w,nxt;
    }e[MAXN<<1];
    int head[MAXN],cur[MAXN],cnt=1;
    int dep[MAXN];
    int S,T,N;

    inline void clear(){
        FOR(i,0,N) head[i] = 0;cnt = 1;S = T = N = 0;
    }

    inline int addf(int u,int v,int w){
        e[++cnt] = (Edge){v,w,head[u]};head[u] = cnt;
        e[++cnt] = (Edge){u,0,head[v]};head[v] = cnt;
        return cnt-1;
    }

    inline bool bfs(){
        FOR(i,0,N) cur[i] = head[i],dep[i] = 0;
        std::queue<int> q;q.push(S);dep[S] = 1;
        while(!q.empty()){
            int v = q.front();q.pop();
            for(int i = head[v];i;i = e[i].nxt){
                if(e[i].w > 0 && !dep[e[i].to]){
                    dep[e[i].to] = dep[v] + 1;
                    if(e[i].to == T) return true;
                    q.push(e[i].to);
                }
            }
        }
        return dep[T];
    }

    inline int dfs(int v,int flow=1e9){
        if(v == T) return flow;
        if(!flow) return 0;
        int ans = 0;
        for(int &i = cur[v];i;i = e[i].nxt){
            if(e[i].w > 0 && dep[e[i].to] == dep[v] + 1){
                int t = dfs(e[i].to,std::min(flow,e[i].w));
                if(t>0){
                    ans += t;flow -= t;
                    e[i].w -= t;e[i^1].w += t;
                    if(!flow) break;
                }
            }
        }
        return ans;
    }

    inline int Dinic(){
        int ans = 0,t = 0;
        while(bfs()) while((t=dfs(S))) ans += t;
        return ans;
    }
};
using Flow::S;
using Flow::T;
using Flow::addf;
int du[MAXN];// 出-入
std::vector<P> edge;
int id[MAXN];
int chk[MAXN];
struct Edge{
    int to,w,nxt;
}e[MAXN];
int head[MAXN],cnt;

inline void add(int u,int v){
    chk[u]++;chk[v]--;
    e[++cnt] = (Edge){v,0,head[u]};head[u] = cnt;
}
std::vector<int> ans;

inline void dfs(int v){
    for(int &i = head[v];i;i = e[i].nxt){
        if(e[i].w) continue;
        e[i].w = 1;int t = i;
        dfs(e[i].to);
        ans.pb(e[t].to);
    }
}
bool g[MAXN];
inline void Solve(){
    scanf("%d%d",&n,&m);ans.clear();
    std::vector<int> q;edge.clear();Flow::clear();
    FOR(i,1,n) du[i] = head[i] = g[i] = chk[i] = 0;cnt = 0;
    FOR(i,1,m){
        int u,v;char str[23];
        scanf("%d%d%s",&u,&v,str);
        ++du[u];--du[v];
        g[u] = g[v] = 1;
        if(str[0] == 'U') edge.pb(MP(u,v));
        else add(u,v);
    }
    S = n+1;Flow::N = T = n+2;
    bool flag = false;
    FOR(i,1,n){
        flag |= (du[i]&1);
        if(du[i] > 0) addf(S,i,du[i]/2);
        else addf(i,T,(-du[i])/2);
    }
    if(flag){
        puts("No euler circuit exist");return;
    }
    FOR(i,0,(int)edge.size()-1) id[i] = addf(edge[i].fi,edge[i].se,1);
    Flow::Dinic();
    FOR(i,0,(int)edge.size()-1) Flow::e[id[i]].w ? add(edge[i].fi,edge[i].se) : add(edge[i].se,edge[i].fi);
    int s = 0;
    FOR(i,1,n){
        if(chk[i]){puts("No euler circuit exist");return;}
    }
    FOR(i,1,n) if(g[i]) {s = i;dfs(i);break;}
    ans.pb(s);std::reverse(all(ans));
    for(auto x:ans) printf("%d ",x);puts("");
}

int main(){
    int T;scanf("%d",&T);
    while(T--) Solve(),puts("");
    return 0;
}