/*
 * Author: RainAir
 * Time: 2019-11-08 18:44:40
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

const int MAXN = 2000+5;
const int MAXM = 2e5 + 5;

struct Edge{
    int to,nxt;
}e[MAXM<<1];
int head[MAXN],cnt;

inline void add(int u,int v){
    e[++cnt] = (Edge){v,head[u]};head[u] = cnt;
}

int n,m;
char str[233];
int ans[MAXN],low[MAXN],dfn[MAXN],col[MAXN];
// i+n : 1,i:0
int stk[MAXN],tp = 0,tot;
bool ins[MAXN];
int ts = 0;

inline void dfs(int v){
    dfn[v] = low[v] = ++ts;stk[++tp] = v;
    ins[v] = true;
    for(int i = head[v];i;i = e[i].nxt){
        if(!dfn[e[i].to]){
            dfs(e[i].to);
            low[v] = std::min(low[v],low[e[i].to]);
        }
        else if(ins[e[i].to]) low[v] = std::min(low[v],dfn[e[i].to]);
    }
    if(low[v] == dfn[v]){
        int t = -1;++tot;
        do{
            t = stk[tp--];
            ins[t] = false;
            col[t] = tot;
        }while(t != v);
    }
}

inline bool chk(int v,int k){ // force v -> k
    int t1 = head[v],t2 = head[v+n],t3 = cnt;
    tp = 0;tot = 0;ts = 0;
    add(v+(!k)*n,v+k*n);
    FOR(i,1,2*n) dfn[i] = low[i] = col[i] = ins[i] = 0;
    FOR(i,1,2*n) if(!dfn[i]) dfs(i);
    head[v] = t1;head[v+n] = t2;cnt = t3;
    FOR(i,1,n) if(col[i] == col[i+n]) return false;
    return true;
}

int main(){
    freopen("a.in","r",stdin);
    scanf("%d%d",&n,&m);
    FOR(i,1,m){
        int u,v,a,b;
        scanf("%d",&u);scanf("%s",str+1);
        a = str[1] == 'Y';
        scanf("%d",&v);scanf("%s",str+1);
        b = str[1] == 'Y';
        add(u+(!a)*n,v+n*b);add(v+(!b)*n,u+a*n);
    }
    FOR(i,1,2*n) if(!dfn[i]) dfs(i);
    FOR(i,1,n) if(col[i] == col[i+n]){
        puts("IMPOSSIBLE");
        return 0;
    }
    FOR(i,1,n){
        bool flag1 = chk(i,0),flag2 = chk(i,1);
        if(flag1 && flag2) putchar('?');
        else if(flag1) putchar('N');
        else putchar('Y');
    }
    puts("");
    return 0;
}
