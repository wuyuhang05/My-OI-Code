/*
 * Time: 2019-11-12 10:17:11
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
#define LL long long
#define pb push_back
#define MP std::make_pair
#define all(x) x.begin(),x.end()
#define CLR(i,a) memset(i,a,sizeof(i))
#define FOR(i,a,b) for(int i = a;i <= b;++i)
#define ROF(i,a,b) for(int i = a;i >= b;--i)
#define DEBUG(x) std::cerr << #x << '=' << x << std::endl

const int MAXN = 1e5 + 5;

struct Edge{
    int to,nxt;
}e[MAXN<<5];
int head[MAXN],cnt;

inline void add(int u,int v){
    e[++cnt] = (Edge){v,head[u]};head[u] = cnt;
    e[++cnt] = (Edge){u,head[v]};head[v] = cnt;
}

int val[MAXN];
int n;

struct Node{
    int x,y,id;

    Node(int x=0,int y=0,int id=0) : x(x),y(y),id(id) {}

    bool operator < (const Node &t) const {
        return x == t.x ? y < t.y : x < t.x;
    }
}a[MAXN];

inline void work(int limx,int limy){
    std::sort(a+1,a+n+1);
    int l = 1,r = 1,lst = 1;
    FOR(i,1,n){
        while(((a[l].x-a[i].x < limx) || (a[l].x-a[i].x == limx && a[i].y-a[l].y > limy)) && (l <= n)) ++l;
        while(((a[r].x-a[i].x < limx) || (a[r].x-a[i].x == limx && a[r].y-a[i].y <= limy)) && (r <= n)) ++r;
        // [l,r)
        if(l > n) break;
        val[a[i].id] += r-l;
        lst = std::max(lst,l);
        if(lst >= r) continue;
        add(a[lst].id,a[i].id);
        FOR(i,lst+1,r-1) add(a[i-1].id,a[i].id);
        lst = std::max(lst,r-1);
    }
}

LL ans = 0;
bool vis[MAXN];

inline void dfs(int v){
    ans += val[v];vis[v] = 1;
    for(int i = head[v];i;i = e[i].nxt){
        if(vis[e[i].to]) continue;
        dfs(e[i].to);
    }
}

int main(){
    scanf("%d",&n);
    int p1,p2;scanf("%d%d",&p1,&p2);
    FOR(i,1,n){
        int x,y;scanf("%d%d",&x,&y);
        a[i] = Node(x+y,x-y,i);
    }
    int dis = std::max(std::abs(a[p1].x-a[p2].x),std::abs(a[p1].y-a[p2].y));
    work(dis,dis);
    FOR(i,1,n) std::swap(a[i].x,a[i].y);
    work(dis,dis-1);
    dfs(p1);
    printf("%lld\n",ans);
    return 0;
}
