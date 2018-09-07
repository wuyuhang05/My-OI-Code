#include <algorithm>
#include <iostream>
#include <cstring>
#include <climits>
#include <cstdio>
#include <vector>
#include <cmath>
#include <queue>
#include <stack>
#include <map>
#include <set>

#define R register
#define LL long long
#define U unsigned
#define FOR(i,a,b) for(R int i = a;i <= b;++i)
#define RFOR(i,a,b) for(R int i = a;i >= b;--i)
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
    int depth,num;
    LL a;
    bool vis;
}node[MAXN];

struct Edge{
    Node *s,*t;
    Edge *next;
}pool[MAXN*2],*frog = pool;

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
float log2N;
int fa[MAXN][25];
LL fu[MAXN][25],fv[MAXN][25],cnt[MAXN][25];

inline void pre(){
    // CLR(fa,-1);
    FOR(i,1,N){
        node[i].vis = false;
        node[i].depth = 0;
        node[i].num = i;
    }
    node[1].depth = 1;
    node[1].vis = true;
    log2N = log2(N) + 1;
    // log2N = 20;
}

void dfs(Node *v){
    FOR(i,0,log2N){
        cnt[v->num][i] = cnt[fa[v->num][0]][i] + ((v->a & (1 << i))==0);
    }
    for(Edge *e = v->firstEdge;e;e = e->next){
        if(!e->t->vis){
            e->t->vis = true;
            e->t->depth = v->depth + 1;
            fa[e->t->num][0] = v->num;
            dfs(e->t);
        }
    }
}

int lca(int x,int y){
    int dx = node[x].depth,dy = node[y].depth;
    if(dx != dy){
        if(dx < dy){
            std::swap(x,y);
            std::swap(dx,dy);
        }
        int d = dx - dy;
        FOR(i,0,log2N){
            if((1 << i) & d) x = fa[x][i];
        }
    }
    if(x == y) return x;
    RFOR(i,log2N,0){
        if(node[fa[x][i]].depth < 0) continue;
        if(fa[x][i] == fa[y][i]) continue;
        x = fa[x][i];y = fa[y][i];
    }
    return fa[x][0];
}

LL query1(LL v,LL l){
    LL ret = 0;
    RFOR(i,log2N,0){
        if(node[fa[v][i]].depth >= node[l].depth){
            ret += fu[v][i];
            v = fa[v][i];
            ret += (1ll << i) * (cnt[v][i] - cnt[l][i]);
        }
    }
    return ret;
}

LL query2(LL v,LL d){
    LL ret = 0;
    d++;LL t = v;
    FOR(i,0,log2N){
        if(d & (1 << i)){
            ret += fv[v][i];
            ret += (1ll << i) * (cnt[t][i] - cnt[v][i]);
            v = fa[v][i];
        }
    }
    return ret;
}

int main(){
    read(N);read(M);
    pre();
    FOR(i,1,N) read(node[i].a);
    FOR(i,1,N-1){
        int u,v;read(u);read(v);
        add(u,v);
    }
    dfs(&node[1]);
    FOR(i,1,N) fu[i][0] = fv[i][0] = node[i].a;
    FOR(j,1,log2N){
        FOR(i,1,N){
            fa[i][j] = fa[fa[i][j-1]][j-1];// printf("%d ",fa[i][j]);
            fu[i][j] = fu[i][j-1] + fu[fa[i][j-1]][j-1] + (1ll << (j-1)) * (cnt[fa[i][j-1]][j-1] - cnt[fa[i][j]][j-1]);
            fv[i][j] = fv[i][j-1] + fv[fa[i][j-1]][j-1] + (1ll << (j-1)) * (cnt[i][j-1] - cnt[fa[i][j-1]][j-1]);
        }
    }
    // put();
    while(M--){
        int u,v;read(u);read(v);
        int l = lca(u,v),d = node[u].depth + node[v].depth - node[l].depth*2;
        // DEBUG(l);
        printf("%lld\n",query1(u,fa[l][0]) + query2(v,d) - query2(l,node[u].depth - node[l].depth));
    }
    return 0;
}
