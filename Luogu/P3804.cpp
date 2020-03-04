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

const int MAXN = 2e6 + 5;

int ch[MAXN][26],fail[MAXN],len[MAXN];
LL sz[MAXN];

int las = 1,tot = 1;

inline void copy(int x,int y){
	FOR(i,0,25) ch[x][i] = ch[y][i];
	fail[x] = fail[y];len[x] = len[y];
}

inline void insert(int c){
	int p = las;int np = las = ++tot;
	sz[np] = 1;
	len[np] = len[p]+1;
	while(p&&!ch[p][c]) ch[p][c] = np,p = fail[p];
	if(!p) fail[np] = 1;
	else{
		int q = ch[p][c];
		if(len[p]+1 == len[q]) fail[np] = q;
		else{
			int nq = ++tot;copy(nq,q);// split
			len[nq] = len[p]+1;
			fail[q] = fail[np] = nq;
			while(p&&ch[p][c]==q) ch[p][c] = nq,p = fail[p];
		}
	}
}

char str[MAXN];
int n;

struct Edge{
	int to,nxt;
}e[MAXN];
int head[MAXN],cnt;

inline void add(int u,int v){
	e[++cnt] = (Edge){v,head[u]};head[u] = cnt;
}

// std::vector<int> G[MAXN];

inline void dfs(int v){
	for(int i = head[v];i;i = e[i].nxt){
		dfs(e[i].to);
		sz[v] += sz[e[i].to];
	}
}

int main(){
	scanf("%s",str+1);n = strlen(str+1);
	FOR(i,1,n) insert(str[i]-'a');
	FOR(i,2,tot) add(fail[i],i);
	dfs(1);
	LL ans = 0;
	FOR(i,1,tot) if(sz[i] > 1) ans = std::max(ans,sz[i]*len[i]);
	// DEBUG(sz[1981]);DEBUG(len[1981]);
	printf("%lld\n",ans);
	return 0;
}