#include <algorithm>
#include <iostream>
#include <cstring>
#include <climits>
#include <cstdio>
#include <queue>

#define LL long long
const int MAXN = 10000 + 5;
const int MAXM = 50000 + 5;

struct Edge{
    int to,w,next;
}e[MAXM * 2];

int N,M;
int head[MAXN],cnt;
LL power[MAXN],B,L,R,dist[MAXN];
bool inQueue[MAXN];

inline void add(int u,int v,int w){
    e[++cnt] = (Edge){v,w,head[u]};
    head[u] = cnt;
    e[++cnt] = (Edge){u,w,head[v]};
    head[v] = cnt;
}

bool check(int mid){
    if(power[1] > mid) return false;
    for(int i = 1;i <= N;i++){
        dist[i] = INT_MAX;
        inQueue[i] = false;
    }
    std::queue<int> q;
    q.push(1);
    dist[1] = 0;
    inQueue[1] = true;
    while(!q.empty()){
        int v = q.front();q.pop();
        inQueue[v] = false;
        for(int i = head[v];i;i = e[i].next){
            if(dist[e[i].to] > dist[v] + e[i].w){
                dist[e[i].to] = dist[v] + e[i].w;
                if(power[e[i].to] <= mid && !inQueue[e[i].to]){
                    q.push(e[i].to);
                    inQueue[e[i].to] = true;
                }
            }
        }
    }
    if(dist[N] < B) return true;
    else return false;
}

int main(){
    scanf("%d%d%lld",&N,&M,&B);
    for(int i = 1;i <= N;i++){
        scanf("%lld",&power[i]);
        R = (power[i] > R) ? power[i] : R;
    }
    L = (power[1] > power[N]) ? power[1] : power[N];
    for(int u,v,w,i = 1;i <= M;i++){
        scanf("%d%d%d",&u,&v,&w);
        add(u,v,w);
    }
    if(!check(INT_MAX)){
        printf("AFK\n");
        return 0;
    }
    while(L <= R){
        int mid = (L + R) >> 1;
        if(check(mid)) R = mid - 1;
        else L = mid + 1;
    }
    printf("%lld\n",L);
    //getchar();getchar();
    return 0;
}
