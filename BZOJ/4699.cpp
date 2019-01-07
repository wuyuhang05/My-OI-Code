// 假 算 法:神奇TLE+MLE
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

#define U unsigned
#define Re register
#define LL long long
#define MP std::make_pair
#define P std::pair<int,int>
#define FOR(i,a,b) for(Re int i = a;i <= b;++i)
#define ROF(i,a,b) for(Re int i = a;i >= b;--i)
#define SFOR(i,a,b,c) for(Re int i = a;i <= b;i+=c)
#define SROF(i,a,b,c) for(Re int i = a;i >= b;i-=c)
#define CLR(i,a) memset(i,a,sizeof(i))
#define BR printf("--------------------\n")
#define DEBUG(x) std::cerr << #x << '=' << x << std::endl

const int MAXN = 300000+5;

struct Edge{
    int to,w,next;
}e[MAXN<<1];

int head[MAXN],cnt;
int N,M,K;
std::vector<int> dl[MAXN];
std::vector<P> v[MAXN];
float log2N;
int f[MAXN][25],fa[MAXN],depth[MAXN],in[MAXN],out[MAXN],ts;
int l1[MAXN],r1[MAXN],l2[MAXN],r2[MAXN],c[MAXN],vs[MAXN],vt[MAXN];
int L[MAXN];

inline void add(int u,int v,int w){
    //printf("%d %d %d\n",u,v,w);
    e[++cnt] = (Edge){v,w,head[u]};head[u] = cnt;
}

struct Node *New(int ,int ,Node *,Node *);

struct Node{
    int l,r;P max,min;
    Node *lc,*rc;

    static Node *build(int l,int r){
        int mid = (l + r) >> 1;
        return (l == r) ? New(l,r,NULL,NULL) : New(l,r,build(l,mid),build(mid+1,r));
    }

    inline void pushup(){
        max = std::max(lc->max,rc->max);
        min = std::min(lc->min,rc->min);
    }

    inline void update(int pos,int x){
        // x == 0 ==> del minval
        if(l == r){
            //x ? --vt[pos] : ++vs[pos];
            if(x) vt[pos]--;else vs[pos]++;
            //DEBUG(vs[pos]);
            if(vs[pos] <= vt[pos])
                max = v[pos][vt[pos]],min = v[pos][vs[pos]];
            else max = MP(0,0),min = MP(N+1,0);
            return;
        }
        if(pos <= x) lc->update(pos,x);
        else rc->update(pos,x);
        pushup();
    }

    // inline P query(int L,int R,int opt){ // opt==0 ==> find minval
    //     if(L == l && R == r)
    //         return opt ? max : min;
    //     P ans = MP(N+1,0);
    //     int mid = (l + r) >> 1;
    //     if(R <= mid) return lc->query(L,R,opt);
    //     else if(L > mid) return rc->query(L,R,opt);
    //     else return opt ? std::max(lc->query(L,mid,opt),rc->query(mid+1,R,opt)) : std::min(lc->query(L,mid,opt),rc->query(mid+1,R,opt));
    // }

    inline P query(int s,int t,int k){
        int mid=(l+r)>>1;
        if(s<=l&&r<=t) return k?max:min;P ans=k?MP(0,0):MP(N+1,0);
        if(s<=mid) k?ans=std::max(ans,lc->query(s,t,k)):ans=std::min(ans,lc->query(s,t,k));
        if(mid<t) k?ans=std::max(ans,rc->query(s,t,k)):ans=std::min(ans,rc->query(s,t,k));
        return ans;
    }

    // inline P query(int L,int R,int opt){
    //     if(L <= l && r <= R) return opt ? max : min;
    //     P ans = MP(N+1,0);
    //     int mid = (l + r) >> 1;
    //     if(L <= mid) opt ? ans = std::max(ans,lc->query(L,R,opt)) : ans = std::min(ans,lc->query(L,R,opt));
    //     if(mid < R) opt ? ans = std::max(ans,rc->query(L,R,opt)) : ans = std::min(ans,rc->query(L,R,opt));
    //     return ans;
    // }

}pool[MAXN<<3],*frog = pool,*segt;

Node *New(int l,int r,Node *lc,Node *rc){
    Node *ret = ++frog;
    *ret = (Node){l,r,MP(0,0),MP(N+1,0),lc,rc};
    if(l == r){
        if(v[l].size()) ret->min = v[l][0],ret->max = v[l][vt[l]];
    }
    return ret;
}

inline void build(Node *&v,int l,int r){
    v = New(l,r,NULL,NULL);
    if(l != r){
        int mid = (l + r) >> 1;
        build(v->lc,l,mid);build(v->rc,mid+1,r);
        v->pushup();
    }
}

void dfs(int v,int fa){
    in[v] = ++ts;
    FOR(i,1,log2N){
        f[v][i] = f[f[v][i-1]][i-1];
    }
    for(int i = head[v];i;i = e[i].next){
        //if(e[i].to != fa){
        if(e[i].to != fa){
            depth[e[i].to] = depth[v] + 1;
            f[e[i].to][0] = v;
            dfs(e[i].to,v);
        }
    }
    out[v] = ts;
}
/*
inline int query(int a,int b){
    int da = depth[a],db = depth[b];
    if(da != db){
        if(da < db) std::swap(a,b),std::swap(da,db);
        int d = da-db;
        FOR(i,0,log2N){
            if((1<<i)&d) a = f[a][i];
        }
    }
    if(a == b) return a;
    ROF(i,log2N,0){
        if(f[a][i] == f[b][i]) continue;
        a = f[a][i],b = f[b][i];
    }
    return f[a][0];
}
*/
inline int query(int x,int y){
    if(depth[x]<depth[y]) std::swap(x,y);
    for(int i=L[depth[x]];i>=0;i--)
        if(depth[f[x][i]]>=depth[y]) x=f[x][i];
    if(x==y) return x;
    for(int i=L[depth[x]];i>=0;i--)
        if(f[x][i]^f[y][i]) x=f[x][i],y=f[y][i];
    return f[x][0];
}
// inline int find(int x){
//     return x == fa[x] ? x : fa[x] = find(fa[x]);
// }

