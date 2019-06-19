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

const int MAXN = 500+5;

int n,m,a[MAXN][MAXN],b[MAXN],s[MAXN];

struct Edge{
    int from,to,pre,next,c;
}e[MAXN*MAXN],te[210][10050];
int cnt = 1;
int head[MAXN],tc[MAXN],th[210][MAXN];
int zy[210][MAXN][11],tz[210][MAXN];

inline void insert(int u,int v,int w){
    e[++cnt] = (Edge){u,v,0,head[u],w};
    if(head[u]) e[head[u]].pre = cnt;
    head[u] = cnt;
}

inline void add(int u,int v,int c){
    insert(u,v,c);insert(v,u,0);
}

inline void del(int pos){
    if(e[pos].next) e[e[pos].next].pre = e[pos].pre;
    if(e[pos].pre) e[e[pos].pre].next = e[pos].next;
    if(pos == head[e[pos].from]) head[e[pos].from] = e[pos].next;
}

// ----- Network Flow ~

int level[MAXN],cur[MAXN],N,S,T;
inline bool bfs(){
    FOR(i,0,N) level[i] = 0,cur[i] = head[i];
    std::queue<int> q;q.push(S);level[S] = 1;
    while(!q.empty()){
        int v = q.front();q.pop();
        for(int i = head[v];i;i = e[i].next){
            int to = e[i].to;
            if(e[i].c > 0 && !level[to]){
                level[to] = level[v] + 1;
                if(to == T) return true;
                q.push(to);
            }
        }
    }
    return false;
}

inline int dfs(int v=S,int limit=INT_MAX){
    if(v == T) return limit;
    int flow;
    for(int &i = cur[v];i;i = e[i].next){
        int to = e[i].to;
        if(e[i].c > 0 && level[to] == level[v] + 1){
            if((flow = dfs(to,std::min(limit,e[i].c)))){
                e[i].c -= flow;
                e[i^1].c += flow;
                return flow;
            }
        }
    }
    return 0;
}

inline bool tst(){
    return bfs() && dfs();
}

int ans[MAXN];

inline void work1(){
    FOR(i,1,n){
        ans[i] = m+1;
        add(S,i,1);
        FOR(j,1,m){
            if(!tz[i][j]) continue;
            int l = cnt;
            FOR(k,1,tz[i][j]) add(i,zy[i][j][k]+n,1);
            if(tst()){
                ans[i] = j;
                break;
            }
            else{
                FOR(k,l,cnt) del(k);
                cnt = l;
            }
        }
        FOR(j,2,cnt) te[i][j] = e[j];
        FOR(j,0,N) th[i][j] = head[j];
        tc[i] = cnt;
        printf("%d ",ans[i]);
    }
    puts("");
}

inline bool chk(int q,int w){
    cnt = tc[w-1];
    FOR(i,0,N) head[i] = th[w-1][i];
    FOR(i,2,cnt) e[i] = te[w-1][i];
    add(S,q,1);
    FOR(i,1,s[q]){
        if(!tz[q][i]) continue;
        FOR(j,1,tz[q][i]) add(q,zy[q][i][j]+n,1);
    }
    return tst();
}

inline void work2(){
    FOR(i,1,n){
        if(ans[i] <= s[i]){
            printf("0 ");
            continue;
        }
        int L = 1,R = i-1,res = 0;
        while(L <= R){
            int mid = (L + R) >> 1;
            if(chk(i,mid)) L = mid+1,res = mid;
            else R = mid-1;
        }
        printf("%d ",i-res);
    }
    puts("");
}

inline void Solve(){
    scanf("%d%d",&n,&m);
    S = 0;N = T = n+m+1;cnt = 1;
    CLR(head,0);CLR(tc,0);CLR(th,0);
    CLR(tz,0);CLR(e,0);CLR(ans,0);
    FOR(i,1,m) scanf("%d",b+i),add(i+n,T,b[i]);
    tc[0] = cnt;
    FOR(i,0,N) th[0][i] = head[i];
    FOR(i,2,cnt) te[0][i] = e[i];
    FOR(i,1,n){
        FOR(j,1,m){
            scanf("%d",&a[i][j]);
            if(!a[i][j]) continue;
            zy[i][a[i][j]][++tz[i][a[i][j]]] = j;
        }
    }
    FOR(i,1,n) scanf("%d",s+i);
    work1();work2();
}

int main(){
    int T,C;scanf("%d%d",&T,&C);
    while(T--) Solve();
    return 0;
}
