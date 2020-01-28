/*
 * Time: 2019-11-27 13:12:54
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

const int MAXN = 1000000+5;

struct Edge{
    int to,nxt;
}e[MAXN<<1];
int head[MAXN],cnt;
int n,m;

inline void add(int u,int v){
    e[++cnt] = (Edge){v,head[u]};head[u] = cnt;
    e[++cnt] = (Edge){u,head[v]};head[v] = cnt;
}

struct Node{
    int id;
    Node *pre,*suf;

    inline void del(){
        if(pre) pre->suf = suf;
        if(suf) suf->pre = pre;
    }

    inline void insert(Node *p){
        p->suf = suf;p->pre = this;
        if(suf) suf->pre = p;
        suf = p;
    }
}h[MAXN],p[MAXN];

int ans[MAXN],tot[MAXN];
bool vis[MAXN];

inline void build(){
    FOR(i,1,n) p[i].id = i,h[0].insert(&p[i]);
    int now = 0;
    ROF(i,n,1){
        while(h[now+1].suf) now++;
        while(!h[now].suf) now--;
        int v = h[now].suf->id;
        h[now].suf->del();
        ans[i] = v;vis[v] = true;
        for(int i = head[v];i;i = e[i].nxt){
            if(vis[e[i].to]) continue;
            p[e[i].to].del();
            h[++tot[e[i].to]].insert(&p[e[i].to]);
        }
    }
}

int deg[MAXN];

inline void work(){
    CLR(vis,0);int res = 0;
//    FOR(i,1,n) printf("%d ",ans[i]);puts("");
    ROF(k,n,1){
        int v = ans[k];
        for(int i = head[v];i;i = e[i].nxt){
            deg[v] += vis[e[i].to];
        }
        res = std::max(res,deg[v]+1);
        vis[v] = 1;
    }
    printf("%d\n",res);
}

int main(){
    scanf("%d%d",&n,&m);
    FOR(i,1,m){
        int u,v;scanf("%d%d",&u,&v);
        add(u,v);
    }
    build();
    work();
    return 0;
}
