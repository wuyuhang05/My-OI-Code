
// Problem : #6405. 「ICPC World Finals 2018」征服世界
// Contest : LibreOJ
// URL : https://loj.ac/problem/6405
// Memory Limit : 1024 MB
// Time Limit : 8000 ms
// Powered by CP Editor (https://github.com/cpeditor/cpeditor)

#include<bits/stdc++.h>
#include<ext/pb_ds/priority_queue.hpp>

#define fi first
#define se second
#define U unsigned
#define P std::pair<int,int>
#define LL long long
#define pb push_back
#define MP std::make_pair
#define all(x) x.begin(),x.end()
#define CLR(i,a) memset(i,a,sizeof(i))
#define FOR(i,a,b) for(int i = a;i <= b;++i)
#define ROF(i,a,b) for(int i = a;i >= b;--i)
#define DEBUG(x) std::cerr << #x << '=' << x << std::endl

const int MAXN = 2e5 + 5;

struct Edge{
	int to,w,nxt;
}e[MAXN<<1];
int head[MAXN],cnt;

inline void add(int u,int v,int w){
	e[++cnt] = (Edge){v,w,head[u]};head[u] = cnt;
	e[++cnt] = (Edge){u,w,head[v]};head[v] = cnt;
}

int dep[MAXN];

inline void dfs1(int v,int fa=0){
	for(int i = head[v];i;i = e[i].nxt){
		if(e[i].to == fa) continue;
		dep[e[i].to] = dep[v]+1;dfs(e[i].to,v);
	}
}

int n;
int a[MAXN];
// > 0 hole  < 0 mouse
int ans;
__gnu_pbds::priority_queue<int,std::greater<int> > q1[MAXN],q2[MAXN];

inline void dfs2(int v,int fa=0){
	flak;wjfl;akqfkawl;kfl;awkfl;w
}

int main(){
	scanf("%d",&n);
	FOR(i,2,n){
		int u,v,w;scanf("%d%d%d",&u,&v,&w);
		add(u,v,w);
	}
	FOR(i,1,n){
		int x,y;scanf("%d%d",&x,&y);
		a[i] = x-y;
	}
	dfs1(1);
	dfs2(1);
	printf("%d\n",ans);
	return 0;
}