#include<bits/stdc++.h>

#define fi first
#define se second
#define U unsigned
#define P std::pair<int,int>
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
}e[MAXN<<1];
int head[MAXN],cnt;

inline void add(int u,int v){
    e[++cnt] = (Edge){v,head[u]};head[u] = cnt;
    e[++cnt] = (Edge){u,head[v]};head[v] = cnt;
}

int f[MAXN],sz[MAXN],mx[MAXN],cmx[MAXN],dep[MAXN];

inline void dfs(int v,int fa=0){
    sz[v] = 1;mx[v] = 0;f[v] = 0;dep[v] = dep[fa]+1;
    for(int i = head[v];i;i = e[i].nxt){
        if(e[i].to == fa) continue;
        dfs(e[i].to,v);sz[v] += sz[e[i].to];
        if(sz[e[i].to] > sz[mx[v]]) cmx[v] = mx[v],mx[v] = e[i].to;
        else if(sz[e[i].to] > sz[cmx[v]]) cmx[v] = e[i].to;
    }
    if(sz[mx[v]]-2*f[mx[v]] <= sz[v]-1-sz[mx[v]]) f[v] = (sz[v]-1)/2;
    else f[v] = f[mx[v]]+sz[v]-1-sz[mx[v]];
}
int ans[MAXN],n;
inline void upd(int v,int fa=0,int orz=0){
    int x = sz[mx[v]]>sz[orz]?mx[v]:orz;
    if(sz[x]-2*f[x] <= n-dep[v]-sz[x]){
        ans[v] = (n&1)==(dep[v]&1);
    }
    for(int i = head[v];i;i = e[i].nxt){
        if(e[i].to == fa) continue;
        upd(e[i].to,v,e[i].to == mx[v] ? (sz[cmx[v]]>sz[orz]?cmx[v]:orz) : (sz[mx[v]]>sz[orz]?mx[v]:orz));
    }
}

int W;

inline void Solve(){
    scanf("%d",&n);FOR(i,1,n) head[i] = 0;cnt = 0;
    FOR(i,2,n){
        int u,v;scanf("%d%d",&u,&v);
        add(u,v);
    }FOR(i,1,n) ans[i] = 0;
    dfs(1);upd(1);
    FOR(i,1,n){
        if(i != 1 && W == 3) break;
        putchar(ans[i]+'0');
    }
    puts("");
}

int main(){
    int T;scanf("%d%d",&W,&T);
    while(T--) Solve();
    return 0;
}
/*
 * 考虑只询问 1 号点如何做：我们发现实际上在两个不同的子树内接上 操作会相互抵消
 * 相当于从两个不同的集合可以选出一对消去 问你是否可能全部消没
 *  f[v] 表示 v 子树最多可以消去多少 如果2*mx <= restsize 就可以直接全部消去（或者是剩下一个），否则必须借助子树内部的 f[mx] 消去
 *  最终考虑如何回答别的点的询问：我们可以先把这个点和根之间的边连上 然后把这条链缩成一个点 找出这个大点的最重的儿子讨论即可 为了能快速计算 需要对每个点预处理重儿子和次重儿子
 *  最后注意判断是否可达的时候需要额外判断奇偶性（
 */
