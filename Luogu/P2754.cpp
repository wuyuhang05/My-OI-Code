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
        for(int &i = cur[v];i;i = e[i].nxt){
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

int n,m,k;
std::vector<int> t[MAXN];
int h[MAXN];
int ori[2][MAXN],now;
int f[MAXN];
inline int find(int x){
    return x == f[x] ? x : f[x] = find(f[x]);
}

int main(){
    scanf("%d%d%d",&n,&m,&k);
    std::iota(f+1,f+n+3,1);
    FOR(i,1,m){
        scanf("%d",h+i);int n;scanf("%d",&n);
        while(n--){
            int x;scanf("%d",&x);
            t[i].pb(x);
        }
        FOR(j,1,(int)t[i].size()-1){
            int u = t[i][j-1],v = t[i][j];
            if(u <= 0) u += ::n+2;
            if(v <= 0) v += ::n+2;
            u = find(u);v = find(v);f[v] = u;
        }
    }
//    DEBUG(find(n+1));DEBUG(find(n+2));
    if(find(n+1) != find(n+2)){
        puts("0");return 0;
    }
    S = ++N;T = ++N;
    FOR(i,0,n) ori[now][i] = ++N;
    add(S,ori[now][0],1e9);
    int res = 0;
    FOR(ts,0,19260817){
        now ^= 1;
        FOR(i,0,n) ori[now][i] = ++N;
        add(S,ori[now][0],1e9);
        FOR(i,1,n) add(ori[now^1][i],ori[now][i],1e9);
        FOR(i,1,m){
            int u = t[i][ts%t[i].size()],v = t[i][(ts+1)%t[i].size()];
            if(u == -1) continue;
            else if(v == -1) add(ori[now^1][u],T,h[i]);
            else add(ori[now^1][u],ori[now][v],h[i]);
        }
        res += Dinic();
        if(res >= k){
            printf("%d\n",ts+1);
            return 0;
        }
    }
    return 0;
}
