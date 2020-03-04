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

const int MAXN = 100000 + 5;

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

struct Node{
    struct Edge *firstEdge;
    int du,num;

    bool operator < (const Node &other) const {
        return num > other.num;
    }
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
    ++node[v].du;
}

int ans[MAXN],top=0;

inline void topsort(int N){
    top=0;
    std::priority_queue<Node *> q;
    FOR(i,1,N)
        if(!node[i].du)
            q.push(&node[i]);
    while(!q.empty()){
        Node *v = q.top();q.pop();
        ans[++top] = v->num;
        for(Edge *e = v->firstEdge;e;e = e->next){
            if(--e->t->du == 0) q.push(e->t);
        }
    }
    if(top != N) puts("Impossible!");
    else{
        RFOR(i,N,1) printf("%d%c",ans[i],(i == 1) ? '\n' : ' ');
    }
}

inline void Solve(){
    memset(node,0,sizeof(node));
    frog = pool;
    int N,M;read(N);read(M);
    FOR(i,1,N) node[i].num = i;
    FOR(i,1,M){
        int a,b;read(a);read(b);
        add(b,a);
    }
    topsort(N);
}

int main(){
    int T;read(T);
    while(T--) Solve();
    return 0;
}
