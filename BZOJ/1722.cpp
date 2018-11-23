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
#define Re register
#define LL long long
#define U unsigned
#define FOR(i,a,b) for(Re int i = a;i <= b;++i)
#define ROF(i,a,b) for(Re int i = a;i >= b;--i)
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
const int MAXN = 500+5;
const int MAXM = MAXN;

struct Node{
	struct Edge *firstEdge;
	int dist,num,size;
}node[MAXN];

struct Edge{
	Node *s,*t;
	Edge *next;
}pool[MAXN<<1],*frog = pool;

Edge *New(Node *s,Node *t){
	Edge *ret = ++frog;
	*ret = (Edge){s,t,s->firstEdge};
	return ret;
}

inline void add(int u,int v){
	node[u].firstEdge = New(&node[u],&node[v]);
}

int N,X;
int f[MAXN][MAXM][2];
// f[i][j][0/1]: 以 i 为根的子树，选了 j 对，是否选择 i 的最大产奶量 
// f[i][j][0] = std::max()

void dfs(Node *v){
	v->size = 1;
	for(Edge *e = v->firstEdge;e;e = e->next){
		//if(e->t == v) continue;
		dfs(e->t);v->size += e->t->size;
		ROF(j,v->size-1,0){
			for(int k = 0;k < e->t->size && k <= j;++k) f[v->num][j][0] = std::max(f[v->num][j][0],f[v->num][j-k][0]+std::max(f[e->t->num][k][0],f[e->t->num][k][1]));
			if(!v->num) continue;
			for(int k = 0;k < e->t->size && k <= j;++k) f[v->num][j][1] = std::max(f[v->num][j][1],f[v->num][j-k][1]+f[e->t->num][k][0]);
			for(int k = 0;k < e->t->size && k < j;++k) f[v->num][j][1] = std::max(f[v->num][j][1],f[v->num][j-k-1][1]+f[e->t->num][k][1]);
		}
	}
	FOR(i,0,v->size-1) f[v->num][i][1] += v->dist;
}
 
signed main(){
	scanf("%lld%lld",&N,&X);
	FOR(i,0,N) FOR(j,0,N) f[i][j][0] = f[i][j][1] = INT_MIN;
	FOR(i,0,N) f[i][0][0] = f[i][0][1] = 0;
	FOR(i,1,N){
		node[i].num = i;
		int fa;scanf("%lld%lld",&node[i].dist,&fa);
		//DEBUG(node[i].dist);
		add(fa,i);//add(i,fa);
	}
	int ans = -1;dfs(&node[0]);//DEBUG(node[0].size);
	ROF(i,node[0].size-1,0) {
		//DEBUG(f[0][i][0]);
		if(f[0][i][0] >= X) {ans = i;break;}
	}
	printf("%lld\n",ans);
	return 0;
}
/*
5 8
-1 0
3 1
5 1
-3 3
2 0
*/

