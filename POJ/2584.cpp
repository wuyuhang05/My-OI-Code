/*
 * Author: RainAir
 * Time: 2019-08-25 09:28:17
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
#define MP std::make_pair
#define all(x) x.begin(),x.end()
#define CLR(i,a) memset(i,a,sizeof(i))
#define FOR(i,a,b) for(Re int i = a;i <= b;++i)
#define ROF(i,a,b) for(Re int i = a;i >= b;--i)
#define DEBUG(x) std::cerr << #x << '=' << x << std::endl

const int MAXN = 1000+5;

struct Edge{
    int to,cap,flow,nxt;
}e[MAXN<<1];
int head[MAXN],level[MAXN],cur[MAXN],cnt = 1;
int S,T,N,n;

inline void add(int u,int v,int cap){
//    printf("%d %d %d\n",u,v,cap);
    e[++cnt] = (Edge){v,cap,0,head[u]};head[u] = cnt;
    e[++cnt] = (Edge){u,0,0,head[v]};head[v] = cnt;
}

inline bool bfs(){
    FOR(i,0,N) cur[i] = head[i],level[i] = 0;
    std::queue<int> q;q.push(S);level[S] = 1;
    while(!q.empty()){
        int v = q.front();q.pop();
        for(int i = head[v];i;i = e[i].nxt){
            if(e[i].flow < e[i].cap && !level[e[i].to]){
                level[e[i].to] = level[v] + 1;
                if(e[i].to == T) return true;
                q.push(e[i].to);
            }
        }
    }
    return false;
}

inline int dfs(int v,int lim=INT_MAX){
    if(v == T) return lim;int flow;
    for(int &i = cur[v];i;i = e[i].nxt){
        if(e[i].flow < e[i].cap && level[e[i].to] == level[v] + 1){
            if((flow = dfs(e[i].to,std::min(lim,e[i].cap-e[i].flow)))){
                e[i].flow += flow;e[i^1].flow -= flow;
                return flow;
            }
        }
    }
    return 0;
}

inline int Dinic(){
    int ans = 0,flow;
    while(bfs()){
        while((flow = dfs(S))) ans += flow;
    }
    return ans;
}

char str[MAXN];
std::map<char,int> biao;

inline void clear(){
    CLR(head,0);cnt = 1;
}

int main(){
    biao['S'] = 1;biao['M'] = 2;biao['L'] = 3;biao['X'] = 4;biao['T'] = 5;
    while(~scanf("%s",str+1)){
        if(str[10] == 'T') return 0;
        scanf("%d",&n);
        S = n+6;N = T = S+1;
        FOR(i,1,n){
            scanf("%s",str+1);
            int l = n+biao[str[1]],r = n+biao[str[2]];
            //DEBUG(l);DEBUG(r);
            FOR(j,l,r) add(i,j,1);
        }
        FOR(i,1,n) add(S,i,1);
        FOR(i,1,5){
            int x;scanf("%d",&x);
            add(n+i,T,x);
        }
        scanf("%*s");
        int ans = Dinic();
        puts(ans == n ? "T-shirts rock!" : "I'd rather not wear a shirt anyway...");
        clear();
    }
    return 0;
}
