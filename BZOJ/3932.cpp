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

const int MAXN = 200000+5;
const int MAXM = 2e6 + 5;

#define lc ((x)<<1)
#define rc ((x)<<1|1)

int f[MAXM],ch[MAXM][2],sm[MAXM],sz[MAXM],val[MAXM],cnt[MAXM];
int root[MAXN<<2],tot;

inline void pushup(int x){
	sm[x] = sm[lc]+sm[rc]+val[x]*cnt[x];
	sz[x] = sz[lc]+sz[rc]+cnt[x];
}

inline void rotate(int x){
	int y = f[x],z = f[y],k = ch[y][1]==x,w = ch[x][!k];
	if(z) ch[z][ch[z][1]==y] = x;f[z] = x;
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

inline void insert(int rt,int v){
	int x = root[rt];
	if(!x){
		x = ++tot;sm[x] = val[x] = v;cnt[x] = sz[x] = 1;
		root[rt] = x;return;
	}
	int pre = 0;
	while(233){
		if(val[x] == v){
			cnt[x]++;
			pushup(pre);
			break;
		}
		pre = x;x = ch[x][val[x]<v];
		if(!x){
			x = ++tot;
			sm[x] = val[x] = v;cnt[x] = sz[x] = 1;
			f[x] = pre;ch[pre][val[pre]<v] = x;
			pushup(pre);break;
		}
	}
	splay(rt,x,0);
}

inline int getk(int rt,int k){
	int x = root[rt];
	while(233){
		if(sz[x] <= sz[lc]) x = lc;
		else if(sz[x] <= sz[lc]+cnt[x]){
			splay(rt,x,0);
			return x;
		}
		else k -= sz[lc]+cnt[x],x = rc;
	}
}

int N;
inline void insert(int p,int x){
	for(p += N;p;p >>= 1) insert(p,x);
}

std::vector<int> S;

inline void modify(int l,int r){
	for(l += N-1,r += N+1;l^r^1;l >>= 1,r >>= 1){
		if(!(l&1)) S.pb(l^1);
		if(r&1) S.pb(r^1);
	}
}
#undef lc
#undef rc
int sm[MAXN<<5],lc[MAXN<<5],rc[MAXN<<5];

int main(){
	return 0;
}