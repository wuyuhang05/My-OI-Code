#include <iostream>
#include <cstdio>
#include <cstring>
#include <climits>

int N,M;
const int MAXN = 3000 + 5;
const int MAXM = 10000 + 5;
const double eps = 1e-10;

struct Edge{
    int to,next;
    double w;
}e[MAXM << 1];
int head[MAXN],cnt = 0;
double dist[MAXN];
bool inQueue[MAXN],flag;

inline void add(int u,int v,double w){
    e[++cnt].w = w;e[cnt].to = v;e[cnt].next = head[u];head[u] = cnt;
}

void spfa(int x){
    inQueue[x] = true;
    if(!flag) return;
    for(int i = head[x];i;i = e[i].next)
        if(dist[e[i].to] > dist[x] + e[i].w){
            if(inQueue[e[i].to]){
                flag = false;
                return;
            }
            dist[e[i].to] = dist[x] + e[i].w;
            spfa(e[i].to);
        }
    inQueue[x] = false;
    return;
}


bool check(double mid){
    flag = true;
    for(int i = 1;i <= N;i++){
        dist[i] = 0;
        inQueue[i] = false;
    }
    for(int i = 1;i <= cnt;i++) e[i].w -= mid;
    for(int i = 1;i <= N;i++){
        spfa(i);
        if(!flag) break;
    }
    for(int i = 1;i <= cnt;i++) e[i].w += mid;
    return flag;
}


int main(){
    double L = INT_MAX,R = 0;
    scanf("%d%d",&N,&M);
    for(int u,v,i = 1;i <= M;i++){
        double w;
        scanf("%d%d%lf",&u,&v,&w);
        add(u,v,w);
        R = std::max(R,w);
        L = std::min(L,w);
    }
    double ans;
    while(L + eps < R){
        double mid = (L + R) / 2;
        if(!check(mid)) R = mid-eps,ans = R;
        else L = mid + eps;
    }
    printf("%.8lf",ans);
    return 0;
}
