#include <algorithm>
#include <iostream>
#include <cstring>
#include <climits>
#include <cstdio>
#include <vector>
#include <cstdlib>
#include <ctime>
#include <cmath>
#include <queue>
#include <stack>
#include <map>
#include <set>

#define fi first
#define lc (x<<1)
#define se second
#define U unsigned
#define rc (x<<1|1)
#define Re register
#define LL long long
#define MP std::make_pair
#define CLR(i,a) memset(i,a,sizeof(i))
#define FOR(i,a,b) for(Re int i = a;i <= b;++i)
#define ROF(i,a,b) for(Re int i = a;i >= b;--i)
#define SFOR(i,a,b,c) for(Re int i = a;i <= b;i+=c)
#define SROF(i,a,b,c) for(Re int i = a;i >= b;i-=c)
#define DEBUG(x) std::cerr << #x << '=' << x << std::endl

const int MAXN = 500+5;

struct Edge{
    int to,c,next;
}e[MAXN*MAXN*MAXN];

int head[MAXN],level[MAXN],cur[MAXN],cnt=1;

inline void add(int u,int v,int w){
    e[++cnt] = (Edge){v,w,head[u]};head[u] = cnt;
    e[++cnt] = (Edge){u,0,head[v]};head[v] = cnt;
}

int N,M,S,T;

inline bool bfs(){
    FOR(i,0,N) cur[i] = head[i];
    CLR(level,0);
    std::queue<int> q;q.push(S);level[S] = 1;
    while(!q.empty()){
        int v = q.front();q.pop();
        for(int i = head[v];i;i = e[i].next){
            if(e[i].c > 0 && !level[e[i].to]){
                level[e[i].to] = level[v] + 1;
                if(e[i].to == T) return true;
                q.push(e[i].to);
            }
        }
    }
    return false;
}

inline int dfs(int v,int limit=INT_MAX){
    if(v == T || !limit) return limit;
    int res = 0,flow;
    for(int &i = cur[v];i;i = e[i].next){
        if(level[e[i].to] == level[v] + 1 && (flow = dfs(e[i].to,std::min(limit,e[i].c)))){
            res += flow;limit -= flow;
            e[i].c -= flow;e[i^1].c += flow;
            if(!limit) break;
        }
    }
    return res;
}

inline int dinic(){
    int ans = 0;
    while(bfs()) ans += dfs(S);
    return ans;
}

struct Person{
    std::string str;
    int HP;
}p1[MAXN],p2[MAXN];
#define s1 p1[i].str[0]
#define s2 p2[j].str[0] 
#define ex1 (p1[i].str[0] == 'J' ? xu1 : 0)
#define ex2 (p2[i].str[0] == 'J' ? xu2 : 0)
int main(){
    std::ios::sync_with_stdio(false);
    int n,xu1=0,xu2=0;
    std::cin >> n >> M;
    S = 0;T = N = (n<<1)|1;
    FOR(i,1,n) std::cin >> p1[i].str;
    FOR(i,1,n) std::cin >> p2[i].str;
    FOR(i,1,n) std::cin >> p1[i].HP;
    FOR(i,1,n) std::cin >> p2[i].HP;
    FOR(i,1,n){
        if(p1[i].str[0] == 'Y') xu1++;
        if(p2[i].str[0] == 'Y') xu2++;
    }
    FOR(i,1,n){
        FOR(j,1,n){
            if(s1 == 'J' && (s2 == 'H' || s2 == 'W')) add(i,j+n,1);
            if(s1 == 'E' && (s2 == 'J' || s2 == 'Y')) add(i,j+n,1);
            if(s1 == 'Y' && (s2 == 'J' || s2 == 'H')) add(i,j+n,1);
            if(s1 == 'H' && (s2 == 'E' || s2 == 'W')) add(i,j+n,1);
            if(s1 == 'W' && (s2 == 'Y' || s2 == 'E')) add(i,j+n,1);
        }
    }
    FOR(i,1,n) add(S,i,p1[i].HP+ex1),add(i+n,T,p2[i].HP+ex2);
    std::cout << std::min(dinic(),M) << std::endl;
    return 0;
}