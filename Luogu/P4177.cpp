#pragma GCC optimize("Ofast")
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
const int MAXN = 5000 + 5;

inline char nc(){
    #define SIZE 1000000+3
    static char buf[SIZE],*p1 = buf+SIZE,*p2 = buf+SIZE;
    if(p1 == p2){
        p1 = buf;p2 = buf+fread(buf,1,SIZE,stdin);
        if(p1 == p2) return -1;
    }
    return *p1++;
    #undef SIZE
}

template <typename T>
inline void read(T &x){
    x = 0;int flag = 0;char ch = nc();
    while(!isdigit(ch)){
        if(ch == '-') flag = 1;
        ch = nc();
    }
    while(isdigit(ch)){
        x = (x<<1) + (x<<3) + (ch^'0');
        ch = nc();
    }
    if(flag) x = -x;
}

namespace Flow{
    struct Edge{
        int to,w,nxt;
    }e[3000000+5];
    int head[MAXN],cur[MAXN],cnt=1;
    int dep[MAXN];
    int S,T,N;

    inline void add(int u,int v,int w){
        e[++cnt] = (Edge){v,w,head[u]};head[u] = cnt;
        e[++cnt] = (Edge){u,0,head[v]};head[v] = cnt;
    }

    inline bool bfs(){
        FOR(i,0,N) cur[i] = head[i],dep[i] = 0;
        std::queue<int> q;q.push(S);dep[S] = 1;
        while(!q.empty()){
            int v = q.front();q.pop();
            for(int i = head[v];i;i = e[i].nxt){
                if(e[i].w > 0 && !dep[e[i].to]){
                    dep[e[i].to] = dep[v] + 1;
                    if(e[i].to == T) return true;
                    q.push(e[i].to);
                }
            }
        }
        return dep[T];
    }

    inline int dfs(int v,int flow=1e9){
        if(v == T) return flow;
        if(!flow) return 0;
        int ans = 0;
        for(int &i = cur[v];i;i = e[i].nxt){
            if(e[i].w > 0 && dep[e[i].to] == dep[v] + 1){
                int t = dfs(e[i].to,std::min(flow,e[i].w));
                if(t>0){
                    ans += t;flow -= t;
                    e[i].w -= t;e[i^1].w += t;
                    if(!flow) break;
                }
            }
        }
        return ans;
    }

    inline int Dinic(){
        int ans = 0,t = 0;
        while(bfs()) while((t=dfs(S))) ans += t;
        return ans;
    }
};
using namespace Flow;

int n,m;

signed main(){
//    freopen("6.in","r",stdin);
    read(n);read(m);
    N = n+m;S = ++N;T = ++N;int sm = 0;
    FOR(i,1,n){
        int x,t;read(x);read(t);
        while(t--){
            int a,b;read(a);read(b);
            add(i,a+n,b);
        }
        add(S,i,x);sm += x;
    }
    FOR(i,1,m){
        int x;read(x);
        add(i+n,T,x);
    }
    printf("%d\n",sm-Dinic());
    return 0;
}
