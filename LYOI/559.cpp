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

const int MAXN = 1000 + 5;
const int MAXM = 2000 + 5;

struct Node{
    struct Edge *firstEdge;
    LL dist;bool used;
    int wait[MAXN],num;
}node[MAXN];

struct Edge{
    Node *s,*t;
    int w;
    Edge *next;
}pool[MAXM<<1],*frog = pool;

Edge *New(Node *s,Node *t,LL w){
    Edge *ret = ++frog;
    ret->s = s;ret->t = t;
    ret->w = w;ret->next = s->firstEdge;
    return ret;
}

inline void add(int u,int v,LL w){
    node[u].firstEdge = New(&node[u],&node[v],w);
    node[v].firstEdge = New(&node[v],&node[u],w);
}

#define P std::pair<LL,Node *>
#define MP std::make_pair

inline LL dij(int N){
    std::priority_queue<P,std::vector<P>,std::greater<P> > q;
    FOR(i,1,N){
        node[i].dist = LLONG_MAX;
        node[i].used = false;
    }
    q.push(MP(node[1].dist = 0,&node[1]));
    while(!q.empty()){
        Node *v = q.top().second;q.pop();
        if(v->used) continue;
        v->used = true;
        for(Edge *e = v->firstEdge;e;e = e->next){
            LL gx = v->dist + e->w;
            gx += std::max(0ll,e->t->wait[gx]-gx);
            if(e->t->dist > gx){
                e->t->dist = gx;
                q.push(MP(e->t->dist,e->t));
            }
        }
    }
    return node[N].dist;
}

int N,M;
std::vector<int> v;

int main(){
    freopen("travel.in","r",stdin);
	freopen("travel.out","w",stdout);
    read(N);read(M);
    FOR(i,1,M){
        int u,v;LL w;
        read(u);read(v);read(w);
        add(u,v,w);
    }
    FOR(i,1,N){
        node[i].num = i;
        int k;read(k);
        if(!k) continue;
        v.clear();
        FOR(j,1,k){
            int x;read(x);
            v.push_back(x);
        }
        std::sort(v.begin(),v.end());
        if(v.size()) node[i].wait[v[v.size()-1]] = v[v.size()-1];
        ROF(j,(int)v.size()-2,0){ // 预处理时间区间
            if(v[j]+1 == v[j+1]) node[i].wait[v[j]] = node[i].wait[v[j]+1];
            else node[i].wait[v[j]] = v[j];
        }
    }
    printf("%lld\n",dij(N));
    return 0;
}
/*
4 6 
1 2 2 
1 3 3 
1 4 8 
2 3 4 
2 4 5 
3 4 3 
0 
1 3 
2 3 4 
0
*/