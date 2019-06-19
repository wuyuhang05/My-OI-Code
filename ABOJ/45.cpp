#include <algorithm>
#include <iostream>
#include <cstring>
#include <climits>
#include <cstdlib>
#include <cstdio>
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
#define Re register
#define LL long long
#define pb push_back
#define MP std::make_pair
#define all(x) x.begin(),x.end()
#define CLR(i,a) memset(i,a,sizeof(i))
#define FOR(i,a,b) for(Re int i = a;i <= b;++i)
#define ROF(i,a,b) for(Re int i = a;i >= b;--i)
#define DEBUG(x) std::cerr << #x << '=' << x << std::endl

const int MAXN = 200000+5;
const int Q = 500;

struct bitset{
    U LL bit[502];int cnt;

    inline void clear(){
        FOR(i,0,cnt) bit[i] = 0ll;
        cnt = 0;
    }

    void operator |= (const bitset &t){
        cnt = std::max(cnt,t.cnt);
        FOR(i,0,cnt) bit[i] |= t.bit[i];
    }

    void operator |= (const int &x){
        bit[x >> 6] |= 1ll<<(x&63);
        cnt = std::max(cnt,x>>6);
    }

    int num(){
        int ans = 0;
        FOR(i,0,cnt) FOR(j,0,63) if(bit[i]&(1ll<<j)) ans++;
        return ans;
    }

    int mex(){
        FOR(i,0,cnt) FOR(j,0,63) if(!(bit[i]&(1ll<<j))) return i*64+j;
    }
}ans,bit[Q][Q];

std::vector<int> G[MAXN];
int fa[MAXN],dep[MAXN],size[MAXN],son[MAXN],tp[MAXN],dfn[MAXN];

void dfs(int v){
    size[v] = 1;son[v] = 0;
    for(auto i:G[v]){
        if(i == fa[v]) continue;
        fa[i] = v;dep[i] = dep[v] + 1;
        dfs(i);size[v] += size[i];
        if(size[i] > size[son[v]]) son[v] = i;
    }
}

void dfs(int v,int tpp){
    static int ts = 0;
    tp[v] = tpp;dfn[v] = ++ts;
    if(!son[v]) return;
    dfs(son[v],tpp);
    for(auto i:G[v]){
        if(i == fa[v] || i == son[v]) continue;
        dfs(i,i);
    }
}

int lca(int x,int y){
    while(tp[x] != tp[y]){
        if(dep[tp[x]] < dep[tp[y]]) std::swap(x,y);
        x = fa[tp[x]];
    }
    if(dep[x] > dep[y]) std::swap(x,y);
    return x;
}

int n,m,q,f,a[MAXN],tag[MAXN],pos[MAXN],up[MAXN];
bool vis[MAXN];

int main(){
    srand(20050117);
    scanf("%d%d",&n,&m);q = std::sqrt(1.0*n);f = false;
    FOR(i,1,n) scanf("%d",a+i);
    FOR(i,1,n-1){
        int u,v;scanf("%d%d",&u,&v);
        G[u].pb(v);G[v].pb(u);
    }
    dep[1] = 1;dfs(1);dfs(1,1);
    FOR(i,1,q){
        int v = rand()%n + 1;
        while(pos[v]) v = rand()%n + 1;
        tag[i] = v;pos[tag[i]] = i;
    }
    FOR(i,1,q){
        int v = tag[i];ans.clear();
        do{
            ans |= a[v];
            if(v != tag[i] && pos[v]){
                bit[i][pos[v]] |= ans;
                if(!up[tag[i]]) up[tag[i]] = v;
            }
            v = fa[v];
        }while(v);
    }
    int lastans = 0;
    FOR(i,1,m){
        int cnt;scanf("%d",&cnt);ans.clear();
        FOR(j,1,cnt){
            int x,y;scanf("%d%d",&x,&y);
            if(f) x ^= lastans,y ^= lastans;
            int z = lca(x,y);ans |= a[z];
            while(!pos[x] && x != z) ans |= a[x],x = fa[x];
            int now = x;
            while(dep[up[x]] > dep[z]) x = up[x];
            ans |= bit[pos[now]][pos[x]];
            while(x != z) ans |= a[x],x = fa[x];
            while(!pos[y] && y != z) ans |= a[y],y = fa[y];
            now = y;
            while(dep[up[y]] > dep[z]) y = up[y];
            ans |= bit[pos[now]][pos[y]];
            while(y != z) ans |= a[y],y = fa[y];
        }
        int a = ans.num(),b = ans.mex();
        lastans = a+b;printf("%d %d\n",a,b);
    }
    return 0;
}

