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
        bool flag;
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
                if(e[i].flag) continue;
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
            if(e[i].flag) continue;
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

double a[MAXM][MAXM];
int n;
int d[MAXN];// 出-入

int main(){
    scanf("%d",&n);
    FOR(i,1,n) FOR(j,1,n) scanf("%lf",&a[i][j]);
    N = 2*n;int s = ++N,t = ++N;S = ++N;T = ++N;
    FOR(i,1,n-1){
        FOR(j,1,n-1){
            if(a[i][j]-(int)a[i][j] != 0){ // (i,j+n,a[i][j],a[i][j]+1)
                add(i,j+n,1);
            }
            d[i] += (int)a[i][j];d[j+n] -= (int)a[i][j];
        }
    }
    FOR(i,1,n-1){
        if(a[i][n]-(int)a[i][n] != 0) add(s,i,1);
        d[s] += (int)a[i][n];d[i] -= (int)a[i][n];
    }
    FOR(j,1,n-1){
        if(a[n][j]-(int)a[n][j] != 0) add(j+n,t,1);
        d[j+n] += (int)a[n][j];d[t] -= (int)a[n][j];
    }
    FOR(i,1,n*2+2){
        if(d[i] > 0){
            add(i,T,d[i]);
        }
        else if(d[i] < 0) add(S,i,-d[i]);
    }
    add(t,s,1e9);
    Dinic();
    bool flag = 1;
    for(int i = head[S];i;i = e[i].nxt){
        flag &= (e[i].w==0);
    }
    if(!flag){
        puts("No");return 0;
    }
    FOR(v,1,n*2+4){
        for(int i = head[v];i;i = e[i].nxt){
            if(v == S || v == T || e[i].to == S || e[i].to == T) e[i].flag = 1;
        }
    }
    head[S] = head[T] = 0;
    int ans = e[cnt].w;
    S = s;T = t;e[cnt--].flag = 1;e[cnt--].flag = 1;
    ans += Dinic();
    printf("%d\n",ans*3);
    return 0;
}
