/*
 * Author: RainAir
 * Time: 2019-10-12 09:06:50
 */
#pragma GCC optimize(2)
#pragma GCC optimize(3)
#pragma GCC optimize("Ofast")
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
#define FOR(i,a,b) for(register int i = a;i <= b;++i)
#define ROF(i,a,b) for(register int i = a;i >= b;--i)
#define DEBUG(x) std::cerr << #x << '=' << x << std::endl

const int MAXN = 5e4 + 5;
const int MAXM = 1e5 + 5;

struct Edge{
    int to,nxt;
}e[MAXM<<1];
int head[MAXM],cnt;
char str[MAXN];
clock_t start;
std::vector<int> ps;
int n,d,m;
// a,b 和其他字符

inline void add(int u,int v){
    e[++cnt] = (Edge){v,head[u]};head[u] = cnt;
}

struct Query{
    int i,j;char hi,hj;
}q[MAXM];
char t0[MAXN],t1[MAXN],ch[23];
int dfn[MAXM],low[MAXM],col[MAXM];
int st[MAXM],tp,tot;
bool ins[MAXM];

inline void dfs(int v){
    static int ts = 0;
    dfn[v] = low[v] = ++ts;ins[v] = true;st[++tp] = v;
    for(int i = head[v];i;i = e[i].nxt){
        if(!dfn[e[i].to]){
            dfs(e[i].to);low[v] = std::min(low[v],low[e[i].to]);
        }
        else if(ins[e[i].to]) low[v] = std::min(low[v],dfn[e[i].to]);
    }
    if(low[v] == dfn[v]){
        int t = -1;++tot;
        do{
            t = st[tp--];
            col[t] = tot;
            ins[t] = false;
        }while(t != v);
    }
}

inline void clear(){
    CLR(head,0);CLR(dfn,0);CLR(ins,0);CLR(col,0);
    tp = tot = cnt =  0;
}

inline void Solve(){
//    puts("NEW BEGINNING");
    FOR(i,1,n){
        if(str[i] == 'A') t0[i] = 'B',t1[i] = 'C';
        else if(str[i] == 'B') t0[i] = 'A',t1[i] = 'C';
        else t0[i] = 'A',t1[i] = 'B';
    }
//    FOR(i,1,n) printf("%c %c\n",t0[i],t1[i]);
    FOR(i,1,m){
        int u = q[i].i,v = q[i].j; 
        if(t0[u] == q[i].hi){
            if(str[v] == q[i].hj) add(u,u+n);
            else{
                if(t0[v] == q[i].hj) add(u,v),add(v+n,u+n);
                if(t1[v] == q[i].hj) add(u,v+n),add(v,u+n);
            }
        }
        if(t1[u] == q[i].hi){
            if(str[v] == q[i].hj) add(u+n,u);
            else{
                if(t0[v] == q[i].hj) add(u+n,v),add(v+n,u);
                if(t1[v] == q[i].hj) add(u+n,v+n),add(v,u);
            }
        }
    }
    FOR(i,1,2*n) if(!dfn[i]) dfs(i);
    FOR(i,1,n) if(col[i] == col[n+i]){
        clear();return;
    }
    // num[i] > num[i+1]
    // col[i] < col[n+i]
    FOR(i,1,n) putchar(col[i] < col[n+i] ? t0[i] : t1[i]);exit(0);
    // 缩点后编号小的拓扑序大
}

inline double now(){
    clock_t end = clock();
    return 1.0*(end-start)/CLOCKS_PER_SEC;
}

int G[MAXN];

int main(){
    std::ios::sync_with_stdio(false);
    srand(time(NULL));
    start = clock();
//    scanf("%d%d",&n,&d);
    std::cin >> n >> d;
    std::cin >> (str+1);
//    scanf("%s",str+1);
    FOR(i,1,n) str[i] -= 32;
    FOR(i,1,n) if(str[i] == 'X') ps.pb(i);
//    scanf("%d",&m);
    std::cin >> m;
    FOR(i,1,m){
//        scanf("%d",&q[i].i);scanf("%s",ch);
        std::cin >> q[i].i >> ch;
        q[i].hi = ch[0];
//        scanf("%d",&q[i].j);scanf("%s",ch);
        std::cin >> q[i].j >> ch;
        q[i].hj = ch[0];
    }
    std::vector<int> G;
    FOR(S,0,(1<<d)-1) G.pb(S);
    std::random_shuffle(all(G));
    FOR(S,0,(1<<d)-1){
        FOR(i,0,d-1) str[ps[i]] = (G[S]&(1<<i)) ? 'A' : 'B';
        Solve();
        if(now() > 1.983) break;
    }
    puts("-1");
    return 0;
}
