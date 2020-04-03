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

const int MAXN = 4e5 + 5;
const int MAXM = 40+5;

namespace Flow{
//public:
    struct Edge{
        int to,w,nxt;
    }e[MAXN<<1];
    int head[MAXN],dep[MAXN],cur[MAXN],cnt = 1;
    int S,T,N;

    inline void add(int u,int v,int w){
//        printf("%d %d %d\n",u,v,w);
        e[++cnt] = (Edge){v,w,head[u]};head[u] = cnt;
        e[++cnt] = (Edge){u,0,head[v]};head[v] = cnt;
    }

    inline bool bfs(){
        FOR(i,0,N) dep[i] = 0,cur[i] = head[i];
        std::queue<int> q;q.push(S);dep[S] = 1;
        while(!q.empty()){
            int v = q.front();q.pop();
            for(int i = head[v];i;i = e[i].nxt){
                if(!dep[e[i].to] && e[i].w > 0){
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
        int ans = 0,t = 0;
        for(int &i = cur[v];i;i = e[i].nxt){
            if(e[i].w > 0 && dep[e[i].to] == dep[v]+1){
                if((t = dfs(e[i].to,std::min(flow,e[i].w)))){
                    ans += t;flow -= t;
                    e[i].w -= t;e[i^1].w += t;
                }
            }
        }
        return ans;
    }

    inline int Dinic(){
        int ans = 0,t = 0;
        while(bfs()) while((t = dfs(S))) ans += t;
        return ans;
    }
};
using namespace Flow;

int n,m,h,D;
int a[MAXM][MAXM][MAXM];
// (i,j) 高度k

inline int calc(int i,int j,int k){
    return ((i-1)*m+j-1)*(h+1)+k;
}

const int dx[] = {0,0,1,-1};
const int dy[] = {1,-1,0,0};

int main(){
    scanf("%d%d%d%d",&n,&m,&h,&D);
    FOR(k,1,h) FOR(i,1,n) FOR(j,1,m) scanf("%d",&a[i][j][k]);
    N = calc(n,m,h+1);S = ++N;T = ++N;
    FOR(i,1,n){
        FOR(j,1,m){
            add(S,calc(i,j,1),1e9);
            int las = calc(i,j,1);
            FOR(k,1,h){
                add(las,calc(i,j,k+1),a[i][j][k]);
                las = calc(i,j,k+1);
            }
            add(las,T,1e9);
        }
    }
    FOR(x,1,n){
        FOR(y,1,m){
            FOR(i,0,3){
                int xx = x+dx[i],yy = y+dy[i];
                if(xx < 1 || xx > n || yy < 1 || yy > m) continue;
                FOR(k,D+1,h+1){
                    add(calc(x,y,k),calc(xx,yy,k-D),1e9);
                }
            }
        }
    }
    printf("%d\n",Dinic());
    return 0;
}
