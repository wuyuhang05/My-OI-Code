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

#define Re register
#define LL long long
#define U unsigned
#define FOR(i,a,b) for(Re int i = a;i <= b;++i)
#define ROF(i,a,b) for(Re int i = a;i >= b;--i)
#define SFOR(i,a,b,c) for(Re int i = a;i <= b;i+=c)
#define SROF(i,a,b,c) for(Re int i = a;i >= b;i-=c)
#define CLR(i,a) memset(i,a,sizeof(i))
#define BR printf("--------------------\n")
#define DEBUG(x) std::cerr << #x << '=' << x << std::endl

const int MAXN = 200000+5;

struct Edge{
    int to,next;
}e[MAXN<<1];

int head[MAXN],cnt,size[MAXN],dfn[MAXN];

inline void add(int u,int v){
    e[++cnt] = (Edge){v,head[u]};head[u] = cnt;
}

void dfs(int v,int fa){
    static int ts = 0;
    dfn[v] = ++ts;size[v] = 1;
    for(int i = head[v];i;i = e[i].next){
        if(e[i].to == fa) continue;
        dfs(e[i].to,v);
        size[v] += size[e[i].to];
    }
}

int w[MAXN<<2],a[MAXN];
#define lc x<<1
#define rc x<<1|1

inline void pushup(int x){
    w[x] = w[lc] + w[rc];
}

inline void build(int x,int l,int r){
    if(l == r){
        w[x] = 1;
        return;
    }
    int mid = (l + r) >> 1;
    build(lc,l,mid);build(rc,mid+1,r);
    pushup(x);
}

inline void update(int x,int l,int r,int pos){
    if(l == r){
        w[x] ^= 1;
        return;
    } 
    int mid = (l + r) >> 1;
    if(pos <= mid) update(lc,l,mid,pos);
    else update(rc,mid+1,r,pos);
    pushup(x);
}

inline int query(int x,int l,int r,int L,int R){
    if(L == l && R == r) return w[x];
    int mid = (l + r) >> 1;
    if(R <= mid) return query(lc,l,mid,L,R);
    if(L > mid) return query(rc,mid+1,r,L,R);
    return query(lc,l,mid,L,mid) + query(rc,mid+1,r,mid+1,R);
}

int N,M;

int main(){
    scanf("%d",&N);
    FOR(i,1,N-1){
        int u,v;scanf("%d%d",&u,&v);
        add(u,v);add(v,u);
    }
    dfs(1,0);
    build(1,1,N);
    scanf("%d",&M);
    FOR(i,1,M){
        char opt[2];scanf("%s",opt);
        int x;scanf("%d",&x);
        if(opt[0] == 'C') update(1,1,N,dfn[x]);
        else printf("%d\n",query(1,1,N,dfn[x],dfn[x]+size[x]-1));
    }
    return 0;
}