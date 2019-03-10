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

#define fi first
#define se second
#define U unsigned
#define Re register
#define LL long long
#define MP std::make_pair
#define P std::pair<int,int>
#define CLR(i,a,b) memset(i,a,b)
#define FOR(i,a,b) for(Re int i = a;i <= b;++i)
#define ROF(i,a,b) for(Re int i = a;i >= b;--i)
#define SFOR(i,a,b,c) for(Re int i = a;i <= b;i+=c)
#define SROF(i,a,b,c) for(Re int i = a;i >= b;i-=c)
#define DEBUG(x) std::cerr << #x << '=' << x << std::endl

const int MAXN = 200000+9;
const int MAXM = 20000000+7;

inline char nc(){
    static char buf[MAXM],*p1 = buf+MAXM,*p2 = buf+MAXM;
    if(p1 == p2){
        p1 = buf;p2 = buf+fread(buf,1,MAXM,stdin);
        if(p1 == p2) return -1;
    }
    return *p1++;
}

inline void read(int &x){
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

struct Data{
    int u,v,w;
    bool operator < (const Data &t) const {
        return w < t.w;
    }
}d[MAXN<<2];

struct Edge{
    int to,w,next;
}e[MAXN<<2];
int head[MAXN],dis[MAXN],root[MAXN<<2],p1,p2,n,m;
bool vis[MAXN];
int size[MAXM],lc[MAXM],rc[MAXM],f[MAXM],min[MAXM];

inline void add(int u,int v,int w){
    e[++p2] = (Edge){v,w,head[u]};head[u] = p2;
}

inline void build(int &x,int l,int r){
    x = ++p1;
    if(l == r){
        min[x] = dis[f[x]=l];
        return;
    }
    int mid = (l + r) >> 1;
    build(lc[x],l,mid);build(rc[x],mid+1,r);
}

inline int insert(int *x,int v,int t){
    int l = 1,r = n;
    while(l != r){
        *x = ++p1;int mid = (l + r) >> 1;
        if(t <= mid) r = mid,rc[*x] = rc[v],x = lc + *x,v = lc[v];
        else l = mid+1,lc[*x] = lc[v],x = rc + *x,v = rc[v];
    }
    return *x = ++p1;
}

inline int find(int root,int x){
    int v = root;
    while("NOI2018"){
        int l = 1,r = n;v = root;
        while(l != r){
            int mid = (l + r) >> 1;
            if(x <= mid) r = mid,v = lc[v];
            else l = mid+1,v = rc[v];
        }
        if(x == f[v]) break;
        x = f[v];
    }
    return v;
}

inline void dijkstra(){
    std::priority_queue<P,std::vector<P>,std::greater<P> > q;
    CLR(dis,0x3f,sizeof(dis));
    q.push(MP(dis[1]=0,1));
    while(!q.empty()){
        int v = q.top().second;q.pop();
        if(vis[v]) continue;vis[v] = true;
        for(int i = head[v];i;i = e[i].next){
            if(dis[e[i].to] > dis[v] + e[i].w){
                dis[e[i].to] = dis[v] + e[i].w;
                q.push(MP(dis[e[i].to],e[i].to));
            }
        }
    }
}
int t[MAXN<<2];

inline void recycle(int n,int L){
    CLR(vis,0,n+1);CLR(head,0,(n+1)<<2);
    CLR(lc,0,(p1+1)<<1);CLR(rc,0,(p1+1)<<1);
    CLR(root,0,(L+1)<<1);CLR(f,0,(p1+1)<<1);
    CLR(min,0,(p1+1)<<1);CLR(size,0,(p1+1)<<1);
}

inline void Solve(){
    read(n);read(m);
    p1 = p2 = 0;
    FOR(i,1,m){
        int u,v,w,a;read(u);read(v);read(w);read(a);
        add(u,v,w);add(v,u,w);
        d[i] = (Data){u,v,a};
    }
    dijkstra();
    int q,k,s,lastans = 0;read(q);read(k);read(s);
    std::sort(d+1,d+m+1);
    FOR(i,1,m) t[i] = d[i].w;t[m+1] = s+1;
    int L = std::unique(t+1,t+m+2)-t-1;
    build(root[L],1,n);
    int j = m;
    ROF(i,L-1,1){
        root[i] = root[i+1];
        for(;j&&d[j].w == t[i];--j){
            int u,v;
            if((u = find(root[i],d[j].u)) == (v = find(root[i],d[j].v))) continue;
            if(size[u] > size[v]) std::swap(u,v);
            f[insert(&root[i],root[i],f[u])] = f[v];
            int w = insert(&root[i],root[i],f[v]);
            f[w] = f[v];min[w] = std::min(min[u],min[v]);
            size[w] = size[v]+(size[u]==size[v]);
        }
    }
    while(q--){
        int u,v;read(u);read(v);std::swap(u,v);
        v = (v+k*lastans-1)%n+1;u = (u+k*lastans)%(s+1);
        printf("%d\n",lastans = min[find(root[std::upper_bound(t+1,t+L+1,u)-t],v)]);
    }
    recycle(n,L);
}

int main(){
    int T;read(T);
    while(T--) Solve();
    return 0;
}