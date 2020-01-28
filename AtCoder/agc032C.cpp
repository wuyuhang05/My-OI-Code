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
	int to,w,nxt;
}e[MAXN<<1];
int du[MAXN],cnt,head[MAXN];

inline void add(int u,int v,int w){
	e[++cnt] = (Edge){v,w,head[u]};head[u] = cnt;
	e[++cnt] = (Edge){u,w,head[v]};head[v] = cnt;
	du[u]++;du[v]++;
}

int n,m;
bool vis[MAXN],used[MAXN<<1];
bool flag = false;
std::vector<int> tt;

inline void dfs(int v){
	vis[v] = 1;
	// DEBUG(v);
	if(flag) return;
	for(int i = head[v];i;i = e[i].nxt){
		if(used[e[i].w]) continue;
		used[e[i].w] = 1;
		if(e[i].to == tt[0]){
			flag = true;
			break;
		}
		if(!vis[e[i].to]) dfs(e[i].to);
	}
	if(flag) return;
}

inline bool pd(){
	FOR(i,1,n) if(du[i] == 4) tt.pb(i);
	vis[tt[1]] = true;
	dfs(tt[0]);
	return flag;
}

int main(){
	scanf("%d%d",&n,&m);
	FOR(i,1,m){
		int u,v;scanf("%d%d",&u,&v);
		add(u,v,i);
	}
	int mx = 0,cntt = 0;
	FOR(i,1,n){
		if(du[i]&1){
			puts("No");
			return 0;
		}
		mx = std::max(mx,du[i]);
		if(du[i] == 4) cntt++;
	}
	if(mx >= 6){
		puts("Yes");
		return 0;
	}
	if(mx == 4 && cntt >= 3){
		puts("Yes");
		return 0;
	}
	if(mx == 4 && cntt == 2){
		puts(pd() ? "Yes" : "No");
		return 0;
	}
	puts("No");
	return 0;
}