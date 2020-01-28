/*
 * Time: 2019-12-01 21:47:35
 */
#include <algorithm>
#include <iostream>
#include <cstring>
#include <climits>
#include <cstdlib>
#include <cstdio>
#include <bitset>
#include <vector>
#include <cmath>
#include <ctime>
#include <queue>
#include <stack>
#include <map>
#include <set>

#define fi first
#define se second
#define P std::pair
#define LL long long
#define pb push_back
#define MP std::make_pair
#define all(x) x.begin(),x.end()
#define CLR(i,a) memset(i,a,sizeof(i))
#define FOR(i,a,b) for(int i = a;i <= b;++i)
#define ROF(i,a,b) for(int i = a;i >= b;--i)
#define DEBUG(x) std::cerr << #x << '=' << x << std::endl

const int MAXN = 3000+5;
const int MAXM = 11;

struct Edge{
    int to,w,nxt;
}e[MAXN<<1];
int head[MAXN],cnt;

inline void add(int u,int v,int w){
    e[++cnt] = (Edge){v,w,head[u]};head[u] = cnt;
    e[++cnt] = (Edge){u,w,head[v]};head[v] = cnt;
}

int n,m,p;
int c[MAXN],d[MAXN];
int f[MAXN][(1<<MAXM)+1],g[(1<<MAXM)+1];
std::queue<int> q;
bool inq[MAXN];

inline void spfa(int S){
    while(!q.empty()){
        int v = q.front();q.pop();
        inq[v] = 0;
        for(int i = head[v];i;i = e[i].nxt){
            int gx = f[v][S]+e[i].w;
            if(gx < f[e[i].to][S]){
                f[e[i].to][S] = gx;
                if(!inq[e[i].to]) q.push(e[i].to);
            }
        }
    }
}

int main(){
//    freopen("1.in","r",stdin);
//    DEBUG(1);
    scanf("%d%d%d",&n,&m,&p);
    FOR(i,1,m){
        int u,v,w;scanf("%d%d%d",&u,&v,&w);
        add(u,v,w);
    }
    CLR(f,0x3f);
    FOR(i,0,p-1) scanf("%d%d",c+i,d+i),f[d[i]][1<<i] = 0,c[i]--;
    int U = 0;
    FOR(i,0,p-1) U |= (1<<c[i]);
    FOR(S,0,(1<<p)-1){
        FOR(i,1,n){
            for(int T = S;T;T = (T-1)&S){
                f[i][S] = std::min(f[i][S],f[i][T]+f[i][S-T]);
            }
            q.push(i);inq[i] = 1;
        }
        spfa(S);
    }
    CLR(g,0x3f);g[0] = 0;
    FOR(S,1,(1<<p)-1){
        int t = 0;
        FOR(i,0,p-1) if((S>>c[i])&1) t |= (1ll<<i);
        FOR(i,1,n) g[S] = std::min(g[S],f[i][t]);
        for(int T = S;T;T = (T-1)&S){
            g[S] = std::min(g[S],g[T]+g[S-T]);
        }
    }
    printf("%d\n",g[U]);
    return 0;
}
