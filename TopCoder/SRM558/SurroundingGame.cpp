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
const int MAXM = 100 + 5;

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

inline int tr(char c){
    if(isdigit(c)) return c-'0';
    else if('a' <= c && c <= 'z') return c-'a'+10;
    else return c-'A'+36;
}

int n,m;

inline int calc(int i,int j,int opt=0){
    return opt*n*m+(i-1)*m+j;
}

const int dx[] = {0,0,1,-1};
const int dy[] = {1,-1,0,0};

class SurroundingGame{
public:
    inline int maxScore(std::vector<std::string> a,std::vector<std::string> b){
        n = a.size();m = a[0].length();
        N = calc(n,m,1);S = ++N;T = ++N;int ans = 0;
        FOR(x,1,n){
            FOR(y,1,m){
                if((x+y)&1) add(S,calc(x,y),tr(a[x-1][y-1])),add(calc(x,y),calc(x,y,1),tr(b[x-1][y-1]));
                else add(calc(x,y),calc(x,y,1),tr(b[x-1][y-1])),add(calc(x,y,1),T,tr(a[x-1][y-1]));
                ans += tr(b[x-1][y-1]);
                if(!((x+y)&1)) continue;
                FOR(i,0,3){
                    int xx = x+dx[i],yy = y+dy[i];
                    if(xx < 1 || xx > n || yy < 1 || yy > m) continue;
                    add(calc(x,y),calc(xx,yy),1e9);add(calc(x,y,1),calc(xx,yy,1),1e9);
                }
            }
        }
        return ans-Dinic();
    }
};

#ifdef RainAir
int main(){
    SurroundingGame test;
    printf("%d\n",test.maxScore({"asam","atik"}
,{"123A","45BC"}));
    return 0;
}
#endif
