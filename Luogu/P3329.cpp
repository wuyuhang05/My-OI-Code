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

const int MAXN = 5e5 + 5;

namespace Flow{
    struct Edge{
        int to,w,cap,nxt;
    }e[MAXN<<1];
    int head[MAXN],cur[MAXN],cnt=1;
    int dep[MAXN];
    int S,T,N;

    inline void init(){
        FOR(i,1,cnt) e[i].w = e[i].cap;
    }

    inline void add(int u,int v,int w){
        e[++cnt] = (Edge){v,w,w,head[u]};head[u] = cnt;
        e[++cnt] = (Edge){u,0,0,head[v]};head[v] = cnt;
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

    inline LL Dinic(){
        LL ans = 0,t = 0;
        while(bfs()) while((t=dfs(S))) ans += t;
        return ans;
    }
};
using namespace Flow;

int n;
int p[MAXN];
int t1[MAXN],t2[MAXN];

struct Node{
    int u,v;LL w;
    Node(int u=0,int v=0,LL w=0) : u(u),v(v),w(w) {}
}edge[MAXN];
int tot,cs;

inline void work(int l,int r){
    if(l >= r) return;
    init();
    S = p[l];T = p[l+1];int t = Dinic();
    edge[++tot] = Node(S,T,t);int tp1=0,tp2=0;
    FOR(i,l,r){
        if(dep[p[i]]) t1[++tp1] = p[i];
        else t2[++tp2] = p[i];
    }
    FOR(i,1,tp1) p[l+i-1] = t1[i];
    FOR(i,1,tp2) p[l+tp1+i-1] = t2[i];
    work(l,l+tp1-1);work(l+tp1,r);
}

int f[MAXN],sz[MAXN];

inline int find(int x){
    return x == f[x] ? x : f[x] = find(f[x]);
}
int now;
inline void merge(int x,int y){
    x = find(x);y = find(y);
    if(x == y) return;
    if(sz[x] < sz[y]) std::swap(x,y);
    now += sz[x]*sz[y];
    f[y] = x;sz[x] += sz[y];
}

P q[MAXN];int ans[MAXN];
bool vis[MAXN];
inline void Solve(){++cs;
    int m;scanf("%d%d",&n,&m);
    FOR(i,1,n) head[i] = 0;cnt = 1;N = n;now = 0;tot = 0;
    FOR(i,1,m){
        int u,v,c;scanf("%d%d%d",&u,&v,&c);
        add(u,v,c);add(v,u,c);
    }
    std::iota(p+1,p+n+1,1);
    work(1,n);
    std::fill(sz+1,sz+n+1,1);std::iota(f+1,f+n+1,1);
    std::sort(edge+1,edge+n,[](const Node &a,const Node &b){return a.w > b.w;});
    scanf("%d",&m);
    FOR(i,1,m) scanf("%d",&q[i].fi),q[i].se = i,ans[i] = 0;
    std::sort(q+1,q+m+1,[](const P &a,const P &b){return a.fi > b.fi;});int tp = 1;
    FOR(i,1,m){
        while(tp < n && edge[tp].w > q[i].fi) merge(edge[tp].u,edge[tp].v),++tp;
        ans[q[i].se] = n*(n-1)/2-now;
    }
    FOR(i,1,m) printf("%d\n",ans[i]);
    puts("");
}

int main(){
    freopen("10.in","r",stdin);
    int T;scanf("%d",&T);
    while(T--) Solve();
    return 0;
}
