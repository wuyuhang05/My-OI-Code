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

const int MAXN = 100000+5;

int head[MAXN],id[MAXN],top[MAXN],dfn[MAXN],size[MAXN],dep[MAXN],son[MAXN],fa[MAXN];
int col[MAXN],val[MAXN],root[MAXN];
int cnt,tot,N,M;

struct Edge{
    int to,next;
}e[MAXN<<1];

inline void add(int u,int v){
    e[++cnt] = (Edge){v,head[u]};head[u] = cnt;
}

struct Node{
    int l,r,sum,max;
    #define lc (p[x].l)
    #define rc (p[x].r)
    #define sm(x) (p[x].sum)
    #define mx(x) (p[x].max)
}p[MAXN<<5];

inline void pushup(int x){
    sm(x) = sm(lc) + sm(rc);
    mx(x) = std::max(mx(lc),mx(rc));
}

void clear(int x){
    p[x].l = p[x].r = sm(x) = mx(x) = 0;
}

void insert(int &x,int l,int r,int pos,int val){
    if(!x) x = ++tot;
    if(l == r){
        mx(x) = sm(x) = val;
        return;
    }
    int mid = (l + r) >> 1;
    if(pos <= mid) insert(lc,l,mid,pos,val);
    else insert(rc,mid+1,r,pos,val);
    pushup(x);
}

inline void del(int &x,int l,int r,int pos){
    if(l == r){
        clear(x);x = 0;
        return;
    }
    int mid = (l + r) >> 1;
    if(pos <= mid) del(lc,l,mid,pos);
    else del(rc,mid+1,r,pos);
    pushup(x);
    if(!lc && !rc){
        clear(x);x = 0;
    }
}

inline int querysum(int x,int l,int r,int L,int R){
    if(!x) return 0;
    if(l == L && r == R) return sm(x);
    int mid = (l + r) >> 1;
    if(R <= mid) return querysum(lc,l,mid,L,R);
    if(L > mid) return querysum(rc,mid+1,r,L,R);
    return querysum(lc,l,mid,L,mid) + querysum(rc,mid+1,r,mid+1,R);
}

inline int querymax(int x,int l,int r,int L,int R){
    if(!x) return 0;
    if(l == L && r == R) return mx(x);
    int mid = (l + r) >> 1;
    if(R <= mid) return querymax(lc,l,mid,L,R);
    if(L > mid) return querymax(rc,mid+1,r,L,R);
    return std::max(querymax(lc,l,mid,L,mid),querymax(rc,mid+1,r,mid+1,R));
}

void dfs1(int v){
    size[v] = 1;
    for(int i = head[v];i;i = e[i].next){
        if(e[i].to == fa[v]) continue;
        dep[e[i].to] = dep[v] + 1;
        fa[e[i].to] = v;dfs1(e[i].to);
        size[v] += size[e[i].to];
        son[v] = (size[son[v]] < size[e[i].to]) ? e[i].to : son[v];
    }
}

void dfs2(int v,int tp){
    static int ts = 0;
    id[dfn[v] = ++ts] = v;top[v] = tp;
    if(son[v]) dfs2(son[v],tp);
    for(int i = head[v];i;i = e[i].next){
        if(e[i].to == fa[v] || e[i].to == son[v]) continue;
        dfs2(e[i].to,e[i].to);
    }
}

void change1(int x,int y){
    del(root[col[x]],1,N,dfn[x]);
    col[x] = y;
    insert(root[col[x]],1,N,dfn[x],val[x]);
}

void change2(int x,int y){
    val[x] = y;
    insert(root[col[x]],1,N,dfn[x],val[x]);
}

int query1(int x,int y){
    int res = 0,c = col[x];
    while(top[x] != top[y]){
        if(dep[top[x]] < dep[top[y]]) std::swap(x,y);
        res += querysum(root[c],1,N,dfn[top[x]],dfn[x]);
        x = fa[top[x]];
    }
    if(dep[x] > dep[y]) std::swap(x,y);
    return res + querysum(root[c],1,N,dfn[x],dfn[y]);
}

int query2(int x,int y){
    int res = 0,c = col[x];
    while(top[x] != top[y]){
        if(dep[top[x]] < dep[top[y]]) std::swap(x,y);
        res = std::max(res,querymax(root[c],1,N,dfn[top[x]],dfn[x]));
        x = fa[top[x]];
    }
    if(dep[x] > dep[y]) std::swap(x,y);
    return std::max(res,querymax(root[c],1,N,dfn[x],dfn[y]));
}

int main(){
    //freopen("1.in","r",stdin);
    //freopen("users.out","w",stdout);
    scanf("%d%d",&N,&M);
    FOR(i,1,N) scanf("%d%d",val+i,col+i);
    FOR(i,1,N-1){
        int u,v;scanf("%d%d",&u,&v);
        add(u,v);add(v,u);
    }
    dep[1] = 1;dfs1(1);dfs2(1,1);
    FOR(i,1,N) insert(root[col[i]],1,N,dfn[i],val[i]);
    FOR(i,1,M){
        char ch[4];scanf("%s",ch+1);
        int x,y;scanf("%d%d",&x,&y);
        if(ch[1] == 'C'){
            if(ch[2] == 'C') change1(x,y);
            if(ch[2] == 'W') change2(x,y);
        }
        if(ch[1] == 'Q'){
            if(ch[2] == 'S') printf("%d\n",query1(x,y));
            if(ch[2] == 'M') printf("%d\n",query2(x,y));
        }
    }
    return 0;
}