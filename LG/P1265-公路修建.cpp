// 70pts TLE
#include <algorithm>
#include <iostream>
#include <cstring>
#include <cstdio>
#include <cmath>

#define DEBUG(x) std::cerr << #x << '=' << x << std::endl
const int MAXN = 5000 + 5;

int N,M,cnt;
double ans;

struct Point{
    int x,y;
}p[MAXN];

double cost(const Point &a,const Point &b){
    return sqrt((double)(a.x - b.x) * (double)(a.x - b.x) + (double)(a.y - b.y) * (double)(a.y - b.y));
}

struct Edge{
    int u,v;
    double w;
    
    bool operator < (const Edge &other) const{
        return w < other.w;
    }
}e[MAXN * MAXN];

int f[MAXN];

void init(){
    for(int i = 1;i <= N;i++)
        f[i] = i;
}

int find(int x){
    return f[x] == x ? x : f[x] = find(f[x]);
}

int main(){
    scanf("%d",&N);
    init();
    for(int i = 1;i <= N;i++)
        scanf("%d%d",&p[i].x,&p[i].y);
    for(int i = 1;i <= N;i++)
        for(int j = i + 1;j <= N;j++)
            e[++M] = (Edge){i,j,cost(p[i],p[j])};
    std::sort(e + 1,e + M + 1);
    for(int i = 1;i <= M;i++){
        int fu = find(e[i].u),fv = find(e[i].v);
        if(fu == fv) continue;
        ans += e[i].w;
        f[fu] = fv;
        if(++cnt == N - 1) break;
    }
    printf("%.2f",ans);
    return 0;
}
