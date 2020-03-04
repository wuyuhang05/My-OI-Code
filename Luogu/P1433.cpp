#include <algorithm>
#include <iostream>
#include <cstring>
#include <climits>
#include <cstdio>
#include <vector>
#include <cmath>
#include <queue>
#include <stack>
#include <map>
#include <set>

#define R register
#define LL long long
#define U unsigned
#define FOR(i,a,b) for(R int i = a;i <= b;++i)
#define RFOR(i,a,b) for(R int i = a;i >= b;--i)
#define CLR(i,a) memset(i,a,sizeof(i))
#define BR printf("--------------------\n")
#define DEBUG(x) std::cerr << #x << '=' << x << std::endl

const int MAXN = 15 + 5;

struct Point{
    double x,y;
}p[MAXN];

int N;

double dist(const Point &a,const Point &b){
    double dx = (double)(a.x-b.x),dy = (double)(a.y-b.y);
    return (double)std::sqrt((dx*dx + dy*dy));
}

double ans = (double)(INT_MAX);
bool vis[MAXN];

void dfs(int step,int last,double sum){
    if(sum > ans) return;
    if(step == N + 1){
        ans = std::min(ans,sum);return;
    }
    FOR(i,1,N){
        if(vis[i]) continue;
        vis[i] = true;
        double gx = dist(p[last],p[i]);
    //    DEBUG(gx);
        dfs(step+1,i,sum+dist(p[last],p[i]));
        vis[i] = false;
    }
}

int main(){
    scanf("%d",&N);
    FOR(i,1,N) scanf("%lf%lf",&p[i].x,&p[i].y);
    p[0].x = 0.0;p[0].y = 0.0;
    dfs(1,0,0.0);
    printf("%.2f\n",ans);
    return 0;
}
