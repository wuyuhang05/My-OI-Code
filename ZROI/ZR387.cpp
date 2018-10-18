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
#define P std::pair<double,Node *>
#define MP std::make_pair
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
const int MAXM = 300000 +5;

struct Node{
	struct Edge *firstEdge;
	double dist;
	bool used;
}node[MAXN<<2];

struct Edge{
	Node *s,*t;
	double w;
	Edge *next;
}pool[MAXM<<3],*frog = pool;

Edge *New(Node *s,Node *t,double w){
	Edge *ret = ++frog;
	ret->s = s;ret->t = t;
	ret->w = w;ret->next = s->firstEdge;
	return ret;
}

inline void add(int u,int v,double w){
	w = std::fabs(w);
	//printf("%d %d %.3f\n",u,v,w);
	node[u].firstEdge = New(&node[u],&node[v],w);
	//node[v].firstEdge = New(&node[v],&node[u],w);
}

inline double f(double x){
	return 1.0/(1.0-x);
	//return (opt == 0) ? (x : ((opt == 1) ? 1.0/(1.0-x) : (x-1.0)/x));
}

int N,M;

inline int getp(int x,int pos){
	return (x-1)*3+pos;
}

inline double Dijkstra(int N){
	FOR(i,1,N) node[i].dist = (double)INT_MAX;
	std::priority_queue<P,std::vector<P>,std::greater<P> > q;
	q.push(MP(node[1].dist = 0.0,&node[1]));
	while(!q.empty()){
		Node *v = q.top().second;q.pop();
		if(v->used) continue;
		v->used = true;
		for(Edge *e = v->firstEdge;e;e = e->next){
			if(e->t->dist > v->dist + std::fabs(e->w)){
				e->t->dist = v->dist + std::fabs(e->w);
				q.push(MP(e->t->dist,e->t));
			}
		}
	}
	return std::min(node[N-1].dist,std::min(node[N-2].dist,node[N].dist));
}
//#define read(x) std::cin >> x
int main(){
	//freopen("a.in","r",stdin);
	read(N);read(M);
	FOR(i,1,M){
		int u,v,w;
		read(u);read(v);read(w);
		add(getp(u,1),getp(v,2),w);
		add(getp(v,1),getp(u,2),w);
		add(getp(u,2),getp(v,3),f(w));
		add(getp(v,2),getp(u,3),f(w));
		add(getp(u,3),getp(v,1),f(f(w)));
		add(getp(v,3),getp(u,1),f(f(w)));
	}
	printf("%.3f\n",Dijkstra(N * 3));
	return 0;
}
