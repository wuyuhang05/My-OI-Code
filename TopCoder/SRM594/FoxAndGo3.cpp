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
const int MAXM = 50+5;
int n;

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

inline int calc(int i,int j){
    return (i-1)*n+j;
}

const int dx[] = {0,0,1,-1};
const int dy[] = {1,-1,0,0};

class FoxAndGo3{
public:
    inline int maxEmptyCells(std::vector<std::string> a){
        n = a.size();
        N = calc(n,n);S = ++N;T = ++N;int sm = calc(n,n);
        FOR(i,1,n){
            FOR(j,1,n){
                if(a[i-1][j-1] == 'o'){
                    add(S,calc(i,j),1);
                    FOR(k,0,3){
                        int xx = i+dx[k],yy = j+dy[k];
                        if(xx >= 1 && xx <= n && yy >= 1 && yy <= n && a[xx-1][yy-1] == '.') add(calc(i,j),calc(xx,yy),1);
                    }
                }
                else if(a[i-1][j-1] == '.') add(calc(i,j),T,1);
                else sm--;
            }
        }
        return sm-Dinic();
    }
};
// 一个白色和周围的空格不可能同时为0
// 二分图 最大独立集
#ifdef RainAir
int main(){
    FoxAndGo3 test;
    printf("%d\n",test.maxEmptyCells({"o.o", ".o.", "o.o"}));
    return 0;
}
#endif
