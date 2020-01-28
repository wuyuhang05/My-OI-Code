/*
 * Time: 2019-11-27 13:27:16
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

const int MAXN = 200+5;

struct Edge{
    int to,nxt;
}e[(MAXN*MAXN)<<1];
int head[MAXN],cnt;

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
        p->pre = this;p->suf = suf;
        if(suf) suf->pre = p;
        suf = p;
    }
}h[MAXN],p[MAXN];
int ans[MAXN],tot[MAXN];
int n,m;
bool vis[MAXN];

inline void build(){
    FOR(i,1,n) h[0].insert(&p[i]),p[i].id = i;
    int now = 0;
    ROF(i,n,1){
        while(h[now+1].suf) ++now;
        while(!h[now].suf) --now;
        int v = h[now].suf->id;h[now].suf->del();
        vis[v] = true;ans[i] = v;
        for(int i = head[v];i;i = e[i].nxt){
            if(vis[e[i].to]) continue;
            p[e[i].to].del();
            h[++tot[e[i].to]].insert(&p[e[i].to]);
        }
    }
}

inline void work(){
    int ans = 0;CLR(vis,0);
//    FOR(i,1,n) DEBUG(::ans[i]);
    FOR(i,1,n){
        int v = ::ans[i];
        if(vis[v]) continue;
        ans++;
        vis[v] = true;
        for(int i = head[v];i;i  = e[i].nxt){
            vis[e[i].to] = true;
        }
    }
    printf("%d\n",ans);
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
