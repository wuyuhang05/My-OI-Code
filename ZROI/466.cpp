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

const int MAXN = 200+5;

struct Node{
	struct Edge *firstEdge;
	int chain,depth,num;
}node[MAXN];

struct Edge{
	Node *s,*t;
	Edge *next; 
}pool[MAXN<<1],*frog = pool;

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

int N;
long double f[MAXN][MAXN][MAXN];
long double g[MAXN][MAXN];
int max1[MAXN],max2[MAXN];

bool cmp(Node *a,Node *b){
	return a->chain < b->chain;
}

const double EPS = 1e-9;

void dfs(Node *v,Node *fa){
	f[v->num][0][0] = 1;std::vector<Node *> ch;
	for(Edge *e = v->firstEdge;e;e = e->next){
		if(e->t == fa) continue;
		dfs(e->t,v);ch.push_back(e->t);//DEBUG(e->t->num);
	}
	std::sort(ch.begin(),ch.end(),cmp);//DEBUG(v->num);
	DEBUG(ch.size());
	FOR(k,0,(int)ch.size()-1){
		Node *t = ch[k];
		FOR(i,0,v->depth){
			FOR(j,0,v->chain){
				g[i][j] = f[v->num][i][j];
				f[v->num][i][j] = 0;
			}
		}
		FOR(i1,0,v->depth){
			FOR(j1,0,v->chain){
				if(std::fabs(g[i1][j1]) < EPS) continue;
				FOR(i2,0,t->depth){
					FOR(j2,0,t->chain){
						if(std::fabs(f[t->num][i2][j2]) < EPS) continue;
						long double x = g[i1][j1] * f[t->num][i2][j2] * 0.5;
						FOR(kk,1,2){
							int i = std::max(i1,i2+kk),j = std::max(i1+i2+kk,std::max(j1,j2));
							f[v->num][i][j] += x;//DEBUG(v->num);DEBUG(i);DEBUG(j);DEBUG(x);
						}
					}
				}
			}
		}
		v->chain = std::max(std::max(v->chain,t->chain),v->depth+t->depth+2);
		v->depth = std::max(v->depth,t->depth+2);
		//printf("%d %d %d %d\n",v->chain,t->chain,v->depth,t->depth);
	}
}

int main(){
	scanf("%d",&N);
	FOR(i,1,N) node[i].num = i;
	FOR(i,1,N-1){
		int u,v;scanf("%d%d",&u,&v);
		add(u,v);
	}
	//for(Edge *e = node[4].firstEdge;e;e = e->next) DEBUG(e->t->num);
	dfs(&node[1],&node[0]);
	long double ans = 0;
	FOR(i,0,node[1].depth)
		FOR(j,0,node[1].chain)
			ans += j*f[1][i][j];
	printf("%.17Lf",ans+0.00000000019260817);
	return 0;
}

