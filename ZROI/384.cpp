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

const int MAXN = 100000 + 5;

struct Node{
    struct Edge *firstEdge;
    int deg;
    bool vis,col;
}node[MAXN];

struct Edge{
    Node *s,*t;
    Edge *next;
}pool[MAXN],*frog = pool;

Edge *New(Node *s,Node *t){
    Edge *ret = ++frog;
    ret->s = s;ret->t = t;
    ret->next = s->firstEdge;
    return ret;
}

inline void add(int u,int v){
    node[u].firstEdge = New(&node[u],&node[v]);
    node[v].deg++;
}

int N;

int main(){
    read(N);
    FOR(i,1,N){
        int x;read(x);
        // if(x == i) continue;
        add(i,x);
    }
    std::queue<Node *> q;
    FOR(i,1,N) if(!node[i].deg) q.push(&node[i]),node[i].vis = true;
    while(!q.empty()){
        Node *v = q.front();q.pop();
        for(Edge *e = v->firstEdge;e;e = e->next){
            e->t->deg--;
            if(!v->col && !e->t->vis){
                e->t->col = true;
                e->t->vis = true;
                q.push(e->t);
                continue;
            }
            if(!e->t->deg && !e->t->vis){
                q.push(e->t);
                e->t->vis = true;
            }
        }
    }
    int cnt=0,ans=0;
    FOR(i,1,N){
        if(node[i].col) ans++;
        if(node[i].deg) cnt++;
    }
    //DEBUG(cnt);DEBUG(ans);
    printf("%d\n",ans+cnt/2);
    return 0;
}