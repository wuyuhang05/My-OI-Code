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
#define int LL
const int MAXN = 200000 + 5;

struct Node{
	struct Edge *firstEdge;
	int val,depth;
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
const int MAXM = (1ll<<18) +2323;
int N,Q;
int ans[MAXM];

void dfs(Node *v,Node *fa=NULL){
	ans[v->depth] ^= v->val;//DEBUG(v->depth);
	for(Edge *e = v->firstEdge;e;e = e->next){
		if(e->t == fa) continue;
		e->t->depth = v->depth + 1;
		dfs(e->t,v);
	}
}

signed main(){
	read(N);read(Q);
	FOR(i,1,N-1){
		int u,v;read(u);read(v);++u;++v;
		add(u,v);
	}
	FOR(i,1,N) read(node[i].val);
	dfs(&node[1]);
	//FOR(i,1,N) DEBUG(ans[i]);
	FOR(i,1,18){
		FOR(j,0,(1ll<<18)-1){
			if(!(j&(1ll<<(i-1))))
				ans[j|(1<<(i-1))] ^= ans[j];
		}
	}
	//FOR(i,1,N) DEBUG(ans[i]);
	while(Q--){
		int x;read(x);
		--x;
		int r = (1ll<<18)-1;
		x &= r;r ^= x;
		printf("%lld\n",ans[r]);
	}
	return 0;
}
/*
4 3
0 1
1 2
0 3
1 5 8 7
1
2
3
*/
