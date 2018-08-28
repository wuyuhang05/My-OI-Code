#include <iostream>
#include <cstdio>
#include <cstring>

const int MAXN = 100000 + 5;
const int MAXM = MAXN * 2;

struct Edge{
    int to,next;
}e[MAXM];

int head[MAXN],cnt,in[MAXN];
int N,M;

inline void add(int u,int v){
    e[++cnt] = (Edge){v,head[u]};
    head[u] = cnt;
}

void topsort(){
    for(int i = 1;i <= N;i++)
        
}

int main(){
    scanf("%d%d",&N,&M);
    for(int u,v,i = 1;i <= M;i++){
        scanf("%d%d",&u,&v);
        add(v,u);
        in[u]++;
    }

    return 0;
}
