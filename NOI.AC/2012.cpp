#include <algorithm>
#include <iostream>
#include <cstring>
#include <climits>
#include <cstdlib>
#include <cstdio>
#include <bitset>
#include <cassert>
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
#define int LL
const int MAXN = 2e5 + 5;

struct Edge{
    int to,w,nxt;
}e[MAXN<<1];
int head[MAXN],cnt;

inline void add(int u,int v,int w){
    e[++cnt] = (Edge){v,w,head[u]};head[u] = cnt;
    e[++cnt] = (Edge){u,w,head[v]};head[v] = cnt;
}

int val[MAXN],sz[MAXN],son[MAXN],tp[MAXN],fa[MAXN],n;

inline void dfs1(int v){
    sz[v] = 1;
    for(int i = head[v];i;i = e[i].nxt){
        if(e[i].to == fa[v]) continue;
        fa[e[i].to] = v;val[e[i].to] = e[i].w;dfs1(e[i].to);
        sz[v] += sz[e[i].to];
        if(sz[son[v]] < sz[e[i].to]) son[v] = e[i].to;
    }
}

inline void dfs2(int v,int tp){
    ::tp[v] = tp;
    if(son[v]) dfs2(son[v],tp);
    for(int i = head[v];i;i = e[i].nxt){
        if(e[i].to == fa[v] || e[i].to == son[v]) continue;
        dfs2(e[i].to,e[i].to);
    }
}

inline void upmax(int &x,int y){
    if(x < y) x = y;
}

struct Poly{
    std::vector<int> x;
    inline int& operator [] (const int &n){return x[n];}
    inline int deg(){return (int)x.size()-1;}
    inline void ext(const int &n){x.resize(n+1);}
    Poly(int n=-1){ext(n);FOR(i,0,n) x[i] = -1e18;}
    inline void print(){
        FOR(i,0,deg()) printf("%lld ",x[i]);puts("");
    }
    friend Poly operator + (Poly A,Poly B){
        Poly res(A.deg()+B.deg());
        int i = 0,j = 0;
        while(i <= A.deg() && j <= B.deg()){
            upmax(res[i+j],A[i]+B[j]);
            if(i+1 > A.deg() || j+1 > B.deg()) break;
            if(A[i+1]+B[j] >= A[i]+B[j+1]) ++i;
            else ++j;
        }
        FOR(k,i+1,A.deg()) upmax(res[k+j],A[k]+B[j]);
        FOR(k,j+1,B.deg()) upmax(res[i+k],A[i]+B[k]);
        return res;
    }
    friend Poly operator + (Poly A,const int &d){
        A.ext(A.deg()+1);
        ROF(i,A.deg(),1) A[i] = A[i-1]+d;
        A[0] = -1e18;
        return A;
    }
};

inline void upmax(Poly &A,Poly B){
//    DEBUG(1);
    FOR(i,0,B.deg()){
        if(i > A.deg()) A.x.pb(B[i]);
        else upmax(A[i],B[i]);
    }
}

struct Node{
    Poly f[2][2];
};
bool xxx;
inline Node merge(Node A,Node B,int w,bool flagl=0,bool flagr=0){
    Node res;
    FOR(i,0,1){
        FOR(j,0,1){
            upmax(res.f[i][j],A.f[i][0]+B.f[1][j]);
            //if(xxx) res.f[0][0].print();
            upmax(res.f[i][j],A.f[i][1]+B.f[0][j]);
            //if(xxx) res.f[0][0].print();
            upmax(res.f[flagl|i][flagr|j],(A.f[i][0]+B.f[0][j])+w);
            upmax(res.f[i][j],A.f[i][0]+B.f[0][j]);
            upmax(res.f[i][j],A.f[i][1]+B.f[1][j]);
        }
    }
    return res;
}

Poly g[MAXN][2];

inline Node work(std::vector<int> &chain,int l,int r){
    if(l == r){
        Node res;
        res.f[0][0] = g[chain[l]][0];
        res.f[1][1] = g[chain[l]][1];
        res.f[1][0].x.pb(-1e18);res.f[0][1].x.pb(-1e18);
        return res;
    }
    int mid = (l + r) >> 1;
    Node ll = work(chain,l,mid),rr = work(chain,mid+1,r);
//    if(l == 0 && r == 2) xxx = 1,DEBUG(1);
    Node t = merge(ll,rr,val[chain[mid+1]],mid-l+1==1,r-mid==1);
    xxx = 0;
    if(l == 0 && r == 2){
//        DEBUG(l);DEBUG(r);
//        FOR(i,0,1) FOR(j,0,1) ll.f[i][j].print();
//        puts("");
//        FOR(i,0,1) FOR(j,0,1) rr.f[i][j].print();
//        puts("");
//        FOR(i,0,1) FOR(j,0,1) t.f[i][j].print();
    }
    return t;
}

struct NODE{
    Poly f[2];
};

inline NODE merge(NODE A,NODE B){
    NODE res;
    upmax(res.f[1],A.f[1]+B.f[0]);
    upmax(res.f[1],A.f[0]+B.f[1]);
    upmax(res.f[0],A.f[0]+B.f[0]);
    return res;
}

inline NODE work2(std::vector<int> &chain,int l,int r){
    if(l > r){
        NODE res;
        res.f[0].x.pb(0);res.f[1].x.pb(-1e18);
        return res;
    }
    if(l == r){
        NODE res;
        res.f[1] = g[chain[l]][0]+val[chain[l]];
        res.f[1][0] = -1e18;
        upmax(res.f[0],g[chain[l]][0]);
        upmax(res.f[0],g[chain[l]][1]);
        return res;
    }
    int mid = (l + r) >> 1;
    return merge(work2(chain,l,mid),work2(chain,mid+1,r));
}

inline void get1(int);
inline void get2(int);

inline void get1(int v){
    std::vector<int> chain;
    int now = v;
    while(now) chain.pb(now),now = son[now];
    FOR(i,0,(int)chain.size()-1) get2(chain[i]);
    Node res = work(chain,0,(int)chain.size()-1);
    upmax(g[v][0],res.f[0][0]);upmax(g[v][0],res.f[0][1]);
    upmax(g[v][1],res.f[1][0]);upmax(g[v][1],res.f[1][1]);
//    if(v == 1) g[v][0].print(),g[v][1].print();
}

inline void get2(int v){
    g[v][0].x.pb(0);
    g[v][1].x.pb(-1e18);
    std::vector<int> chain;
    for(int i = head[v];i;i = e[i].nxt){
        if(e[i].to == fa[v] || e[i].to == son[v]) continue;
        get1(e[i].to);chain.pb(e[i].to);
    }
    NODE res = work2(chain,0,(int)chain.size()-1);
    upmax(g[v][1],res.f[1]);
    upmax(g[v][0],res.f[0]);
}

signed main(){
    int l,r;
    scanf("%*d%lld%lld%lld",&n,&l,&r);
    FOR(i,2,n){
        int u,v,w;scanf("%lld%lld%lld",&u,&v,&w);
        add(u,v,w);
    }
    dfs1(1);dfs2(1,1);
    get1(1);
//    DEBUG(g[1][0][2]);
//    DEBUG(g[1][1][2]);
    Poly ans;
    upmax(ans,g[1][0]);upmax(ans,g[1][1]);
    FOR(i,l,r){
        if(i > ans.deg() || ans[i] < -9e17) printf("- ");
        else printf("%lld ",ans[i]);
    }
    puts("");
    return 0;
}
