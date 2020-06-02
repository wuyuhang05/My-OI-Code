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

const int MAXN = 18+2;
int p[MAXN],n,m,f[MAXN];

inline int find(int x){
    return x == f[x] ? x : f[x] = find(f[x]);
}

inline void merge(int x,int y){
    x = find(x);y = find(y);
    if(x == y) return;
    f[x] = y;
}

std::vector<P> e;
int dp[(1<<MAXN)+1],t;
bool use[MAXN];
int du[MAXN];

inline bool chk(int S){
    FOR(i,0,n-1) use[i] = 0,f[i] = i,du[i] = 0;
    FOR(i,0,t-1){
        if((S>>i)&1){
            use[e[i].fi] = use[e[i].se] = 1;
            merge(e[i].fi,e[i].se);du[e[i].fi]++;du[e[i].se]--;
        }
    }
    int ps = -1,cnt = 0;
    FOR(i,0,n-1) if(use[i]) ps = i,cnt++;
    FOR(i,0,n-1) if(use[i] && find(ps) != find(i)) return false;
    FOR(i,0,n-1) if(use[i] && du[i]) return false;//重边
    // 还要判断重环
    return __builtin_popcount(S)==cnt;
}

inline void Solve(){
    scanf("%d%d",&n,&m);
    FOR(i,0,n-1){
        scanf("%d",&p[i]);p[i]--;f[i] = i;
    }
    FOR(i,1,m){
        int u,v;scanf("%d%d",&u,&v);--u;--v;
        merge(u,v);
    }e.clear();
    FOR(i,0,n-1) if(find(i) != find(p[i])) e.pb(MP(find(i),find(p[i])));
    t = e.size();
    FOR(S,1,(1<<t)-1) dp[S] = chk(S);
    FOR(S,1,(1<<t)-1){
        for(int T = S;T;T = (T-1)&S){
            if(dp[T] && dp[S^T]){
                dp[S] = std::max(dp[S],dp[T]+dp[S^T]);
            }
        }
    }
    printf("%d\n",t-dp[(1<<t)-1]);
}

int main(){
    int T;scanf("%d",&T);
    while(T--) Solve();
    return 0;
}
