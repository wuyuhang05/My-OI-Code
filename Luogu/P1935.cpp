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
const int MAXM = 100+5;

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

int n,m;
int A[MAXM][MAXM],B[MAXM][MAXM],C[MAXM][MAXM];

inline int calc(int i,int j){
    return (i-1)*m+j;
}

const int dx[] = {1,-1,0,0};
const int dy[] = {0,0,1,-1};

int main(){
    scanf("%d%d",&n,&m);int ans = 0;
    FOR(i,1,n) FOR(j,1,m) scanf("%d",&A[i][j]),ans += A[i][j];
    FOR(i,1,n) FOR(j,1,m) scanf("%d",&B[i][j]),ans += B[i][j];
    FOR(i,1,n) FOR(j,1,m) scanf("%d",&C[i][j]);
    FOR(i,1,n) FOR(j,1,m) if((i+j)&1) std::swap(A[i][j],B[i][j]);
    N = calc(n,m);S = ++N;T = ++N;
    FOR(i,1,n){
        FOR(j,1,m){
            add(S,calc(i,j),B[i][j]);add(calc(i,j),T,A[i][j]);
            if((i+j)&1) continue;
            FOR(k,0,3){
                int xx = i+dx[k],yy = j+dy[k];
                if(xx < 1 || xx > n || yy < 1 || yy > m) continue;
                add(calc(i,j),calc(xx,yy),C[i][j]+C[xx][yy]);
                add(calc(xx,yy),calc(i,j),C[i][j]+C[xx][yy]);
                ans += C[i][j]+C[xx][yy];
            }
        }
    }
    ans -= Dinic();
    printf("%d\n",ans);
    return 0;
}

