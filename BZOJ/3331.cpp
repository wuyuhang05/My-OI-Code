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

#define Re register
#define LL long long
#define U unsigned
#define FOR(i,a,b) for(Re int i = a;i <= b;++i)
#define ROF(i,a,b) for(Re int i = a;i >= b;--i)
#define SFOR(i,a,b,c) for(Re int i = a;i <= b;i+=c)
#define SROF(i,a,b,c) for(Re int i = a;i >= b;i-=c)
#define CLR(i,a) memset(i,a,sizeof(i))
#define BR printf("--------------------\n")
#define DEBUG(x) std::cerr << #x << '=' << x << std::endl

const int MAXN = 250000+5;
const int MAXM = 450000+5;

struct Edge{
    int to,next;
}e1[MAXM<<1],e2[MAXM<<1];
float log2N;
int head1[MAXN],head2[MAXN],cnt1,cnt2;
int dfn[MAXN],low[MAXN],bel[MAXN],st[MAXN],top;
int f[MAXN][50],val[MAXN],tot,d[MAXN];
int N,M,Q;

inline void add1(int u,int v){
    e1[++cnt1] = (Edge){v,head1[u]};head1[u] = cnt1;
}

inline void add2(int u,int v){
    e2[++cnt2] = (Edge){v,head2[u]};head2[u] = cnt2;
}

void dfs1(int v){
    static int ts = 0;
    dfn[v] = low[v] = ++ts;st[++top] = v;
    for(int i = head1[v];i;i = e1[i].next){
        if(!dfn[e1[i].to]){
            dfs1(e1[i].to);low[v] = std::min(low[v],low[e1[i].to]);
            if(low[e1[i].to] >= dfn[v]){
                tot++;int t = -1;
                do{
                    t = st[top--];add2(tot,t);add2(t,tot);
                }while(t != e1[i].to);
                add2(tot,v);add2(v,tot);
            }
        }
        else low[v] = std::min(low[v],dfn[e1[i].to]);
    }
}

void dfs2(int v){
    FOR(i,1,log2N){
        if(d[v] <= (1<<i)) break;
        f[v][i] = f[f[v][i-1]][i-1];
    }
    for(int i = head2[v];i;i = e2[i].next){
        if(e2[i].to == f[v][0]) continue;
        f[e2[i].to][0] = v;
        d[e2[i].to] = d[v] + 1;
        dfs2(e2[i].to);
    }
}

int lca(int x,int y){
    int dx = d[x],dy = d[y];
    if(dx != dy){
        if(dx < dy) std::swap(x,y),std::swap(dx,dy);
        int d = dx - dy;
        FOR(i,0,log2N) if(d & (1<<i)) x = f[x][i];
    }
    if(x == y) return x;
    ROF(i,log2N,0){
        if(f[x][i] == f[y][i]) continue;
        x = f[x][i],y = f[y][i];
    }
    return f[x][0];
}

void dfs3(int v,int fa){
    // printf("%d %d\n",v,fa);
    for(int i = head2[v];i;i = e2[i].next){
        if(e2[i].to == fa) continue;
        dfs3(e2[i].to,v);val[v] += val[e2[i].to];
    }
}

int main(){
    // freopen("1.in","r",stdin);
    // freopen("1.out","w",stdout);
    scanf("%d%d%d",&N,&M,&Q);tot = N;
    FOR(i,1,M){
        int u,v;scanf("%d%d",&u,&v);
        add1(u,v);add1(v,u);
    }
    log2N = log2(tot);
    FOR(i,1,N) if(!dfn[i]) dfs1(1);
    d[1] = 1;dfs2(1);
    FOR(i,1,Q){
        int x,y;scanf("%d%d",&x,&y);
        int l = lca(x,y);
        val[x]++;val[y]++;val[l]--;val[f[l][0]]--;
        //printf("%d\n",l);
    }
    dfs3(1,0);
    FOR(i,1,N) printf("%d\n",val[i]);
    return 0;
}
/*
4 4 2
1 2
1 3
2 3
1 4
4 2
4 3
*/