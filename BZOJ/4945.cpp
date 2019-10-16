/*
 * Author: RainAir
 * Time: 2019-10-12 09:06:50
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

const int MAXN = 1e5 + 5;

struct Edge{
    int to,nxt;
}e[MAXN<<2];
int head[MAXN],cnt;
char str[MAXN];
std::vector<int> ps;
int n,d,m;
// a,b 和其他字符

inline void add(int u,int v){
//    printf("%d %d\n",u,v);
    e[++cnt] = (Edge){v,head[u]};head[u] = cnt;
}

struct Query{
    int i,j;char hi,hj;
}q[MAXN];
char t0[MAXN],t1[MAXN],ch[23];
int dfn[MAXN],low[MAXN],col[MAXN];
int st[MAXN],tp,tot;
bool ins[MAXN];

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
    FOR(i,1,2*n) head[i] = dfn[i] = low[i] = col[i] = ins[i] = 0;
    tp = tot = cnt = 0;
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

int main(){
    scanf("%d%d",&n,&d);
    scanf("%s",str+1);
    FOR(i,1,n) str[i] -= 32;
    FOR(i,1,n) if(str[i] == 'X') ps.pb(i);
    scanf("%d",&m);
    FOR(i,1,m){
        scanf("%d",&q[i].i);scanf("%s",ch);
        q[i].hi = ch[0];
        scanf("%d",&q[i].j);scanf("%s",ch);
        q[i].hj = ch[0];
    }
    FOR(S,0,(1<<d)-1){
        FOR(i,0,d-1) str[ps[i]] = (S&(1<<i)) ? 'A' : 'B';
        Solve();
    }
    puts("-1");
    return 0;
}
