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
#define P std::pair<int,int>
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
const int MAXM = 1e5 + 4;

struct Edge{
    int to,w,next;
}e[MAXM],e1[MAXM];
int cnt,S,T,K,n,m;
int head[MAXN],head1[MAXN],g[MAXN];

inline void add(int u,int v,int w){
    e[++cnt] = (Edge){v,w,head[u]};head[u] = cnt;
    e1[cnt] = (Edge){u,w,head1[v]};head1[v] = cnt;
}

inline void dij(int s){
    bool vis[MAXN] = {0};
    FOR(i,1,n) g[i] = 1e9;
    std::priority_queue<P,std::vector<P>,std::greater<P> > q;
    q.push(MP(0,s));g[s] = 0;
    while(!q.empty()){
        int v = q.top().se;q.pop();
        if(vis[v]) continue;
        vis[v] = true;
        for(int i = head1[v];i;i = e1[i].next){
            if(g[e1[i].to] > g[v] + e1[i].w){
                g[e1[i].to] = g[v] + e1[i].w;
                q.push(MP(g[e1[i].to],e1[i].to));
            }
        }
    }
}

struct Node{
    int g,h,id;
    Node(){g = h = id = 0;}

    bool operator < (const Node &t) const {
        return (g+h) > (t.g+t.h);
    }
};

inline int bfs(){
    std::priority_queue<Node> q;
    int times[MAXN] = {0};
    Node v;v.id = S;q.push(v);
    while(!q.empty()){
        v = q.top();q.pop();
        times[v.id]++;//DEBUG(v.h);DEBUG(v.g);DEBUG(v.id);DEBUG(times[v.id]);
        if(times[v.id] == K && v.id == T) return v.h+v.g;
        if(times[v.id] > K) continue;
        Node vv;
        for(int i = head[v.id];i;i = e[i].next){
            vv.id = e[i].to;
            vv.h = v.h+e[i].w;
            vv.g = g[e[i].to];
            q.push(vv);
        }
    }
    return -1;
}

int main(){
    scanf("%d%d",&n,&m);
    FOR(i,1,m){
        int u,v,w;scanf("%d%d%d",&u,&v,&w);
        add(u,v,w);//add(v,u,w);
    }
    scanf("%d%d%d",&S,&T,&K);
    if(S == T) K++;
    dij(T);printf("%d\n",bfs());
    return 0;
}
