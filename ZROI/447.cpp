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

const int MAXN = 500000 + 5;
const int MAXM = 1000000 + 5;

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
struct Node{
    struct Edge *firstEdge;
    int dist;bool used;
}node[MAXN];

struct Edge{
    Node *s,*t;
    int w,l,r,k;
    Edge *next;
}pool[MAXM<<1],*frog = pool;

Edge *New(Node *s,Node *t,int w,int l,int r,int k){
    Edge *ret = ++frog;
    ret->s = s;ret->t = t;
    ret->w = w;ret->l = l;
    ret->r = r;ret->k = k;
    ret->next = s->firstEdge;
    return ret;
}

inline void add(int u,int v,int w,int l,int r,int k){
    node[u].firstEdge = New(&node[u],&node[v],w,l,r,k);
    node[v].firstEdge = New(&node[v],&node[u],w,l,r,k);
}
#define P std::pair<int,Node *>
#define MP std::make_pair

inline int calc(int start,int l,int r,int k,int w){
    int pos = start%k;
    LL ret = 0ll;
    if(pos <= r && pos >= l){
        if(r-pos+1>=w) return w+start;
        ret = r-pos+1;w-=ret;
        pos = r+1;
    }
    if(pos > r) ret += k-pos;
    else ret -= pos;
    pos = r-l+1;
    ret += 1ll*(w-1)/pos*k;
    w = (w-1)%pos+1;
    ret += l+w;
    return start+ret;
}

int N,M;

inline void dij(){
    std::priority_queue<P,std::vector<P>,std::greater<P> > q;
    FOR(i,1,N) node[i].dist = LLONG_MAX; // LLONG_MAX
    q.push(MP(node[1].dist = 0,&node[1]));
    while(!q.empty()){
        Node *v = q.top().second;q.pop();//DEBUG(v);
        if(v->used) continue;
        v->used = true;
        for(Edge *e = v->firstEdge;e;e = e->next){
            int d = calc(v->dist,e->l,e->r,e->k,e->w);
            if(d < e->t->dist){
                e->t->dist = d;
                q.push(MP(e->t->dist,e->t));
            }
        }
    }
    FOR(i,1,N){
        printf("%lld\n",node[i].dist);
    }
}

signed main(){
    //DEBUG(calc(3,1,2,3,7));
    read(N);read(M);
    FOR(i,1,M){
        int u,v,w,k,l,r;
        read(u);read(v);read(w);read(k);read(l);read(r);
        add(u,v,w,l,r,k);
    }
    dij();
    return 0;
}