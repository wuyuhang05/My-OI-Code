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

const int MAXN = 2e5 + 5;
int n,m;

struct Edge{
    int to,w,nxt;
}e[MAXN<<1];
int head[MAXN],cnt;

inline void add(int u,int v){
    e[++cnt] = (Edge){v,0,head[u]};head[u] = cnt;
}

namespace Undirected{
    int du[MAXN];std::vector<int> S;

    inline void dfs(int v){
        for(int &i = head[v];i;i = e[i].nxt){
            if(e[i].w) continue;
            e[i].w = 1;
            //e[i^1].w = 1;
            int t = i;dfs(e[i].to);
            S.pb(t);
            //S.pb((t&1?-1:1)*(int)(t/2));
        }
    }

    inline void Solve(){
        cnt = 1;
        FOR(i,1,m){
            int u,v;scanf("%d%d",&u,&v);add(u,v);add(v,u);++du[u];++du[v];
        }
        FOR(i,1,n) if(du[i]&1) {puts("NO");return;}
        FOR(i,1,n) if(du[i]) {dfs(i);break;}
        if(S.size() != m) {puts("NO");return;}
        puts("YES");
        std::reverse(all(S));for(auto x:S) printf("%d ",x);puts("");
    }
}

namespace Directed{
    int in[MAXN],out[MAXN];std::vector<int> S;

    inline void dfs(int v){
        for(int &i = head[v];i;i = e[i].nxt){
            if(e[i].w) continue;
            e[i].w = 1;// 不能缺少标记 因为这个边还没被真正删除
            int t = i;dfs(e[i].to);S.pb(t);//注意取址后后面会改
        }
    }

    inline void Solve(){
        cnt = 0;
        FOR(i,1,m){
            int u,v;scanf("%d%d",&u,&v);add(u,v);++out[u];++in[v];
        }
        FOR(i,1,n) if(in[i] != out[i]) {puts("NO");return;}
        FOR(i,1,n) if(out[i]){dfs(i);break;}
        dfs(1);std::reverse(all(S));
        if(S.size() != m) {puts("NO");return;}
        puts("YES");for(auto x:S) printf("%d ",x);puts("");
    }
}

int main(){
    int t;scanf("%d%d%d",&t,&n,&m);
    if(t == 1) Undirected::Solve();
    else Directed::Solve();
    return 0;
}

