/*
 * Time: 2019-11-29 20:51:06
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
#define U unsigned
#define P std::pair
#define LL long long
#define pb push_back
#define MP std::make_pair
#define all(x) x.begin(),x.end()
#define CLR(i,a) memset(i,a,sizeof(i))
#define FOR(i,a,b) for(int i = a;i <= b;++i)
#define ROF(i,a,b) for(int i = a;i >= b;--i)
#define DEBUG(x) std::cerr << #x << '=' << x << std::endl

const int MAXN = 4e5 + 5;

struct Edge{
    int to,nxt;
}e[MAXN<<1];

int head[MAXN],cnt;

inline void add(int u,int v){
    e[++cnt] = (Edge){v,head[u]};head[u] = cnt;
    e[++cnt] = (Edge){u,head[v]};head[v] = cnt;
}

int f[MAXN];

inline int find(int x){
    return x == f[x] ? x : f[x] = find(f[x]);
}

int n,m,k,now;
bool del[MAXN];
int opt[MAXN],ans[MAXN];

inline void merge(int x,int y){
    int fx = find(x),fy = find(y);
    if(fx == fy) return;
    now--;f[fy] = fx;
}

int main(){
    scanf("%d%d",&n,&m);
    FOR(i,1,n) f[i] = i;
    FOR(i,1,m){
        int u,v;scanf("%d%d",&u,&v);++u;++v;
        add(u,v);
    }
    scanf("%d",&k);
    FOR(i,1,k) scanf("%d",opt+i),del[++opt[i]] = 1;
    now = n-k;
    FOR(v,1,n){
        if(del[v]) continue;
        for(int i = head[v];i;i = e[i].nxt){
            if(del[e[i].to]) continue;
            merge(v,e[i].to);
        }
    }
    ans[k+1] = now;
    ROF(i,k,1){
        int v = opt[i];
        del[v] = 0;
        for(int i = head[v];i;i = e[i].nxt){
            if(del[e[i].to]) continue;
            merge(v,e[i].to);
        }
        now++;
        ans[i] = now;
    }
    FOR(i,1,k+1) printf("%d\n",ans[i]);
    return 0;
}
