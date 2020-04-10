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

namespace MCMF{
    struct Edge{
        int fr,to,w,c,nxt;
    }e[MAXN<<1];
    int head[MAXN],cnt=1;

    inline void add(int u,int v,int w,int c){
        e[++cnt] = (Edge){u,v,w,c,head[u]};head[u] = cnt;
        e[++cnt] = (Edge){v,u,0,-c,head[v]};head[v] = cnt;
    }

    int dis[MAXN],pre[MAXN];
    bool inq[MAXN];
    int N,S,T;

    inline bool spfa(){
        std::queue<int> q;
        FOR(i,0,N) dis[i] = 1e9,pre[i] = -1;
        dis[S] = 0;pre[S] = 0;q.push(S);inq[S] = 1;
        while(!q.empty()){
            int v = q.front();q.pop();
            inq[v] = 0;
            for(int i = head[v];i;i = e[i].nxt){
                if(e[i].w > 0 && dis[e[i].to] > dis[v]+e[i].c){
//                    DEBUG(e[i].to);DEBUG(e[i].c);
                    dis[e[i].to] = dis[v]+e[i].c;pre[e[i].to] = i;
                    if(!inq[e[i].to]) q.push(e[i].to),inq[e[i].to] = 1;
                }
            }
        }
        return pre[T]!=-1;
    }

    int maxFlow,minCost;

    inline void work(){
        while(spfa()){
            int flow = 1e9;
            for(int v = T;v != S;v = e[pre[v]].fr){
                flow = std::min(flow,e[pre[v]].w);
            }
            maxFlow += flow;
            for(int v = T;v != S;v = e[pre[v]].fr){
                minCost += flow*e[pre[v]].c;
                e[pre[v]].w -= flow;
                e[pre[v]^1].w += flow;
            }
        }
    }
}
using namespace MCMF;

char str[MAXM][MAXM];
int n,m;

inline int calc(int i,int j){
    return (i-1)*m+j;
}

int d[MAXN];// out-in
const int dx[] = {0,0,1,-1};
const int dy[] = {1,-1,0,0};

int main(){
    while(~scanf("%s",str[++n]+1));
    m = strlen(str[1]+1);while((int)strlen(str[n]+1) != m) n--;
    N = calc(n,m);int s = ++N,t = ++N;S = ++N;T = ++N;
    FOR(i,1,n){
        FOR(j,1,m){
            if(str[i][j] == '#') continue;
            if((i+j)&1){
                d[calc(i,j)] -= 2,d[s] += 2;
                FOR(k,0,3){
                    int ii = i+dx[k],jj = j+dy[k];
                    if(ii <= 0 || ii > n || jj <= 0 || jj > m) continue;
                    if(str[ii][jj] == '#') continue;
                    add(calc(i,j),calc(ii,jj),1,0);
                }
                if(i == 1 || i == n || j == 1 || j == m) add(calc(i,j),t,1,1);
            }
            else{
                d[calc(i,j)] += 2,d[t] -= 2;
                if(i == 1 || i == n || j == 1 || j == m) add(s,calc(i,j),1,1);
            }
        }
    }
    int sm = 0;
    FOR(i,1,calc(n,m)+2){
        if(d[i] > 0) add(i,T,d[i],0);
        if(d[i] < 0) add(S,i,-d[i],0),sm -= d[i];
    }
    add(t,s,1e9,0);
    work();
//    DEBUG(maxFlow);DEBUG(minCost);DEBUG(sm);
    if(sm != maxFlow){
        puts("-1");return 0;
    }
    printf("%d\n",minCost/2);
    return 0;
}
