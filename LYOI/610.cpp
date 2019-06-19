#include <algorithm>
#include <iostream>
#include <cstring>
#include <climits>
#include <cstdio>
#include <vector>
#include <cstdlib>
#include <ctime>
#include <cmath>
#include <queue>
#include <stack>
#include <map>
#include <set>
 
#define fi first
#define lc (x<<1)
#define se second
#define U unsigned
#define rc (x<<1|1)
#define Re register
#define LL long long
#define MP std::make_pair
#define CLR(i,a) memset(i,a,sizeof(i))
#define FOR(i,a,b) for(Re int i = a;i <= b;++i)
#define ROF(i,a,b) for(Re int i = a;i >= b;--i)
#define SFOR(i,a,b,c) for(Re int i = a;i <= b;i+=c)
#define SROF(i,a,b,c) for(Re int i = a;i >= b;i-=c)
#define DEBUG(x) std::cerr << #x << '=' << x << std::endl
#define int LL
const int ha = 998244353;

inline int qpow(int a,int n=ha-2){
	int res = 1;
	while(n){
		if(n & 1) res = 1ll*res*a%ha;
		a = 1ll*a*a%ha;
		n >>= 1;
	}
	return res;
}
const int MAXN = 200000+5;
struct Node{
	int mul,ans;
	
	Node operator + (const Node &t) const {
		Node ans;
		ans.mul = 1ll*mul*t.mul%ha;
		ans.ans = (this->ans + mul*t.ans%ha)%ha;
		return ans;
	}
}s[MAXN<<2];
int val[MAXN];

inline void pushup(int x){
	s[x] = s[lc] + s[rc];
}

inline void build(int x,int l,int r){
	if(l == r){
		s[x] = (Node){val[l],val[l]};
		return;
	}
	int mid = (l + r) >> 1;
	build(lc,l,mid);build(rc,mid+1,r);
	pushup(x);
}

inline void update(int x,int l,int r,int pos,int val){
	if(l == r){
		s[x] = (Node){val,val};
		return;
	}
	int mid = (l + r) >> 1;
	if(pos <= mid) update(lc,l,mid,pos,val);
	else update(rc,mid+1,r,pos,val);
	pushup(x);
}

inline Node query(int x,int l,int r,int L,int R){
	if(l == L && r == R) return s[x];
	int mid = (l + r) >> 1;
	if(R <= mid) return query(lc,l,mid,L,R);
	if(L > mid) return query(rc,mid+1,r,L,R);
	return query(lc,l,mid,L,mid)+query(rc,mid+1,r,mid+1,R);
}

int n,q;

signed main(){
	scanf("%lld%lld",&n,&q);
	FOR(i,1,n){
		int x,y;scanf("%lld%lld",&x,&y);
        int t = 1ll*x*qpow(y)%ha;
		val[i] = (1-t+ha)*qpow(t)%ha;
	}
	build(1,1,n);
	while(q--){
		int opt;scanf("%lld",&opt);
		if(opt & 1){
			int d,x,y;scanf("%lld%lld%lld",&d,&x,&y);
			int v = 1ll*x*qpow(y)%ha;update(1,1,n,d,1ll*(1-v+ha)%ha*qpow(v)%ha);
		}
		else{
			int l,r;scanf("%lld%lld",&l,&r);
            int t = query(1,1,n,l,r).ans;
			printf("%lld\n",qpow(t+1));
		}
	}
	return 0;
}
/*
3 7 
1 3 
1 2 
2 3
2 1 1 
2 1 2 
2 1 3 
1 2 2 3 
2 1 1 
2 1 2 
2 1 3
*/