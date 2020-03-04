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

const int MAXN = 5000 + 5;

struct Edge{
    int to,next,w1,w2;
}e[MAXN<<1];

int head[MAXN],cnt;

inline void add(int u,int v,int w1,int w2){
    e[++cnt] = (Edge){v,head[u],w1,w2};head[u] = cnt;
    e[++cnt] = (Edge){u,head[v],w1,w2};head[v] = cnt;
}

struct node{
    int x;LL t,c;
    node(int x=0,int t=0,int c=0) : x(x),t(t),c(c) {}
    inline bool operator < (const node &tt) const {
        return t*c > tt.t*tt.c;
    }
};

struct rnode{
    LL t,c;
    rnode(int t=0,int c=0) : t(t), c(c) {}
    inline bool operator < (const rnode &tt) const {
        return t == tt.t ? c < tt.c : t < tt.t;
    }
};

std::priority_queue<node> q;
std::set<rnode> S[MAXN];
int f[MAXN],vis[MAXN],tc;

inline int find(int x){
    return x == f[x] ? x : f[x] = find(f[x]);
}

inline bool chk(int x,rnode v){
    auto i = S[x].lower_bound(v);
    for(;i != S[x].end() && i->c >= v.c;++i) S[x].erase(i);
    if(i != S[x].begin()){
        --i;if(i->c < v.c) return false;
    }
    S[x].insert(v);return true;
}

LL ans[MAXN];
int ct=1;

void dij(int s){
    q.push(node(s,0,0));
    while(!q.empty()){
        auto v = q.top();q.pop();
        if(!chk(v.x,rnode(v.t,v.c))) continue;
        if(!vis[v.x]) vis[v.x] = true,ans[v.x] = v.c*v.t,++tc;
        if(tc == ct) return;
        for(int i = head[v.x];i;i = e[i].next){
            int to = e[i].to;
            q.push(node(to,v.t+e[i].w1,v.c+e[i].w2));
        }
    }
}

int n,m;

int main(){
    scanf("%d%d",&n,&m);
    FOR(i,1,n) ans[i] = -1,f[i] = i;
    FOR(i,1,m){
        int u,v,w1,w2;scanf("%d%d%d%d",&u,&v,&w1,&w2);
        add(u,v,w1,w2);if(find(u) != find(v)) f[f[u]] = f[v];
    }
    for(int i = 2,rt = find(1);i <= n;++i) if(find(i) == rt) ++ct;
    dij(1);
    FOR(i,2,n) printf("%lld\n",ans[i]);
    return 0;
}
