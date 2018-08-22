#include <iostream>
#include <cstdio>
#include <cstring>
#include <stack>

const int MAXN = 10000 + 5;
const int MAXM = 50000 + 5;

struct Edge{
    int to,next;
}e[MAXM];

int head[MAXN],dfn[MAXN],low[MAXN],outall[MAXN],out[MAXN],id[MAXN],num;
bool noSCC[MAXN];
int N,M,cnt,timer;

inline void add(int u,int v){
    e[++cnt] = Edge{v,head[u]};
    head[u] = cnt;
}

std::stack<int> s;

void dfs(int v){
    dfn[v] = low[v] = ++timer;
    s.push(v);noSCC[v] = true;
    for(int i = head[v];i;i = e[i].next){
        if(!dfn[e[i].to]){
            dfs(e[i].to);
            low[v] = std::min(low[v],low[e[i].to]);
        }
        else
            if(noSCC[e[i].to])
                low[v] = std::min(low[v],dfn[e[i].to]);
    }
    if(low[v] == dfn[v]){
        int x;
        num++;
        do{
            x = s.top();s.pop();
            noSCC[x] = false;
            id[x] = num;outall[num]++;
        }while(x != v);
    }
}

int main(){
    scanf("%d%d",&N,&M);
    for(int u,v,i = 1;i <= M;i++){
        scanf("%d%d",&u,&v);
        add(u,v);
    }
    for(int i = 1;i <= N;i++)
        if(!dfn[i])
            dfs(i);
    for(int n = 1;n <= N;n++){
        for(int i = head[n];i;i = e[i].next){
            if(id[n] != id[e[i].to])
                out[id[n]]++;
        }
    }
    int t = 0;
    for(int i = 1;i <= num;i++){
        if(!out[i]){
            if(t) {
                puts("0");return 0;
            }
            t = i;
        }
    }
    printf("%d",outall[t]);
    return 0;
}
