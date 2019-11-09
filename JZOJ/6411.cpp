/*
 * Author: RainAir
 * Time: 2019-11-06 15:55:10
 */
#include <algorithm>
#include <iostream>
#include <assert.h>
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
#define U unsigned
#define P std::pair
#define LL long long
#define pb push_back
#define MP std::make_pair
#define all(x) x.begin(),x.end()
#define CLR(i,a) memset(i,a,sizeof(i))
#define FOR(i,a,b) for(int i = a;i <= b;++i)
#define ROF(i,a,b) for(int i = a;i >= b;--i)
#define DEBUG(x) std::cerr << #x << '=' << x << std::endl

const int MAXN = 1e6 + 5;

struct Edge{
    int to,w,nxt;
}e[MAXN<<1];
int head[MAXN],du[MAXN],cnt,tot;

inline void add(int u,int v,int w){
  //  printf("%d %d %d\n",u,v,w);
    e[++cnt] = (Edge){v,w,head[u]};head[u] = cnt;
    ++du[v];
}

#define lc ((x)<<1)
#define rc ((x)<<1|1)

int p[MAXN];
int dis[MAXN];

inline void build(int x,int l,int r){
    tot = std::max(tot,x);
    if(l == r){
        if(p[l]) dis[x] = p[l];
        else dis[x] = 1;
        return;
    }
    int mid = (l + r) >> 1;
    add(lc,x,0);add(rc,x,0);
    build(lc,l,mid);build(rc,mid+1,r);
}
// small -> big
inline void modify(int x,int l,int r,int L,int R,int p){
    if(l == L && r == R){
        add(x,p,0);
        return;
    }
    int mid = (l + r) >> 1;
    if(R <= mid) modify(lc,l,mid,L,R,p);
    else if(L > mid) modify(rc,mid+1,r,L,R,p);
    else modify(lc,l,mid,L,mid,p),modify(rc,mid+1,r,mid+1,R,p);
}

inline int getid(int x,int l,int r,int p){
    if(l == r) return x;
    int mid = (l + r) >> 1;
    if(p <= mid) return getid(lc,l,mid,p);
    return getid(rc,mid+1,r,p);
}

int n,s,m;
int x[MAXN],ans[MAXN];

inline void link(int l,int r,int p){ // [l,r] -> p
    if(l > r) return;
    modify(1,1,n,l,r,p);
}

inline void topsort(){
    std::queue<int> q;
    FOR(i,1,tot) if(!du[i]) q.push(i);//,DEBUG(i);
    int c = 0;
    while(!q.empty()){
        int v = q.front();q.pop();++c;
        for(int i = head[v];i;i = e[i].nxt){
 //           DEBUG(e[i].to);
//            if(e[i].to == 1) DEBUG(v),DEBUG(dis[v]);
//            DEBUG(dis[1]);
            dis[e[i].to] = std::max(dis[e[i].to],dis[v] + e[i].w);
            if(!--du[e[i].to]) q.push(e[i].to);
        }
    }
    if(c != tot){
        puts("Impossible");
        exit(0);
    }
    puts("Possible");
    FOR(i,1,n) ans[i] = std::max(0,dis[getid(1,1,n,i)]);
 //   FOR(i,1,tot) DEBUG(dis[i]);
}

const int MAXM = 19;

struct Node{
    int l,r,k;
    std::vector<int> x;
}q[MAXN];
int mn[MAXN][MAXM+1];
int pc[MAXN];

inline void prework(){
    FOR(i,1,n) mn[i][0] = ans[i];
    FOR(i,1,MAXM){
        for(int j = 0;j+(1<<(i-1)) < MAXN;++j){
            mn[j][i] = std::max(mn[j][i-1],mn[j+(1<<(i-1))][i-1]);
        }
    }
}

inline int calc(int l,int r){
    if(l > r) return 0;
    int c = pc[r-l+1]-1;
    return std::max(mn[l][c],mn[r-(1<<c)+1][c]);
}

inline void spj(){
    FOR(i,1,n) pc[i] = pc[i>>1]+1;
    prework();
    FOR(i,1,m){
        int mx = 0;
        mx = std::max(mx,calc(q[i].l,q[i].x[0]-1));
        mx = std::max(mx,calc(q[i].x[q[i].k-1]+1,q[i].r));
//        DEBUG(q[i].x[0]);DEBUG(q[i].x[1]);
        FOR(j,1,q[i].k-1){
            mx = std::max(mx,calc(q[i].x[j-1]+1,q[i].x[j]-1));
        }
  //      DEBUG(i);
    //    DEBUG(mx);
        FOR(j,0,q[i].k-1) assert(mx < ans[q[i].x[j]]);
    }
}

int main(){
    freopen("web.in","r",stdin);
    freopen("web.out","w",stdout);
    scanf("%d%d%d",&n,&s,&m);
    FOR(i,1,s){
        int a,b;scanf("%d%d",&a,&b);
        p[a] = b;
    }
    build(1,1,n);
    FOR(i,1,m){
        int l,r,k;scanf("%d%d%d",&l,&r,&k);
        FOR(i,1,k) scanf("%d",x+i);
        ++tot;
        link(l,x[1]-1,tot);
        link(x[k]+1,r,tot);
        FOR(i,2,k) link(x[i-1]+1,x[i]-1,tot);
        FOR(i,1,k) add(tot,getid(1,1,n,x[i]),1);
        q[i].l = l;q[i].r = r;q[i].k = k;
        FOR(j,1,k) q[i].x.pb(x[j]);
    }
    topsort();
    FOR(i,1,n) printf("%d ",ans[i]);puts("");
//    spj();
    return 0;
}
