#pragma GCC optimize("Ofast")
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

const int MAXN = 1e5 + 5;
int ch[MAXN][4],tot=1,fail[MAXN],rt = 1;
int n,m,k;
bool bd[MAXN];
int G[MAXN];

inline void insert(char str[],int opt,int id=0){
    int v = rt;
    FOR(i,1,k){
        int o = str[i]-'1';
        if(!ch[v][o]) ch[v][o] = ++tot;
        v = ch[v][o];
    }
    if(opt == 1) G[id] = v;
    else bd[v] = 1;
}

struct Edge{
    int to,w,nxt;
}e[MAXN<<2];
int head[MAXN],cnt;

inline void add(int u,int v,int w){
    if(bd[u] || bd[v]) return;
//    printf("%d %d %d\n",u,v,w);
    e[++cnt] = (Edge){v,w,head[u]};head[u] = cnt;
}

inline void build(){
    std::queue<int> q;
    FOR(i,0,3){
        if(ch[rt][i]) fail[ch[rt][i]] = rt,q.push(ch[rt][i]);
        else ch[rt][i] = rt;
    }
    while(!q.empty()){
        int v = q.front();q.pop();
        FOR(i,0,3){
            if(ch[v][i]) fail[ch[v][i]] = ch[fail[v]][i],q.push(ch[v][i]);
            else ch[v][i] = ch[fail[v]][i];
        }
    }
    FOR(i,1,tot) FOR(j,0,3) add(i,ch[i][j],j+1);
}

char str[123];
int dis[21][MAXN];
bool used[MAXN];

inline void dij(int dis[],int s){
    std::priority_queue<P,std::vector<P>,std::greater<P> > q;
    FOR(i,1,tot) dis[i] = 1e9,used[i] = 0;
    q.push(MP(dis[s]=0,s));
    while(!q.empty()){
        int v = q.top().se;q.pop();
        if(used[v]) continue;
        used[v] = 1;
        for(int i = head[v];i;i = e[i].nxt){
            if(bd[e[i].to]) continue;
            if(dis[e[i].to] > dis[v] + e[i].w){
                dis[e[i].to] = dis[v]+e[i].w;
                q.push(MP(dis[e[i].to],e[i].to));
            }
        }
    }
}

int f[(1<<20)+5][20];

int main(){
//    int sz = sizeof(f)+sizeof(ch)+sizeof(fail)+sizeof(bd)+sizeof(G)+sizeof(e)+sizeof(head)+sizeof(used)+sizeof(dis);
//    DEBUG(sz/1024/1024);
//    freopen("D.in","r",stdin);
//    freopen("D.out","w",stdout);
    scanf("%d%d%d",&n,&m,&k);
    FOR(i,1,n) scanf("%s",str+1),insert(str,1,i);
    FOR(i,1,m) scanf("%s",str+1),insert(str,2);
    build();
    dij(dis[0],1);
    FOR(i,1,n) dij(dis[i],G[i]);
    CLR(f,0x3f);
    FOR(i,0,n-1) f[(1<<i)][i] = dis[0][G[i+1]];
    FOR(S,1,(1<<n)-1){
        FOR(i,0,n-1){
            if(f[S][i] == 0x3f3f3f3f) continue;
            if(!((S>>i)&1)) continue;
            FOR(j,0,n-1){
                if((S>>j)&1) continue;
                f[S^(1<<j)][j] = std::min(f[S^(1<<j)][j],f[S][i]+dis[i+1][G[j+1]]);
            }
        }
    }
    int ans = 1e9;
    FOR(i,0,n-1) ans = std::min(ans,f[(1<<n)-1][i]);
    printf("%d\n",ans);
    return 0;
}
