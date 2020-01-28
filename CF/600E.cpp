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

const int MAXN = 1e5 + 5;

struct Edge{
	int to,nxt;
}e[MAXN<<1];

int head[MAXN],cnt;
int n;

inline void add(int u,int v){
	e[++cnt] = (Edge){v,head[u]};head[u] = cnt;
	e[++cnt] = (Edge){u,head[v]};head[v] = cnt;
}

int son[MAXN],sz[MAXN];

inline void dfs1(int v,int fa=0){
	sz[v] = 1;
	for(int i = head[v];i;i = e[i].nxt){
		if(e[i].to == fa) continue;
		dfs1(e[i].to,v);sz[v] += sz[e[i].to];
		if(sz[son[v]] < sz[e[i].to]) son[v] = e[i].to;
	}
}

int t[MAXN],mx;
LL ans;

inline void add(int x){
	t[x]++;
	if(t[x] > mx) mx = t[x],ans = x;
	else if(t[x] == mx) ans += x;
}

inline void del(int x){
	t[x]--;
}

int ban;
int col[MAXN];

inline void change(int v,int fa,int opt){
	if(opt == 1) add(col[v]);
	else del(col[v]);
	for(int i = head[v];i;i = e[i].nxt){
		if(e[i].to == fa || e[i].to == ban) continue;
		change(e[i].to,v,opt);
	}
}

LL anss[MAXN];

inline void dfs2(int v,int fa=0,int tag=0){
	for(int i = head[v];i;i = e[i].nxt){
		if(e[i].to == fa || e[i].to == son[v]) continue;
		dfs2(e[i].to,v,0);
	}
	if(son[v]) dfs2(son[v],v,1);ban = son[v];
	// if(v == 1) FOR(i,1,3) printf("%d%c",t[i]," \n"[i==3]);
	change(v,fa,1);
	// if(v == 1) FOR(i,1,3) printf("%d%c",t[i]," \n"[i==3]);
	anss[v] = ans;ban = 0;
	if(!tag) change(v,fa,-1),mx = ans = 0;
}

int main(){
	scanf("%d",&n);
	FOR(i,1,n) scanf("%d",col+i);
	FOR(i,1,n-1){
		int u,v;scanf("%d%d",&u,&v);
		add(u,v);
	}
	dfs1(1);
	dfs2(1);
	FOR(i,1,n) printf("%lld%c",anss[i]," \n"[i==n]);
	return 0;
}