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

const int MAXM = 500+5;
const int MAXN = MAXM*MAXM;

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
        for(int i = head[v];i;i = e[i].nxt){
            if(e[i].w > 0 && dep[e[i].to] == dep[v] + 1){
                int t = dfs(e[i].to,std::min(flow,e[i].w));
                if(t>0){
                    ans += t;flow -= t;
                    e[i].w -= t;e[i^1].w += t;
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

int n,m;
int p[MAXM][MAXM],q[MAXM][MAXM],v1[MAXM][MAXM],v2[MAXM][MAXM];

inline int calc(int i,int j){
    return (i-1)*m+j;
}

const int dx[] = {0,1,-1,0,0};
const int dy[] = {0,0,0,1,-1};

int main(){
    scanf("%d%d",&n,&m);int ans = 0;
    FOR(i,1,n) FOR(j,1,m) scanf("%d",&p[i][j]),ans += p[i][j];
    FOR(i,1,n) FOR(j,1,m) scanf("%d",&q[i][j]),ans += q[i][j];
    FOR(i,1,n) FOR(j,1,m) scanf("%d",&v1[i][j]),ans += v1[i][j];
    FOR(i,1,n) FOR(j,1,m) scanf("%d",&v2[i][j]),ans += v2[i][j];
    N = calc(n,m);S = ++N;T = ++N;
    FOR(i,1,n) FOR(j,1,m) add(S,calc(i,j),p[i][j]),add(calc(i,j),T,q[i][j]);
    FOR(i,1,n) FOR(j,1,m){
        FOR(k,0,4){
            int xx = i+dx[k],yy = j+dy[k];
            if(xx < 1 || xx > n || yy < 1 || yy > m) continue;
            add(calc(xx,yy),N+1,1e9);add(N+2,calc(xx,yy),1e9);
        }
        add(N+1,T,v2[i][j]);add(S,N+2,v1[i][j]);
        N += 2;
    }
    ans -= Dinic();
    printf("%d\n",ans);
    return 0;
}
