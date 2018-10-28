#include <algorithm>
#include <iostream>
#include <cstring>
#include <climits>
#include <cstdio>
#include <vector>
#include <cstdlib>
#include <ctime>
#include <cmath>
#include <queue>
#include <stack>
#include <map>
#include <set>

#define Re register
#define LL long long
#define U unsigned
#define FOR(i,a,b) for(Re int i = a;i <= b;++i)
#define ROF(i,a,b) for(Re int i = a;i >= b;--i)
#define SFOR(i,a,b,c) for(Re int i = a;i <= b;i+=c)
#define SROF(i,a,b,c) for(Re int i = a;i >= b;i-=c)
#define CLR(i,a) memset(i,a,sizeof(i))
#define BR printf("--------------------\n")
#define DEBUG(x) std::cerr << #x << '=' << x << std::endl

namespace fastIO{ 
    #define BUF_SIZE 100000 
    #define OUT_SIZE 100000 
    #define ll long long 
    bool IOerror=0; 
    inline char nc(){ 
        static char buf[BUF_SIZE],*p1=buf+BUF_SIZE,*pend=buf+BUF_SIZE; 
        if (p1==pend){ 
            p1=buf; pend=buf+fread(buf,1,BUF_SIZE,stdin); 
            if (pend==p1){IOerror=1;return -1;} 
        } 
        return *p1++; 
    } 
    inline bool blank(char ch){return ch==' '||ch=='\n'||ch=='\r'||ch=='\t';} 
    inline void read(int &x){ 
        bool sign=0; char ch=nc(); x=0; 
        for (;blank(ch);ch=nc()); 
        if (IOerror)return; 
        if (ch=='-')sign=1,ch=nc(); 
        for (;ch>='0'&&ch<='9';ch=nc())x=x*10+ch-'0'; 
        if (sign)x=-x; 
    } 
    inline void read(ll &x){ 
        bool sign=0; char ch=nc(); x=0; 
        for (;blank(ch);ch=nc()); 
        if (IOerror)return; 
        if (ch=='-')sign=1,ch=nc(); 
        for (;ch>='0'&&ch<='9';ch=nc())x=x*10+ch-'0'; 
        if (sign)x=-x; 
    } 
    #undef ll 
    #undef OUT_SIZE 
    #undef BUF_SIZE 
}; 
using namespace fastIO;
#define int long long
const int MAXN = 1000 + 5;
const int MAXM = 1000000 + 5;
const int dx[4] = {0,0,1,-1};
const int dy[4] = {1,-1,0,0};

struct Node{
    struct Edge *firstEdge;
    int low,dfn,num,du;bool instack;
}node[MAXN*MAXN],scc[MAXN*MAXN];

struct Edge{
    Node *s,*t;
    int w;
    Edge *next;
}pool[MAXM<<2],*frog = pool;

Edge *New(Node *s,Node *t){
    Edge *ret = ++frog;
    ret->s = s;ret->t = t;//ret->w = w;
    ret->next = s->firstEdge;
    return ret;
}

inline void add(int u,int v){
    node[u].firstEdge = New(&node[u],&node[v]);
}

inline void add2(int u,int v){
    scc[u].firstEdge = New(&scc[u],&scc[v]);
    scc[v].du++;
}

int N,M;
int h[MAXN][MAXN],v[MAXN][MAXN];

inline int getp(int x,int y){
    return (x-1)*M+y;
}

int ts = 0;
std::stack<Node *> s;
int col[MAXN*MAXN],cnt;
int num[MAXN][MAXN],val[MAXN*MAXN];
int size[MAXN*MAXN],dis[MAXN*MAXN];

void dfs(Node *v){
    static int ts = 0;
    v->low = v->dfn = ++ts;
    s.push(v);v->instack = true;
    for(Edge *e = v->firstEdge;e;e = e->next){
        if(!e->t->dfn){
            dfs(e->t);
            v->low = std::min(v->low,e->t->low);
        }
        else if(e->t->instack) v->low = std::min(v->low,e->t->dfn);
    }
    if(v->low == v->dfn){
        Node *r;cnt++;
        do{
            r = s.top();s.pop();
            size[cnt]++;dis[cnt] += val[r->num];
            r->instack = false;
            col[r->num] = cnt;
        }while(r != v);
    }
}

inline void rebuild(){
    FOR(i,1,cnt) if(size[i]>1) dis[i] = dis[i]<<1ll;
    FOR(i,1,N){
        for(Edge *e = node[i].firstEdge;e;e = e->next){
            if(col[i] == col[e->t->num]) continue;
            add2(col[i],col[e->t->num]);
        }
    }
}
int f[MAXM];
inline void topsort(){
    std::stack<Node *> s;
    FOR(i,1,cnt){
        if(!scc[i].du) s.push(&scc[i]),f[i] = dis[i];
    }
    while(!s.empty()){
        Node *v = s.top();s.pop();
        for(Edge *e = v->firstEdge;e;e = e->next){
            if(!--e->t->du) s.push(e->t);
            f[e->t->num] = std::max(f[e->t->num],f[v->num] + dis[e->t->num]);
        }
    }
}

signed main(){
    freopen("road.in","r",stdin);
    freopen("road.out","w",stdout);
    read(N);read(M);
    FOR(i,1,N) FOR(j,1,M) read(h[i][j]);
    FOR(i,1,N) FOR(j,1,M) read(v[i][j]);
    int tot = 0;
    FOR(i,1,N) FOR(j,1,M) val[++tot] = v[i][j],node[tot].num = scc[tot].num = tot;
    FOR(i,1,N){
        FOR(j,1,M){
            FOR(k,0,3){
                int xx = i+dx[k],yy = j+dy[k];
                if(xx >= 1 && xx <= N && yy >= 1 && yy <= M && h[xx][yy] <= h[i][j])
                    add(getp(i,j),getp(xx,yy));
            }
        }
    }
    N = N*M;
    FOR(i,1,N) if(!node[i].dfn) dfs(&node[i]);
    // FOR(i,1,N) printf("%d ",col[i]);puts("");
    rebuild();
    topsort();
    int ans = 0;
    FOR(i,1,cnt) ans = std::max(ans,f[i]);
    printf("%lld\n",ans);
    return 0;
}