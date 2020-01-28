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

const int MAXN = 50000+5;
const int MAXM = 4e6 + 5;

int f[MAXM],ch[MAXM][2],cnt[MAXM],val[MAXM],sz[MAXM],tot;
int root[MAXN<<2];
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
		if((z = f[y]) != v){
			rotate((ch[z][1]==y)^(ch[y][1]==x) ? x : y);
		}
		rotate(x);
	}
	if(!v) root[rt] = x;
}

inline void insert(int rt,int v){
	int x = root[rt];
	if(!x){
		x = ++tot;
		val[x] = v;sz[x] = cnt[x] = 1;
		root[rt] = x;
		return;
	}
	int pre = 0;
	while(233){
		if(val[x] == v){
			cnt[x]++;pushup(pre);
			break;
		}
		pre = x;
		x = ch[x][val[x]<v];
		if(!x){
			x = ++tot;cnt[x] = sz[x] = 1;val[x] = v;
			ch[pre][val[pre]<v] = x;f[x] = pre;
			pushup(pre);break;
		}
	}
	splay(rt,x,0);
}

inline int getk(int rt,int v){ // 找到数 v
	int x = root[rt];
	while(233){
		if(!x) return -1;// not found
		if(val[x] == v){
			splay(rt,x,0);
			return x;
		}
		x = ch[x][val[x]<v];
	}
}

inline int pre(int x){
	x = ch[x][0];
	while(rc) x = rc;
	return x;
}

inline void dell(int rt,int v){
	int x = getk(rt,v);
	if(cnt[x] > 1){
		cnt[x]--;pushup(x);
		return;
	}
	if(!lc && !rc){
		root[rt] = 0;
		return;
	}
	if(!lc){
		int t = ch[x][1];root[rt] = t;f[t] = 0;
		return;
	}
	if(!rc){
		int t = ch[x][0];root[rt] = t;f[t] = 0;
		return;
	}
	int t = pre(x);splay(rt,t,x);
	ch[t][1] = ch[x][1];f[ch[x][1]] = t;f[t] = 0;
	pushup(t);root[rt] = t;
}

inline int getpre(int rt,int v){
	int x = root[rt],res = INT_MIN+1;
	while(233){
		if(!x) return res;
		if(val[x] < v){
			res = std::max(res,val[x]);
			x = rc;
		}
		else x = lc;
	}
}

inline int getsuf(int rt,int v){
	int x = root[rt],res = INT_MAX;
	while(233){
		if(!x) return res;
		if(val[x] > v){
			res = std::min(res,val[x]);
			x = lc;
		}
		else x = rc;
	}
}

inline int getrank(int rt,int v){
	int x = root[rt],res = 0;
	while(233){
		if(!x) return res;
		if(val[x] == v) return res+sz[lc];
		if(val[x] < v){
			res += sz[lc]+cnt[x];
			x = rc;
		}
		else x = lc;
	}
}

int a[MAXN],n,m,N;

inline void ins(int p,int d){
	for(p += N;p;p >>= 1) insert(p,d);
}

inline void del(int p,int d){
	for(p += N;p;p >>= 1) dell(p,d);
}

std::vector<int> S;

inline void modify(int l,int r){
	S.clear();
	for(l += N-1,r += N+1;l^r^1;l >>= 1,r >>= 1){
		if(!(l&1)) S.pb(l^1);
		if(r&1) S.pb(r^1);
	}
}

int main(){
	// DEBUG(1);
	scanf("%d%d",&n,&m);N = 1;
	FOR(i,1,n) scanf("%d",a+i);
	while(N <= n) N <<= 1;
	FOR(i,1,n) ins(i,a[i]);
	FOR(i,1,m){
		int opt;scanf("%d",&opt);
		if(opt == 1){
			int l,r,k;scanf("%d%d%d",&l,&r,&k);
			modify(l,r);int res = 0;
			for(auto x:S) res += getrank(x,k);
			printf("%d\n",res+1);
		}
		if(opt == 2){
			int l,r,k;scanf("%d%d%d",&l,&r,&k);
			modify(l,r);
			int L = 0,R = 1e8+1,ans = -1;
			while(L <= R){
				int mid = (L + R) >> 1;
				int t = 0;
				for(auto x:S) t += getrank(x,mid);
				if(t < k) L = mid+1;
				else ans = mid,R = mid-1;
			}
			printf("%d\n",ans-1);
		}
		if(opt == 3){
			int p,d;scanf("%d%d",&p,&d);
			del(p,a[p]);a[p] = d;ins(p,a[p]);
		}
		if(opt == 4){
			int l,r,k;scanf("%d%d%d",&l,&r,&k);
			modify(l,r);int res = INT_MIN+1;
			for(auto x:S) res = std::max(res,getpre(x,k));
			printf("%d\n",res);
		}
		if(opt == 5){
			int l,r,k;scanf("%d%d%d",&l,&r,&k);
			modify(l,r);int res = INT_MAX;
			for(auto x:S) res = std::min(res,getsuf(x,k));
			printf("%d\n",res);
		}
	}
	return 0;
}