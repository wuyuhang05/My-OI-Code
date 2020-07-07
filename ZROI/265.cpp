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

const int MAXN = 2e6 + 5;

struct Edge{
    int to,nxt;
}e[MAXN<<1];
int head[MAXN],cnt;

inline void add(int u,int v){
    e[++cnt] = (Edge){v,head[u]};head[u] = cnt;
}

int n,m;

struct Node{
    int a,b,c,d;
    Node(int a=0,int b=0,int c=0,int d=0) : a(a),b(b),c(c),d(d) {}

    inline bool vaild(){
        return a>=0&&b>=0&&c>=0&&d>=0;
    }

    Node operator + (const Node &t) const {
        return Node(a+t.a,b+t.b,c+t.c,d+t.d);
    }

    Node operator - (const Node &t) const {
        return Node(a-t.a,b-t.b,c-t.c,d-t.d);
    }

    inline void add(char s,int dd){
        if(s == 'A') a += dd;
        if(s == 'B') b += dd;
        if(s == 'C') c += dd;
        if(s == 'D') d += dd;
    }

    inline bool operator < (const Node &t) const {
        if(a != t.a) return a < t.a;
        if(b != t.b) return b < t.b;
        if(c != t.c) return c < t.c;
        return d < t.d;
    }
};

std::map<Node,int> S;
std::vector<int> G[MAXN];
int N;
char a[MAXN],b[MAXN];
int col[MAXN],dfn[MAXN],low[MAXN];
int st[MAXN],tp;bool ins[MAXN];
LL val[MAXN],w[MAXN];
int tot;

inline void dfs(int v){
    static int ts=0;
    dfn[v] = low[v] = ++ts;
    st[++tp] = v;ins[v] = 1;
    for(int i = head[v];i;i = e[i].nxt){
        if(!dfn[e[i].to]){
            dfs(e[i].to);
            low[v] = std::min(low[v],low[e[i].to]);
        }
        else if(ins[e[i].to]) low[v] = std::min(low[v],dfn[e[i].to]);
    }
    if(dfn[v] == low[v]){
        int u = -1;++tot;
        do{
            u = st[tp--];
            col[u] = tot;
            w[tot] += val[u];
            ins[u] = 0;
        }while(u != v);
    }
}

LL dis[MAXN];int du[MAXN];

inline void dp(){
    std::queue<int> q;
    FOR(i,1,tot) if(!du[i]) q.push(i),dis[i] = w[i];
    while(!q.empty()){
        int v = q.front();q.pop();
        for(auto x:G[v]){
            dis[x] = std::max(dis[x],dis[v]+w[x]);
            if(!--du[x]) q.push(x);
        }
    }
}

LL C[31][31];

int main(){
    C[0][0] = 1;
    FOR(i,1,30){
        C[i][0] = 1;
        FOR(j,1,i){
            C[i][j] = C[i-1][j]+C[i-1][j-1];
        }
    }
    scanf("%d%d",&n,&m);
    FOR(i,0,n){
        FOR(j,0,n-i){
            FOR(k,0,n-i-j){
                S[Node(i,j,k,n-i-j-k)] = ++N;
                val[N] = C[n][i]*C[n-i][j]*C[n-i-j][k];
//              printf("%d %d %d %d %d\n",i,j,k,n-i-j-k,N);
            }
        }
    }
    FOR(i,1,m){
        scanf("%s%s",a+1,b+1);
        int len = strlen(a+1);Node t1,t2;
        FOR(i,1,len){
            t1.add(a[i],1);
            t2.add(b[i],1);
        }
//        DEBUG(i);
        for(auto x:S){
            Node t = x.fi;
            t = t-t1;
            if(!t.vaild()) continue;
            t = t+t2;
            if(!t.vaild()) continue;
            if(x.se == S[t]) continue;
            add(x.se,S[t]);
        }
    }
    FOR(i,1,N) if(!dfn[i]) dfs(i);
    FOR(v,1,N){
        for(int i = head[v];i;i = e[i].nxt){
            if(col[v] == col[e[i].to]) continue;
            G[col[v]].pb(col[e[i].to]);
            du[col[e[i].to]]++;
        }
    }
    dp();LL ans = 0;
    FOR(i,1,tot) ans = std::max(ans,dis[i]);
    printf("%lld\n",ans);
    return 0;
}
