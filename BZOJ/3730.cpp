#pragma GCC optimize("Ofast")
#include <unordered_map>
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
#define P std::pair<int,int>
#define LL long long
#define pb push_back
#define MP std::make_pair
#define all(x) x.begin(),x.end()
#define CLR(i,a) memset(i,a,sizeof(i))
#define FOR(i,a,b) for(register int i = a;i <= b;++i)
#define ROF(i,a,b) for(register int i = a;i >= b;--i)
#define DEBUG(x) std::cerr << #x << '=' << x << std::endl

const int MAXN = 1e5 + 5;

inline char nc(){
    #define SIZE 1000000+3
    static char buf[SIZE],*p1 = buf+SIZE,*p2 = buf+SIZE;
    if(p1 == p2){
        p1 = buf;p2 = buf+fread(buf,1,SIZE,stdin);
        if(p1 == p2) return -1;
    }
    return *p1++;
}
 
inline void read(int &x){
    x = 0;int flag = 0;char ch = nc();
    while(!isdigit(ch)){
        if(ch == '-') flag = 1;
        ch = nc();
    }
    while(isdigit(ch)){
        x = (x<<1) + (x<<3) + (ch^'0');
        ch = nc();
    }
    if(flag) x = -x;
}

int sm[MAXN<<6],ch[MAXN<<6][2],tot;
#define lc (ch[x][0])
#define rc (ch[x][1])

int pool[MAXN<<6],*tail = pool;
struct TREE{
	#define lowbit(x) ((x)&(-(x)))
	int mx;
	// std::vector<int> tree;
	int *tree;

	inline void init(int x){
		++x;
		mx = x;
		tree = tail;tail += (mx+2);
		//tree.resize(mx+2);
	}

	inline void add(int pos,int x){
		++pos;pos = std::min(pos,mx);
		// assert(pos <= mx);
		for(;pos <= mx;pos += lowbit(pos)) tree[pos] += x;
	}

	inline int query(int pos){
		int res = 0;++pos;pos = std::min(pos,mx);
		if(pos <= 0) return 0;
		for(;pos;pos -= lowbit(pos)) res += tree[pos];
		return res;
	}
}tree[MAXN],tree2[MAXN];

struct Edge{
	int to,nxt;
}e[MAXN<<1];
int head[MAXN],cnt;

inline void add(int u,int v){
	e[++cnt] = (Edge){v,head[u]};head[u] = cnt;
	e[++cnt] = (Edge){u,head[v]};head[v] = cnt;
}

std::vector<int> G[MAXN];

int sz[MAXN],mx[MAXN],n,val[MAXN],root;
int a[MAXN];bool vis[MAXN];
std::unordered_map<int,P> S[MAXN];
std::unordered_map<int,int> frm[MAXN];
int fa[MAXN];

inline void getroot(int v,int fa=0){
	sz[v] = 1;mx[v] = 0;
	for(int i = head[v];i;i = e[i].nxt){
		if(e[i].to == fa || vis[e[i].to]) continue;
		getroot(e[i].to,v);
		sz[v] += sz[e[i].to];mx[v] = std::max(mx[v],sz[e[i].to]);
	}
	mx[v] = std::max(mx[v],mx[0]-sz[v]);
	if(mx[v] < mx[root]) root = v;
}

int dep[MAXN],now;
//<dep,depr>
inline void dfs(int v,int fa=0){
	S[now][v].fi = dep[v];
	frm[::fa[now]][v] = now;
	for(int i = head[v];i;i = e[i].nxt){
		if(e[i].to == fa || vis[e[i].to]) continue;
		dep[e[i].to] = dep[v] + 1;
		dfs(e[i].to,v);
	}
}

inline void build(int v){
	// DEBUG(v);
	now = v;dep[v] = 0;dfs(v); // add 1
	int mx1 = 0,mx2 = 0;
	for(auto x:S[v]) mx1 = std::max(mx1,x.se.fi),mx2 = std::max(mx2,x.se.se);
	tree[v].init(mx1);tree2[v].init(mx2);
	for(auto x:S[v]){
		tree[v].add(x.se.fi,val[x.fi]);
		tree2[v].add(x.se.se,val[x.fi]);
		// tree[v].update(tree[v].root,0,mx1,x.se.fi,val[x.fi]);
		// tree2[v].update(tree2[v].root,0,mx2,x.se.se,val[x.fi]);
	}
}

inline void dfs2(int v,int fa=0){
	S[now][v] = MP(0,dep[v]);
	for(int i = head[v];i;i = e[i].nxt){
		if(e[i].to == fa || vis[e[i].to]) continue;
		dep[e[i].to] = dep[v] + 1;
		dfs2(e[i].to,v);
	}
}

inline void work(int v){
	vis[v] = 1;
	build(v);
	for(int i = head[v];i;i = e[i].nxt){
		if(vis[e[i].to]) continue;
		mx[root = 0] = sz[e[i].to];getroot(e[i].to,v);
		G[v].pb(root);fa[root] = v;
		dep[e[i].to] = 0;::now = root;dfs2(e[i].to,v);
		work(root);
	}
}

int x,y,ans;
int RT;
int total = 0;
inline void query(int v){
	++total;
	if(v == x) {ans += tree[v].query(y);return;}
	auto t = S[v][x];
	ans += tree[v].query(y-t.fi);
	int nxt = frm[v][x];
	ans -= tree2[nxt].query(y-t.fi-1);query(nxt);
}

int main(){
	// freopen("6.in","r",stdin);
	// freopen("5.out","w",stdout);
	// DEBUG(1);
	int m;read(n);read(m);
	FOR(i,1,n) read(val[i]);
	FOR(i,2,n){
		int u,v;read(u);read(v);
		add(u,v);
	}
	dep[1] = 0;dfs2(1,0);
	mx[root = 0] = n;getroot(1);RT = root;
	work(root);
	// DEBUG(1);
	// exit(0);
	int lst = 0;
	FOR(i,1,m){
		// DEBUG(i);
		int opt;read(opt);read(x);read(y);
		x ^= lst;y ^= lst;ans = 0;
		if(!opt){
			total = 0;query(RT);
			printf("%d\n",lst=ans);
		}
		else{
			int t = x;total = 0;
			while(t){
				++total;
				// tree[t].update(tree[t].root,0,tree[t].mx,S[t][x].fi,-val[x]+y);
				// tree2[t].update(tree2[t].root,0,tree2[t].mx,S[t][x].se,-val[x]+y);
				auto tmp = S[t][x];
				tree[t].add(tmp.fi,-val[x]+y);
				tree2[t].add(tmp.se,-val[x]+y);
				t = fa[t];
			}
			// DEBUG(total);
			val[x] = y;
		}
	}
	return 0;
}