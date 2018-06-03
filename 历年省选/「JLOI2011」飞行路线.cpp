#include <iostream>
#include <cstdio>
#include <cstring>
#include <climits>
#include <queue>
#include <algorithm>

const int MAXN = 10000 + 5;
const int MAXM = 50000 + 5;
const int MAXK = 10 + 5;

int N,M,K,S,T;
int dist[MAXN][MAXK];
int head[MAXN],cnt;
bool inQueue[MAXN][MAXK];

struct Edge{
    int to,w,next;
}e[MAXM * 2];

inline void add(int u,int v,int w){
    e[++cnt].w = w;e[cnt].to = v;e[cnt].next = head[u];head[u] = cnt;
}

void spfa(){
    memset(dist,0x7f,sizeof(dist));
    memset(inQueue,false,sizeof(inQueue));
    std::queue<std::pair<int,int> > q;
    q.push(std::make_pair(S,0));
    inQueue[S][0] = true;
    dist[S][0] = 0;
    while(!q.empty()){
        int v = q.front().first;
        int step = q.front().second;
        q.pop();
        inQueue[v][step] = false;
        for(int i = head[v];i;i = e[i].next){
            int to = e[i].to;
            if(dist[v][step] + e[i].w < dist[to][step]){
                dist[to][step] = dist[v][step] + e[i].w;
                if(!inQueue[to][step]){
                    inQueue[to][step] = true;
                    q.push(std::make_pair(to,step));
                }
            }
            if(dist[v][step] < dist[to][step+1] && step < K){
    			dist[to][step+1] = dist[v][step];
    			if(!inQueue[to][step+1]){
    				inQueue[to][step+1]=1;
					q.push(std::make_pair(to,step + 1));
 				}
    		}
        }
    }
    int ans = INT_MAX;
    for(int i = 0;i <= K;i++){
        ans = std::min(ans,dist[T][i]);
    }
    printf("%d",ans);
}

int main(){
    scanf("%d%d%d%d%d",&N,&M,&K,&S,&T);
    for(int i = 1;i <= M;i++){
        int u,v,w;
        scanf("%d%d%d",&u,&v,&w);
        add(u,v,w);add(v,u,w);
    }
    spfa();
    return 0;
}
