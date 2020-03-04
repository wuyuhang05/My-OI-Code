#include <algorithm>
#include <iostream>
#include <cstring>
#include <climits>
#include <cstdlib>
#include <cstdio>
#include <bitset>
#include <vector>
#include <cmath>
#include <ctime>
#include <queue>
#include <stack>
#include <map>
#include <set>

#define fi first
#define se second
#define U unsigned
#define P std::pair
#define LL long long
#define pb push_back
#define MP std::make_pair
#define all(x) x.begin(),x.end()
#define CLR(i,a) memset(i,a,sizeof(i))
#define FOR(i,a,b) for(int i = a;i <= b;++i)
#define ROF(i,a,b) for(int i = a;i >= b;--i)
#define DEBUG(x) std::cerr << #x << '=' << x << std::endl

const int MAXN = 2e5 + 5;
const double PI = acos(-1);

bool p[MAXN];
int prime[MAXN],tot,n;

inline void prework(){
	p[0] = p[1] = 1;
	FOR(i,2,MAXN-1){
		if(!p[i]) prime[++tot] = i;
		for(int j = 1;j <= tot && i*prime[j] < MAXN;++j){
			p[i*prime[j]] = 1;
			if(!(i%prime[j])) break;
		}
	}
}

struct Node{
	double x,y;
	Node(double x=0,double y=0) : x(x),y(y) {};

	inline Node operator + (const Node &t) const {
		return Node(x+t.x,y+t.y);
	}

	inline Node operator - (const Node &t) const {
		return Node(x-t.x,y-t.y);
	}

	inline Node operator * (const Node &t) const {
		return Node(x*t.x-y*t.y,x*t.y+y*t.x);
	}
}A[MAXN],B[MAXN];

int r[MAXN],N;
inline void FFT(Node A[],int opt){
	FOR(i,0,N) if(i < r[i]) std::swap(A[i],A[r[i]]);
	for(int mid = 1;mid < N;mid <<= 1){
		Node W(cos(PI/mid),opt*sin(PI/mid));
		for(int i = 0;i < N;i += (mid<<1)){
			Node w(1,0);
			for(int j = 0;j < mid;++j,w = w*W){
				Node x = A[i+j],y = w*A[i+mid+j];
				A[i+j] = x+y;A[i+mid+j] = x-y;
			}
		}
	}
	if(opt == -1) FOR(i,0,N) A[i].x /= N;
}

struct Edge{
	int to,nxt;
}e[MAXN<<1];
int head[MAXN],cnt;

inline void add(int u,int v){
	e[++cnt] = (Edge){u,head[v]};head[v] = cnt;
	e[++cnt] = (Edge){v,head[u]};head[u] = cnt;
}

int mx[MAXN],sz[MAXN];
int root;
bool vis[MAXN];

inline void getroot(int v,int fa=0){
	mx[v] = 0;sz[v] = 1;
	for(int i = head[v];i;i = e[i].nxt){
		if(e[i].to == fa || vis[e[i].to]) continue;
		getroot(e[i].to,v);
		sz[v] += sz[e[i].to];mx[v] = std::max(mx[v],sz[e[i].to]);
	}
	mx[v] = std::max(mx[v],mx[0]-sz[v]);
	if(mx[root] > mx[v]) root = v;
}

int dep[MAXN],mxdis;
std::vector<int> S;
int cnt1[MAXN],cnt2[MAXN];

inline void getdis(int v,int fa=0){
	mxdis = std::max(mxdis,dep[v]);
	for(int i = head[v];i;i = e[i].nxt){
		if(e[i].to == fa || vis[e[i].to]) continue;
		dep[e[i].to] = dep[v] + 1;
		getdis(e[i].to,v);
	}
}
LL ans = 0;

inline void dfs(int v,int d,int fa=0){
	cnt2[dep[v]] += d;
	if(d == -1) cnt1[dep[v]]++;
	for(int i = head[v];i;i = e[i].nxt) if(e[i].to != fa && !vis[e[i].to]) dfs(e[i].to,d,v);
}

inline LL calc(int v){
	dep[v] = 0;mxdis = 0;getdis(v);int len = 0;LL res = 0;
	cnt1[0] = 1;N = 1;
	while(N <= 2*mxdis) N <<= 1,len++;
	FOR(i,0,N) r[i] = (r[i>>1]>>1)|((i&1)<<(len-1));
	// DEBUG(1);
	for(int i = head[v];i;i = e[i].nxt){
		if(vis[e[i].to]) continue;
		dfs(e[i].to,1,v);
		FOR(j,0,N) A[j] = Node(cnt1[j],0.0),B[j] = Node(cnt2[j],0.0);
		FFT(A,1);FFT(B,1);
		FOR(j,0,N-1) A[j] = A[j]*B[j];
		FFT(A,-1);
		dfs(e[i].to,-1,v);
		FOR(j,0,N-1){
			if(p[j]) continue;
			res += (LL)(A[j].x+0.5);
		}
	}
	FOR(i,0,N) cnt1[i] = A[i].x = A[i].y = B[i].x = B[i].y = 0;
	return res;
}

inline void work(int v){
	int t = 0;
	vis[v] = 1;ans += (t=calc(v));
	// DEBUG(v);DEBUG(t);
	for(int i = head[v];i;i = e[i].nxt){
		if(vis[e[i].to]) continue;
		mx[root = 0] = sz[e[i].to];
		getroot(e[i].to,v);
		work(root);
	}
}

int main(){
	// DEBUG(1);
	prework(); 
	scanf("%d",&n);
	FOR(i,2,n){
		int u,v;scanf("%d%d",&u,&v);add(u,v);
	}
	mx[root = 0] = n;getroot(1);
	work(root);
	printf("%lf\n",1.0*ans/(1.0*n*(n-1)/2.0));
	return 0;
}