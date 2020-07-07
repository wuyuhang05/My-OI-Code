#include <bits/stdc++.h>

#define fi first
#define se second
#define db double
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

const int MAXN = 2e5+5;
const int BASE = 257;
const int BLO = 5000;

struct Edge{
    int to,nxt;
}e[MAXN<<1];
int head[MAXN],cnt;
int n,du[MAXN];

inline void add(int u,int v){
    e[++cnt] = (Edge){v,head[u]};head[u] = cnt;
    e[++cnt] = (Edge){u,head[v]};head[v] = cnt;
}
char str[MAXN];
namespace Subtask1{
//public:
    int r[MAXN];
    char S[MAXN];
    inline void manacher(){
        int mx=0,mid=0;r[0] = 0;
        FOR(i,1,n){
            if(mx > i) r[i] = std::min(r[2*mid-i],r[mid]-(i-mid));
            else r[i] = 1;
            while(S[i-r[i]] == S[i+r[i]]) r[i]++;
            if(i+r[i] > mx) mx = i+r[i],mid = i;
        }
    }
    inline void Solve(){
        S[0] = '#';S[1] = '$';
        FOR(i,1,n) S[2*i] = str[i],S[2*i+1] = '$';
        n = 2*n+1;
        manacher();
        int ans = 1;
        FOR(i,1,n) ans = std::max(ans,r[i]-1);
        printf("%d\n",ans);
        exit(0);
    }
}

namespace Subtask2{
//public:
    int fa[MAXN],dep[MAXN];
    inline void dfs(int v){
        dep[v] = dep[fa[v]]+1;
        for(int i = head[v];i;i = e[i].nxt){
            if(e[i].to == fa[v]) continue;
            fa[e[i].to] = v;dfs(e[i].to);
        }
    }
    std::vector<char> ss;

        int r[MAXN];
    char S[MAXN];
    inline void manacher(){
        int mx=0,mid=0;r[0] = 0;
        FOR(i,1,n){
            if(mx > i) r[i] = std::min(r[2*mid-i],r[mid]-(i-mid));
            else r[i] = 1;
            while(S[i-r[i]] == S[i+r[i]]) r[i]++;
            if(i+r[i] > mx) mx = i+r[i],mid = i;
        }
    }
    inline void split(int x,int y){
        std::vector<int> t1,t2;
        while(x != y){
            if(dep[x] < dep[y]) t2.pb(str[y]),y = fa[y];
            else t1.pb(str[x]),x = fa[x];
        }
        t2.pb(str[x]);
        std::reverse(all(t2));ss.clear();
        for(auto x:t1) ss.pb(x);
        for(auto x:t2) ss.pb(x);
//        for(auto x:ss) putchar(x);puts("");
    }

    inline void Solve(){
        int rt = 0;FOR(i,1,n) if(du[i] != 1){rt = i;break;}
//        DEBUG(rt);
        dfs(rt);std::vector<int> node;
        FOR(i,1,n) if(du[i] == 1) node.pb(i);int ans = 1;
        FOR(i,0,(int)node.size()-1){
            FOR(j,i+1,(int)node.size()-1){
                split(node[i],node[j]);
                S[0] = '#';S[1] = '$';
                FOR(i,1,ss.size()) S[i*2] = ss[i-1],S[i*2+1] = '$';
                n = 2*ss.size()+1;manacher();
                FOR(i,1,n) ans = std::max(ans,r[i]-1);
            }
        }
  //      DEBUG(1);
        printf("%d\n",ans);exit(0);
    }
}

unsigned LL pw[MAXN],sm[MAXN],ms[MAXN];
int dep[MAXN],ans;

std::vector<int> S;
inline void dfs(int v,int fa=0){
    S.pb(v);dep[v] = dep[fa]+1;
    sm[dep[v]] = sm[dep[v]-1]*BASE+str[v];
    ms[dep[v]] = ms[dep[v]-1]+str[v]*pw[dep[v]-1];
    int t = (S.size()+1)/2;
    if(S.size() == 1) ans = std::max(ans,1);
    else if(S.size()&1){
        if(ms[t-1] == sm[dep[v]]-sm[t]*pw[dep[v]-t]) ans = std::max(ans,dep[v]);
    }
    else{
        if(ms[t] == sm[dep[v]]-sm[t]*pw[dep[v]-t]) ans = std::max(ans,dep[v]);
    }
    for(int i = head[v];i;i = e[i].nxt){
        if(e[i].to == fa) continue;
        dfs(e[i].to,v);
    }
    S.pop_back();
}

std::vector<int> id;
std::mt19937 g(time(NULL));
int main(){
    pw[0] = 1;FOR(i,1,MAXN-1) pw[i] = pw[i-1]*BASE;
    scanf("%d",&n);scanf("%s",str+1);
    FOR(i,1,n) id.pb(i);bool flag = 1;
    FOR(i,2,n){
        int u,v;scanf("%d%d",&u,&v);
        if(u > v) std::swap(u,v);
        flag &= (u+1==v);
        du[u]++;du[v]++;
        add(u,v);
    }
    int tot = 0;
    FOR(i,1,n) tot += (du[i]==1);
    dfs(1);
    if(flag) Subtask1::Solve();
    else if(n > 3000 && tot <= 100) Subtask2::Solve();
    std::shuffle(all(id),g);
    FOR(i,1,std::min(BLO,n)) dfs(id[i]);
    printf("%d\n",ans);
    return 0;
}
