#include <iostream>
#include <cstring>
#include <cstdio>
#define LL long long
#define DEBUG(x) std::cerr << #x << '=' << x << std::endl
#define FOR(i,a,b) for(int i = a;i <= b;i++)
#define RFOR(i,a,b) for(int i = a;i >= b;i--)
#define CLR(i,a) memset(i,a,sizeof(i)

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
// using namespace fastIO;

inline void read(int &x){
    scanf("%d",&x);
}

inline void read(LL &x){
    scanf("%lld",&x);
}

const int MAXN = 500000 + 5;
const int MAXM = 500000 + 5;

struct Node{
    struct Edge *firstEdge;
    int num;
    bool flag;
    int depth;
}node[MAXN],tree[MAXN];

int fa[MAXN];

struct Edge{
    Node *s,*t;
    Edge *next;
    bool vis;
}pool[MAXM*2],*frog = pool;

Edge *New(Node *s,Node *t){
    Edge *ret = ++frog;
    ret->s = s;ret->t = t;
    ret->next = s->firstEdge;
    return ret;
}

struct Data{
    int u,v;
    bool flag;
}e[MAXM];

inline void add(int u,int v){
    node[u].firstEdge = New(&node[u],&node[v]);
    node[v].firstEdge = New(&node[v],&node[u]);
}

int ans = 0;
int N,M;
int f[MAXN];

inline void init(){
    for(int i = 1;i <= N;i++)
        f[i] = i;
}

int find(int x){
    return x == f[x] ? x : f[x] = find(f[x]);
}

void dfs(Node *v) {
    v->depth=node[fa[v->num]].depth+1;
    f[v->num]=v->num;
    for(Edge *e = v->firstEdge;e;e = e->next) {
        if(e->t->num==fa[v->num]) continue;
        fa[e->t->num]=v->num;
        dfs(e->t);
    }
}

int ts = 0,ha;

int main(){
    read(N);read(M);read(ha);
    init();
    for(int i = 1;i <= N;i++)
        node[i].num = i;
    memset(fa,0,sizeof(fa));
    for(int i=1;i<=M;i++){
        read(e[i].u);
        read(e[i].v);
        if(find(e[i].u)!=find(e[i].v)) {
            f[f[e[i].u]] = e[i].v;
            e[i].flag = true;
            add(e[i].u,e[i].v);
        }
    }
    for(int i = 1;i <= N;i++){
        if(!node[i].depth){
            dfs(&node[i]);
        }
    }
    LL ans = 1;
    LL tot = 0;
    
    for(int i=1;i<=M;i++) {
        if(e[i].flag) ++tot;
        else {
            for(int x=find(e[i].u),y=find(e[i].v);x!=y;x=f[x]=find(fa[x]),--tot) {
                if(node[x].depth<node[y].depth)
                    std::swap(x,y);
            }
        }
        (ans*=tot+1)%=ha;
    }
    printf("%lld\n",ans);
    return 0;
}

