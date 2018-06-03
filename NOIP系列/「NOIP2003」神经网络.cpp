#include <iostream>
#include <cstdio>
#include <stack>
#include <queue>

const int MAXM = 30000 + 5;
const int MAXN = 100 + 5;

struct Edge{
    int to,w,next;
}e[MAXM];

int head[MAXN],cnt;
int c[MAXN],in[MAXN];
std::queue<int> q;

inline void add(int u,int v,int w){
    e[++cnt] = Edge{v,w,head[u]};
    head[u] = cnt;
}

void topsort(){
    while(!q.empty()){
        int v = q.front();
        q.pop();
        if(c[v] <= 0){
            for(int i = head[v];i;i = e[i].next){
                in[e[i].to]--;
                if(!in[e[i].to])
                    q.push(e[i].to);
            }
            continue;
        }
        for(int i = head[v];i;i = e[i].next){
            c[e[i].to] += e[i].w * c[v];
            in[e[i].to]--;
            if(!in[e[i].to])
                q.push(e[i].to);
        }
    }
}

int main(){
    int N,P;
    scanf("%d%d",&N,&P);
    for(int p,i = 1;i <= N;i++){
        scanf("%d%d",&c[i],&p);
        if(c[i] != 0) q.push(i);
        else c[i] -= p;
    }
    for(int u,v,w,i = 1;i <= P;i++){
        scanf("%d%d%d",&u,&v,&w);
        add(u,v,w);
        in[v]++;
    }
    topsort();
    bool flag = false;
    for(int i = 1;i <= N;i++){
        if(!head[i] && c[i] > 0){
            printf("%d %d\n",i,c[i]);
            flag = true;
        }
    }
    if(!flag) printf("NULL\n");
    return 0;
}
