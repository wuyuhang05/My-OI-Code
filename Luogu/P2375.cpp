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

const int MAXN = 1e6 + 5;
const int ha = 1e9 + 7;

char str[MAXN];
int n,nxt[MAXN];

struct Edge{
	int to,nxt;
}e[MAXN];
int head[MAXN],cnt;

inline void add(int u,int v){
	e[++cnt] = (Edge){v,head[u]};head[u] = cnt;
}

int st[MAXN],tp,ans;

const int MAXM = 5e5 + 5;

struct BIT{
	#define lowbit(x) ((x)&(-(x)))
	int tree[MAXM];

	inline void add(int pos,int x){
		while(pos < MAXM){
			tree[pos] += x;
			pos += lowbit(pos);
		}
	}

	inline int query(int pos){
		if(!pos) return 0;
		int res = 0;
		while(pos){
			res += tree[pos];
			pos -= lowbit(pos);
		}
		return res;
	}
}bit;

inline void dfs(int v){
	ans = 1ll*ans*(bit.query(v/2)+1)%ha;
	if(v <= n/2) bit.add(v,1);
	for(int i = head[v];i;i = e[i].nxt) dfs(e[i].to);
	if(v <= n/2) bit.add(v,-1);
}

inline void Solve(){
	scanf("%s",str+1);n = strlen(str+1);cnt = 0;
	FOR(i,1,n+1) head[i] = 0;
	ans = 1;
	int rt = n+1;
	FOR(i,2,n){
		int j = nxt[i-1];
		while(j&&str[j+1]!=str[i]) j = nxt[j];
		if(str[j+1]==str[i]) j++;
		nxt[i] = j;
	}
	FOR(i,1,n) add(nxt[i]?nxt[i]:rt,i);
	dfs(rt);
	printf("%d\n",ans);
}

int main(){
//	freopen("P2375_2.in","r",stdin);
	int T;scanf("%d",&T);
	while(T--) Solve();
	return 0;
}