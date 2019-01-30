#pragma comment(linker, "/STACK:102400000,102400000")
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

const int MAXN = 200000+5;
const int MAXK = 1000000;

struct Edge{
    int to,w,next;
}e[MAXN<<1];
int head[MAXN],size[MAXN],max[MAXN],dis[MAXN],dep[MAXN],root,cnt,top;
int N,K,sum,minw[MAXK+60];
bool vis[MAXN];

inline void add(int u,int v,int w){
    e[++cnt] = (Edge){v,w,head[u]};head[u] = cnt;
}

struct Node{
    int dis,dep;
    bool operator < (const Node &t) const {
        return dis == t.dis ? dep < t.dep : dis < t.dis;
    }
    bool operator == (const Node &t) const {
        return dis == t.dis && dep == t.dep;
    }
}p[MAXN];

inline void find(int l,int r,Node x,int w){
    int dis = K-x.dis,dep = x.dep,mid;
    while(r-l > 2){
        int mid = (l + r) >> 1;
        if(p[mid].dis > dis) r = mid;
        else l = mid;
    }
    ROF(i,r,l){
        if(p[i].dis != dis) continue;
        mid = i;break;
    }
    if(p[mid].dis != dis) return;
    for(int i = mid;;--i){
        if(p[i].dis != dis) break;
        if(p[i] == x) continue;
        minw[p[i].dep+dep] += w;
    }
    for(int i = mid+1;;++i){
        if(p[i].dis != dis) break;
        if(p[i] == x) continue;
        minw[p[i].dep+dep] += w;
    }
}

void getroot(int v,int fa){
    size[v] = 1;max[v] = 0;
    for(int to,i = head[v];i;i = e[i].next){
        if((to = e[i].to) == fa || vis[to]) continue;
        getroot(to,v);size[v] += size[to];
        max[v] = std::max(max[v],size[to]);
    }
    max[v] = std::max(max[v],sum-size[v]);
    root = max[root] > max[v] ? v : root;
}

void getdis(int v,int fa){
    p[++top] = (Node){dis[v],dep[v]};
    for(int to,i = head[v];i;i = e[i].next){
        if((to = e[i].to) == fa || vis[to]) continue;
        dis[to] = dis[v] + e[i].w;dep[to] = dep[v] + 1;
        getdis(to,v);
    }
}

inline void calc(int v,int len,int w,int depp){
    dis[v] = len;dep[v] = depp;top = 0;
    getdis(v,0);std::sort(p+1,p+top+1);
    FOR(i,1,top){
        if(p[i].dis > K) break;
        if(p[i].dis == p[i-1].dis) continue;
        find(0,top,p[i],w);
    }
}

void divide(int v){
    vis[v] = true;calc(v,0,1,0);
    for(int to,i = head[v];i;i = e[i].next){
        if(vis[(to = e[i].to)]) continue;
        calc(to,e[i].w,-1,1);max[root = 0] = sum = size[to];
        getroot(to,0);divide(root);
    }
}

int main(){
    scanf("%d%d",&N,&K);
    if(!K){
        puts("0");return 0;
    }
    FOR(i,1,N-1){
        int u,v,w;scanf("%d%d%d",&u,&v,&w);++u;++v;
        add(u,v,w);add(v,u,w);
    }
    max[root = 0] = sum = N;getroot(1,0);divide(root);
    FOR(i,1,MAXK){
        if(minw[i] >= 1){
            printf("%d\n",i);
            return 0;
        }
    }
    puts("-1");
    return 0;
}