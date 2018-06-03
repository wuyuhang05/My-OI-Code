#include <iostream>
#include <cstdio>
#include <cstring>

const int MAXN = 500000 + 5;

struct Edge{
    int to,next;
}e[MAXN * 2];

struct Query{
    int to,next,same,num;
    bool flag;

    Query() {flag = false;}
}q[MAXN * 2];

bool vis[MAXN];
int head[MAXN],que[MAXN],fa[MAXN];
int N,M,S,cnt1 = 0,cnt2 = 0,ans[MAXN];

inline void add_edge(int u,int v){
    e[++cnt1] = (Edge) {v,head[u]};
    head[u] = cnt1;
    e[++cnt1] = (Edge) {u,head[v]};
    head[v] = cnt1;
}

inline void add_query(int u,int v,int i){
    q[++cnt2].to = v;
    q[cnt2].same = cnt2 + 1;
    q[cnt2].next = que[u];
    q[cnt2].num = i;
    que[u] = cnt2;
    q[++cnt2].to = u;
    q[cnt2].same = cnt2 - 1;
    q[cnt2].next = que[v];
    q[cnt2].num = i;
    que[v] = cnt2;
}

int find(int x){
    if(fa[x] == x) return fa[x];
    return fa[x] = find(fa[x]);
}

void Union(int x,int y){
    fa[find(y)] = find(x);
}

void lca(int x,int f){
    fa[x] = x;
    vis[x] = true;
    for(int i = head[x];i;i = e[i].next){
        if(e[i].to != f && !vis[e[i].to]){
            lca(e[i].to,x);
            Union(x,e[i].to);
        }
    }
    for(int i = que[x];i;i = q[i].next){
        if(!q[i].flag && vis[q[i].to]){
            ans[q[i].num] = find(q[i].to);
            q[i].flag = true;
            q[q[i].same].flag = 1;
        }
    }
}

int main(){
    scanf("%d%d%d",&N,&M,&S);
    for(int u,v,i = 1;i <= N-1;i++){
        fa[i] = i;
        ans[i] = i;
        scanf("%d%d",&u,&v);
        add_edge(u,v);
    }
    fa[N] = N;
    for(int u,v,i = 1;i <= M;i++){
        scanf("%d%d",&u,&v);
        add_query(u,v,i);
    }
    lca(S,0);
    for(int i = 1;i <= M;i++)
        printf("%d%c",ans[i],'\n');
    getchar();getchar();
    return 0;
}