inline int find(int x){
    int fx=x,y;while(fx^fa[fx]) fx=fa[fx];
    while(x^fx) y=fa[x],fa[x]=fx,x=y;return x;
}

struct Data{
    int x,y;LL w;
    bool operator < (const Data &other) const {
        return w > other.w;
    }
};

std::priority_queue<Data> q;
LL ans[MAXN];

inline void insert(int x,LL w){
    //printf("%d\n",x);
    for(int i = head[x];i;i = e[i].next) q.push((Data){e[i].to,e[i].to,w + e[i].w});
    FOR(i,0,(int)dl[x].size()-1) q.push((Data){l1[dl[x][i]],r1[dl[x][i]],w+c[dl[x][i]]});
    for(int i = segt->query(in[x],out[x],0).second;i && in[l2[i]] < in[x];i = segt->query(in[x],out[x],0).second){
        segt->update(in[r2[i]],0);q.push((Data){l1[i],r1[i],1ll*w+c[i]});
    }
    for(int i = segt->query(in[x],out[x],1).second;i && in[r2[i]] > out[x];i = segt->query(in[x],out[x],1).second){
        segt->update(in[l2[i]],1);q.push((Data){l1[i],r1[i],w+c[i]});
    }
    ans[x] = w;
}


int main(){
    freopen("1.in","r",stdin);
    //freopen("1.out","w",stdout);
    scanf("%d%d%d",&N,&M,&K);
    // FOR(i,1,N-1){
    //     int u,v;LL w;scanf("%d%d%lld",&u,&v,&w);
    //     add(u,v,w);add(v,u,w);
    // }
    // log2N = log2(N);
    // for(int i=2;i<=N;i++) L[i]=L[i>>1]+1;
    // depth[1] = 1;dfs(1,0);
    
    // FOR(i,1,N) fa[i] = i;
    // FOR(i,1,M){
    //     scanf("%d%d%d%d%d",l1+i,r1+i,l2+i,r2+i,c+i);
    //     int lca = query(l2[i],r2[i]);//DEBUG(lca);
    //     dl[lca].push_back(i);
    // }
    // FOR(i,1,M){
    //     if(in[l2[i]] > in[r2[i]]) std::swap(l2[i],r2[i]);
    //     v[in[l2[i]]].push_back(MP(in[r2[i]],i));
    //     v[in[r2[i]]].push_back(MP(in[l2[i]],i));
    // }
    // FOR(i,1,N){
    //     std::sort(v[i].begin(),v[i].end());
    //     vs[i] = 0,vt[i] = (int)v[i].size()-1;
    // }

    for(int i=1,u,v,w;i<N;i++)
        scanf("%d%d%d",&u,&v,&w),add(u,v,w),add(v,u,w);
    for(int i=2;i<=N;i++) L[i]=L[i>>1]+1;
    f[1][0]=fa[N+1]=N+1,depth[1]=1,dfs(1,0);for(int i=1;i<=N;i++) fa[i]=i;
    for(int i=1;i<=M;i++)
        scanf("%d%d%d%d%d",l1+i,r1+i,l2+i,r2+i,c+i),dl[query(l2[i],r2[i])].push_back(i);
    for(int i=1;i<=M;i++)
    {
        if(in[l2[i]]>in[r2[i]]) std::swap(l2[i],r2[i]);
        v[in[l2[i]]].push_back(MP(in[r2[i]],i)),
        v[in[r2[i]]].push_back(MP(in[l2[i]],i));
    }
    for(int i=1;i<=N;i++) std::sort(v[i].begin(),v[i].end()),vs[i]=0,vt[i]=(int)v[i].size()-1;
    build(segt,1,N),ans[K]=0,insert(K,0),fa[K]=f[K][0];

    // //segt = Node::build(1,N);
    // build(segt,1,N);
    // ans[K] = 0;insert(K,0);fa[K] = f[K][0];
    /*
    while(!q.empty()){
        int x = q.top().x,y = q.top().y,lca = query(x,y);
        LL w = q.top().w;q.pop();//DEBUG(w);DEBUG((int)q.size());
       // DEBUG(w);
        for(int t = find(x);depth[t] >= depth[lca];t = find(fa[t]=f[t][0])) insert(t,w);//,DEBUG(t);
        for(int t = find(y);depth[t] >= depth[lca];t = find(fa[t]=f[t][0])) insert(t,w);//,DEBUG(t);
    }*/
     while(!q.empty()){
        int x=q.top().x,y=q.top().y,c=query(x,y);LL w=q.top().w;q.pop();
        for(int t=find(x);depth[t]>=depth[c];t=find(fa[t]=f[t][0])) insert(t,w);//,debug(t)ln;
        for(int t=find(y);depth[t]>=depth[c];t=find(fa[t]=f[t][0])) insert(t,w);//,debug(t)ln;
    }
    FOR(i,1,N) printf("%lld ",ans[i]);puts("");
    return 0;
}