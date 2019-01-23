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

#define fi first
#define se second
#define U unsigned
#define Re register
#define LL long long
#define MP std::make_pair
#define CLR(i,a) memset(i,a,sizeof(i))
#define FOR(i,a,b) for(Re int i = a;i <= b;++i)
#define ROF(i,a,b) for(Re int i = a;i >= b;--i)
#define SFOR(i,a,b,c) for(Re int i = a;i <= b;i+=c)
#define SROF(i,a,b,c) for(Re int i = a;i >= b;i-=c)
#define DEBUG(x) std::cerr << #x << '=' << x << std::endl

const int MAXN = 50+5;
const double EPS = 1e-8;
const int MAXM = 100000+5;

struct Edge{
    int u,v;double w;
}e[MAXM<<1];
int N,M,cnt,root,tot;
int b[MAXN],vis[MAXN],id[MAXN],pre[MAXN];
double a[MAXN],ans,in[MAXN];

inline bool equal(double a,double b){
    return std::fabs(a-b) <= EPS;
}

inline void add(int u,int v,double w){
    e[++cnt] = (Edge){u,v,w};
}

inline void work(){
    root = 1;
    while(true){
        //DEBUG(N);
        int tot = 0;
        FOR(i,1,N) id[i] = vis[i] = 0,in[i] = INT_MAX*1.0;
        FOR(i,1,cnt){
            if(e[i].u != e[i].v && e[i].w < in[e[i].v]){
                in[e[i].v] = e[i].w;
                pre[e[i].v] = e[i].u;
            }
        }
        in[root] = 0;
        FOR(i,1,N){
            ans += in[i];int u;
            for(u = i;u != root && i != vis[u] && !id[u];u = pre[u]) vis[u] = i;
            if(!id[u] && u != root){
                id[u] = ++tot;
                for(int v = pre[u];v != u;v = pre[v]) id[v] = tot;
            }
        }
        if(!tot) return;
        FOR(i,1,N) if(!id[i]) id[i] = ++tot;
        FOR(i,1,cnt){
            double t = in[e[i].v];
            if((e[i].u = id[e[i].u]) != (e[i].v = id[e[i].v])){
                e[i].w -= t;
            }
        }
        N = tot;root = id[root];
    }
}

int main(){
    scanf("%d",&tot);N = 2;
    FOR(i,1,tot){
        scanf("%lf%d",a+N,b+N);
        if(!b[N]) continue;
        add(1,N,a[N]);vis[i] = N++;
    }--N;
    scanf("%d",&M);
    FOR(i,1,M){
        int u,v;double w;
        scanf("%d%d%lf",&u,&v,&w);
        u = vis[u],v = vis[v];
        if(u && v){
            a[v] = std::min(a[v],w);
            e[++cnt] = (Edge){u,v,w};
        }
    }
    FOR(i,2,N){
        //DEBUG(b[i]);DEBUG(a[i]);
        ans += 1.0*(b[i]-1)*a[i];
    }
    //DEBUG(ans);
    work();
    printf("%.2f\n",ans);
    //system("pause");
    return 0;
}