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
#define db double
#define P std::pair<int,int>
#define LL long long
#define pb push_back
#define MP std::make_pair
#define all(x) x.begin(),x.end()
#define CLR(i,a) memset(i,a,sizeof(i))
#define FOR(i,a,b) for(int i = a;i <= b;++i)
#define ROF(i,a,b) for(int i = a;i >= b;--i)
#define DEBUG(x) std::cerr << #x << '=' << x << std::endl
#define ull unsigned LL

const int MAXN = 50000+5;
const int BASE = 256;
char a[MAXN];
int n;
struct Edge{
    int to,nxt;
}e[MAXN<<1];
int head[MAXN],cnt;

inline void add(int u,int v){
    e[++cnt] = (Edge){v,head[u]};head[u] = cnt;
    e[++cnt] = (Edge){u,head[v]};head[v] = cnt;
}

int sz[MAXN],mx[MAXN],rt;
bool vis[MAXN];

inline void getroot(int v,int fa=0){
    sz[v] = 1;
    for(int i = head[v];i;i = e[i].nxt){
        if(e[i].to == fa || vis[e[i].to]) continue;
        getroot(e[i].to,v);
        sz[v] += sz[e[i].to];
        mx[v] = std::max(mx[v],sz[e[i].to]);
    }
    mx[v] = std::max(mx[v],mx[0]-sz[v]);
    if(mx[rt] < mx[v]) rt = v;
}

int ans = 0;
ull sm[MAXN],ms[MAXN],pw[MAXN];
int dep[MAXN];
bool hw[MAXN];
std::vector<int> S;

inline void dfs(int v,int fa=0){
    S.pb(v);
    sm[dep[v]] = sm[dep[v]-1]*BASE+str[v];
    ms[dep[v]] = ms[dep[v]-1]+str[v]*pw[dep[v]-1];
    int t = S.size()/2;
    if(S.size() == 1) hw[v] = 1;
    else if(S.size()&1){//[1..t-1]=[v..t+1]
        hw[v] = ms[t-1] == (ull)(sm[v]-sm[t]*pw[v-t]);
    }
    else{// [1..t-1]=[v..t]
        hw[v] = ms[t-1] == (ull)(sm[v]-sm[t]*pw[v-t+1]);
    }
    if(hw[v]) ans = std::max(ans,dep[v]);
    for(int i = head[v];i;i = e[i].nxt){
        if(e[i].to == fa || vis[e[i].to]) continue;
        dep[e[i].to] = dep[v] + 1;dfs(e[i].to,v);
    }
    S.pop_back();
}

inline void getans(int v){
    S.clear();dep[v] = 1;dfs(v);
}

inline void work(int v){
    vis[v] = 1;getans(v);
    for(int i = head[v];i;i = e[i].nxt){
        if(vis[e[i].to]) continue;
        getroot(e[i].to);work(rt);
    }
}

int main(){
    pw[0] = 1;FOR(i,1,MAXN-1) pw[i] = pw[i-1]*BASE;
    scanf("%d",&n);
    scanf("%s",str+1);
    FOR(i,2,n){
        int u,v;scanf("%d%d",&u,&v);
        add(u,v);
    }
    getroot(1);
    work(rt);
    return 0;
}
