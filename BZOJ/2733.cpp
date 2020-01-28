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

const int MAXN = 3e5 + 5;

int f[MAXN],ch[MAXN][2],sz[MAXN],cnt[MAXN],val[MAXN],root[MAXN];
#define lc (ch[x][0])
#define rc (ch[x][1])

inline void pushup(int x){
	sz[x] = sz[lc]+sz[rc]+cnt[x];
}

inline void rotate(int x){
	int y = f[x],z = f[y],k = ch[y][1]==x,w = ch[x][!k];
	if(z) ch[z][ch[z][1]==y] = x;f[x] = z;
	ch[x][!k] = y;f[y] = x;
	ch[y][k] = w;if(w) f[w] = y;
	pushup(y);pushup(x);
}

inline void splay(int rt,int x,int v){
	int y,z;
	while((y = f[x]) != v){
		if((z = f[y]) != v) rotate((ch[z][1]==y)^(ch[y][1]==x) ? x : y);
		rotate(x);
	}
	if(!v) root[rt] = x;
}

inline void insert(int rt,int v){ // 向树 rt 插入节点 v
	int x = root[rt];
	if(!x){
		root[rt] = v;return;
	}
	int pre = 0;
	while(233){
		if(val[x] == val[v]){
			cnt[x] += cnt[v];
			pushup(pre);
			break;
		}pre = x;
		x = ch[x][val[x]<val[v]];
		if(!x){
			x = v;
			ch[pre][val[pre]<val[x]] = x;
			f[x] = pre;pushup(pre);
			break;
		}
	}
	splay(rt,x,0);
}

inline int kth(int rt,int k){
	int x = root[rt];
	while(233){
		if(k <= sz[lc]) x = lc;
		else if(k == sz[lc]+cnt[x]){
			splay(rt,x,0);
			return x;
		}
		else k -= sz[lc]+cnt[x],x = rc;
	}
}

int F[MAXN],SZ[MAXN];

inline int find(int x){
	return x == F[x] ? x : F[x] = find(F[x]);
}

inline void merge(int x,int y){
	int fx = find(x),fy = find(y);
	if(fx == fy) return;
	if(SZ[fx] < SZ[fy]) std::swap(x,y),std::swap(fx,fy);
	F[fy] = fx;SZ[fx] += SZ[fy];
	std::queue<int> q;q.push(root[fy]);
	while(!q.empty()){
		int v = q.front();q.pop();
		if(ch[v][0]) q.push(ch[v][0]);
		if(ch[v][1]) q.push(ch[v][1]);
		ch[v][0] = ch[v][1] = f[v] = 0;sz[v] = cnt[v];
		insert(fx,v);
	}
}

int n,m,q;

int main(){
	scanf("%d%d",&n,&m);
	FOR(i,1,n){
		scanf("%d",val+i);
		sz[i] = cnt[i] = SZ[i] = 1;F[i] = i;root[i] = i;
	}
	FOR(i,1,m){
		int u,v;scanf("%d%d",&u,&v);
		merge(u,v);
	}
	// DEBUG(sz[root[find(1)]]);
	scanf("%d",&q);
	FOR(i,1,q){
		char str[23];scanf("%s",str);
		if(str[0] == 'Q'){
			int x,k;scanf("%d%d",&x,&k);
			x = find(x);
			if(SZ[x] < k) puts("-1");
			else printf("%d\n",kth(x,k));
		}
		if(str[0] == 'B'){
			int x,y;scanf("%d%d",&x,&y);
			merge(x,y);
		}
	}
	return 0;
}