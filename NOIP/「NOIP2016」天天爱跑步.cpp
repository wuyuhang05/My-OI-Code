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
#define RFOR(i,a,b) for(Re int i = a;i >= b;--i)
#define SFOR(i,a,b,c) for(Re int i = a;i <= b;i+=c)
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

const int MAXN = 300000 + 5;

struct Node{
    struct Edge *firstEdge;
    int depth,ts,num; // cnt:起点
    bool vis;
}node[MAXN];

struct Edge{
    Node *s,*t;
    Edge *next;
}pool[MAXN*2],*frog = pool;

struct Person{
    int s,t;
    int lca,len;
}p[MAXN];

Edge *New(Node *s,Node *t){
    Edge *ret = ++frog;
    ret->s = s;ret->t = t;
    ret->next = s->firstEdge;
    return ret;
}

inline void add(int u,int v){
    node[u].firstEdge = New(&node[u],&node[v]);
    node[v].firstEdge = New(&node[v],&node[u]);
}

int N,M;
int f[MAXN][30];
float log2N;

inline void init(){
    CLR(f,-1);
    FOR(i,1,N){
        node[i].num = i;
        node[i].depth = 0;
        node[i].vis = false;
    }
    log2N = log2(N);
    node[1].depth = 1;
    node[1].vis = true;
}

void dfs(Node *v){
    #define EFOR(i,v) for(Edge *i = v->firstEdge;i;i = i->next)
    FOR(i,1,log2N){
        if((1 << i) >= v->depth) break;
        f[v->num][i] = f[f[v->num][i-1]][i-1];
    }
    EFOR(e,v){
        if(!e->t->vis){
            e->t->vis = true;
            f[e->t->num][0] = v->num;
            e->t->depth = v->depth + 1;
            dfs(e->t);
        }
    }
    #undef EFOR
}

inline int lca(int x,int y){
    int dx = node[x].depth,dy = node[y].depth;
    if(dx != dy){
        if(dx < dy){
            std::swap(x,y);
            std::swap(dx,dy);
        }
        int d = dx - dy;
        FOR(i,0,log2N){
            if((1 << i) & d) x = f[x][i];
        }
    }
    if(x == y) return x;
    RFOR(i,log2N,0){
        // if(node[f[x][i]].depth < 0) continue;
        if(f[x][i] == f[y][i]) continue;
        else x = f[x][i],y = f[y][i];
    }
    return f[x][0];
}

std::vector<int> cf[MAXN],cf1[MAXN],cf2[MAXN];
int max,t[MAXN],ans[MAXN],cnt[MAXN];
// cf: lca 为 i 的人起点深度

void dfs1(Node *v){
    #define EFOR(i,v) for(Edge *i = v->firstEdge;i;i = i->next)
    int now = v->depth + v->ts,pre; // now 记录右边，t 记录左边，pre 记录
    if(now <= max) pre = t[now];
    EFOR(e,v)
        if(v->depth < e->t->depth)
            dfs1(e->t);
    t[v->depth] += cnt[v->num];
    if(now <= max)
        ans[v->num] += t[now]-pre;
    int sz = cf[v->num].size()-1;
    RFOR(i,sz,0)
        t[cf[v->num][i]]--;
    #undef EFOR
}

void dfs2(Node *v){
    #define EFOR(i,v) for(Edge *i = v->firstEdge;i;i = i->next)
    int now = v->depth - v->ts + MAXN,pre; // 同上
    pre = t[now];
    EFOR(e,v)
        if(v->depth < e->t->depth) dfs2(e->t);
    int sz = cf1[v->num].size()-1;
    RFOR(i,sz,0)
        ++t[cf1[v->num][i]+MAXN];
    sz = cf2[v->num].size()-1;
    ans[v->num] += t[now] - pre;
    RFOR(i,sz,0)
        --t[cf2[v->num][i]+MAXN];
    // DEBUG(ans[v->num]);
    #undef EFOR
}

int main(){
    read(N);read(M);
    FOR(i,1,N-1){
        int u,v;read(u);read(v);
        add(u,v);
    }
    init();
    dfs(&node[1]);
    FOR(i,1,N){
        read(node[i].ts);
        max = std::max(max,node[i].depth);
    }
    // DEBUG(max);
    CLR(t,0);CLR(cnt,0);
    // puts("---------------------------");
    FOR(i,1,M){
        read(p[i].s);read(p[i].t);
        // node[p[i].s].cnt++;
        cnt[p[i].s]++;
        p[i].lca = lca(p[i].s,p[i].t);
        p[i].len = node[p[i].s].depth + node[p[i].t].depth - 2*node[p[i].lca].depth;
        cf[p[i].lca].push_back(node[p[i].s].depth); // 记录 lca 为 i 的人的深度
        // printf("%d %d\n",p[i].lca,p[i].len);
    }
    dfs1(&node[1]); // 处理向上的路径
    CLR(t,0);
    FOR(i,1,M){
        int v = node[p[i].t].depth - p[i].len;
        cf1[p[i].t].push_back(v); // 记录终点为 i 的人的等式左边
        cf2[p[i].lca].push_back(v); // 记录 lca 为 i 的人的等式左边
    }
    dfs2(&node[1]);
    FOR(i,1,M)
        if(node[p[i].s].depth - node[p[i].lca].depth == node[p[i].lca].ts) --ans[p[i].lca];
    FOR(i,1,N)
        printf("%d%c",ans[i],(i == N) ? '\n' : ' ');
    return 0;
}