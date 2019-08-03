/*
 * Author: RainAir
 * Time: 2019-08-01 21:54:11
 */
#include <algorithm>
#include <iostream>
#include <cstring>
#include <climits>
#include <cstdlib>
#include <cstdio>
#include <bitset>
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
#define pw2(x) ((x)*(x))
#define MP std::make_pair
#define all(x) x.begin(),x.end()
#define CLR(i,a) memset(i,a,sizeof(i))
#define FOR(i,a,b) for(Re int i = a;i <= b;++i)
#define ROF(i,a,b) for(Re int i = a;i >= b;--i)
#define DEBUG(x) std::cerr << #x << '=' << x << std::endl

const int MAXN = 500+5;
const int MAXM = 40000 + 5;
int mp[MAXN][MAXN];

struct Edge{
    int to,nxt,cap,flow;
}e[MAXM<<2];
int cnt = 1,head[MAXM],level[MAXM],cur[MAXM];

inline void add(int u,int v,int w){
    //if(v == 122) printf("%d %d %d\n",u,v,w);
    e[++cnt] = (Edge){v,head[u],w,0};head[u] = cnt;
    e[++cnt] = (Edge){u,head[v],0,0};head[v] = cnt;
}

int S,T,N;

inline bool bfs(){
    FOR(i,0,N) cur[i] = head[i];std::fill(level,level+N+1,0);
    std::queue<int> q;q.push(S);level[S] = 1;
    while(!q.empty()){
        int v = q.front();q.pop();
       // if(v >= 111) DEBUG(v);
        for(int i = head[v];i;i = e[i].nxt){
           // if(e[i].to == 122) DEBUG(level[e[i].to]);
           // DEBUG(T);
            if(!level[e[i].to] && e[i].cap > e[i].flow){
                level[e[i].to] = level[v] + 1;
                if(e[i].to == T) return true;
                q.push(e[i].to);
            }
        }
    }
    return false;
}

inline int dfs(int v,int lim=INT_MAX){
    if(v == T) return lim;
    if(!lim) return 0;int flow;
    for(int &i = cur[v];i;i = e[i].nxt){
        if(e[i].cap > e[i].flow && level[e[i].to] == level[v]+1){
            if((flow = dfs(e[i].to,std::min(lim,e[i].cap-e[i].flow)))){
                e[i].flow += flow;
                e[i^1].flow -= flow;
                return flow;
            }
        }
    }
    return 0;
}

inline int Dinic(){
    int ans = 0,flow;
    while(bfs()){
       // DEBUG(flow);
        while((flow = dfs(S))) ans += flow;
    }
    return ans;
}

int n,m;
inline int calc(int x,int y){
    return x+n*(y-1);
}

class FoxAndCity{
public:
    int minimalCost(std::vector<std::string> linked, std::vector<int> want){  
        n = linked.size();m = want.size();
        FOR(i,0,n-1){
            FOR(j,0,n-1){
                mp[i+1][j+1] = linked[i][j] == 'Y';
            }
        }
        S = 0,T = n*n+1,N = T;//DEBUG(N);
  //      DEBUG(T);
        FOR(i,1,n){
            FOR(j,1,n){
                if(j == 1) add(S,calc(i,j),i == 1 ? 0 : INT_MAX);
                else add(calc(i,j-1),calc(i,j),i == 1 ? INT_MAX : pw2(want[i-1]-(j-1))),
                    add(calc(i,j),calc(i,j-1),INT_MAX);
            }
            add(calc(i,n),T,i == 1 ? INT_MAX : pw2(want[i-1]-n));
        }
        FOR(i,1,n){
            FOR(j,1,i-1){
                if(mp[i][j] == 1){
                    FOR(k,2,n){
                        add(calc(i,k),calc(j,k-1),INT_MAX);
                        add(calc(j,k),calc(i,k-1),INT_MAX);
                    }
                }
            }
        }
        return Dinic();
    }
};
/*
int main(){
    std::vector<std::string> a;std::vector<int> b;
    int n;scanf("%d",&n);
    FOR(i,1,n){
        std::string str;std::cin >> str;
        a.pb(str);
    }
    FOR(i,1,n){
        int x;std::cin >> x;
        b.pb(x);
    }
    FoxAndCity test;
    printf("%d\n",test.minimalCost(a,b));
    return 0;
}*/
