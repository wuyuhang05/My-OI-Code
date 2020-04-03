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
const int MAXM = 2000+5;

namespace Flow{
    struct Edge{
        int to,w,nxt;
    }e[MAXN<<1];
    int head[MAXN],cur[MAXN],cnt=1;
    int dep[MAXN];
    int S,T,N;

    inline void add(int u,int v,int w){
        e[++cnt] = (Edge){v,w,head[u]};head[u] = cnt;
        e[++cnt] = (Edge){u,0,head[v]};head[v] = cnt;
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
using namespace Flow;

int lc[MAXN<<5],rc[MAXN<<5],root[MAXN],tot,n;

inline void insert(int prev,int &v,int l,int r,int p,int id){
    lc[v = ++tot] = lc[prev];rc[v] = rc[prev];
    if(l == r){
        if(prev) add(N+v,N+prev,1e9);// 后面的要contain前面的
        add(N+v,id,1e9);
        return;
    }
    int mid = (l + r) >> 1;
    if(p <= mid) insert(lc[prev],lc[v],l,mid,p,id);
    else insert(rc[prev],rc[v],mid+1,r,p,id);
    if(lc[v]) add(N+v,N+lc[v],1e9);
    if(rc[v]) add(N+v,N+rc[v],1e9);
}

inline void modify(int x,int l,int r,int L,int R,int id){
    if(!x) return;
    if(l == L && r == R) {add(id,N+x,1e9);return;}
    int mid = (l + r) >> 1;
    if(R <= mid) modify(lc[x],l,mid,L,R,id);
    else if(L > mid) modify(rc[x],mid+1,r,L,R,id);
    else modify(lc[x],l,mid,L,mid,id),modify(rc[x],mid+1,r,mid+1,R,id);
}

int a[MAXN],l[MAXN],r[MAXN];
std::vector<int> ss;
int m;

int main(){
    scanf("%d",&n);
    N = 2*n;S = ++N;T = ++N;int ans = 0;
    FOR(i,1,n){
        int b,w,p;scanf("%d%d%d%d%d%d",a+i,&b,&w,l+i,r+i,&p);
        ans += b+w;
        ss.pb(a[i]);ss.pb(l[i]);ss.pb(r[i]);
        add(S,i,b);add(i,i+n,p);add(i,T,w);
    }
    std::sort(all(ss));ss.erase(std::unique(all(ss)),ss.end());
    FOR(i,1,n){
        a[i] = std::lower_bound(all(ss),a[i])-ss.begin()+1;
        l[i] = std::lower_bound(all(ss),l[i])-ss.begin()+1;
        r[i] = std::lower_bound(all(ss),r[i])-ss.begin()+1;
    }
    m = ss.size();
    FOR(i,1,n) insert(root[i-1],root[i],1,m,a[i],i);
    FOR(i,2,n){
        modify(root[i-1],1,m,l[i],r[i],i+n);
    }
    N += tot;
    ans -= Dinic();
    printf("%d\n",ans);
    return 0;
}
