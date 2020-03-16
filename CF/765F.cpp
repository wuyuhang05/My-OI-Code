#pragma GCC optimize("Ofast")
/*
* Author: RainAir
* File Name: D.cpp
* Date: 2020-02-23 19:01:14
* Last Modified time: 2020-02-29 16:13:27
*/
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
#define FOR(i,a,b) for(int i = a;i <= b;++i)
#define ROF(i,a,b) for(int i = a;i >= b;--i)
#define DEBUG(x) std::cerr << #x << '=' << x << std::endl

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

const int MAXN = 1e5 + 5;
const int MAXM = 3e5 + 5;
LL a[MAXN],ans[MAXM];
int n,m;
std::vector<P> q[MAXN]; // <l,id>
std::set<LL> S[MAXN<<2];
#define lc ((x)<<1)
#define rc ((x)<<1|1)

inline void update(int x,int l,int r,int p,LL d){
	S[x].insert(d);
	if(l == r) return;
	int mid = (l + r) >> 1;
	if(p <= mid) update(lc,l,mid,p,d);
	else update(rc,mid+1,r,p,d);
}

inline int query(int x,int l,int r,int L,int R,LL _LL,LL RR){
	auto p = S[x].lower_bound(_LL);
	if(p == S[x].end()) return -1;
	if(*p > RR) return -1;
	if(l == r) return l;
	int mid = (l + r) >> 1;
	if(R <= mid) return query(lc,l,mid,L,R,_LL,RR);
	if(L > mid) return query(rc,mid+1,r,L,R,_LL,RR);
	int t = query(rc,mid+1,r,mid+1,R,_LL,RR);
	if(t != -1) return t;
	return query(lc,l,mid,L,mid,_LL,RR);
}

inline void build(int x,int l,int r){
	S[x].clear();
	FOR(i,l,r) S[x].insert(a[i]);
	if(l == r) return;
	int mid = (l + r) >> 1;
	build(lc,l,mid);build(rc,mid+1,r);
}

struct BIT{
	#define lb(x) ((x)&(-(x)))
	LL tree[MAXN];

	inline void add(int p,LL x){
		for(;p;p-=lb(p)) tree[p] = std::min(tree[p],x);
	}

	inline LL qry(int p){
		LL res = 1e18;
		for(;p<MAXN;p+=lb(p)) res = std::min(res,tree[p]);
		return res;
	}

	inline void clr(){
		FOR(i,0,MAXN-1) tree[i] = 1e18;
	}
}bit;

int st[MAXN],tp;
inline void work(){
	bit.clr();build(1,1,n);
	a[0] = 1e18;tp = 0;
	FOR(i,1,n){
		while(tp && a[st[tp]] < a[i]) --tp;
		int p = st[tp];
		while(p){
			bit.add(p,a[p]-a[i]);
			if(a[i] == a[p]) break;
			if(p == 1) break;
			int t = query(1,1,n,1,p-1,a[i],(a[p]+a[i])/2);
			if(t == -1) break;
			p = t;
		}
		st[++tp] = i;
		for(auto x:q[i]) ans[x.se] = std::min(bit.qry(x.fi),ans[x.se]);
	}
}

int main(){
	scanf("%d",&n);
	FOR(i,1,n) scanf("%lld",a+i);
	LL mx = 0;FOR(i,1,n) mx = std::min(mx,a[i]);
	mx = -mx;FOR(i,1,n) a[i] += mx;mx = 0;
	scanf("%d",&m);
	FOR(i,1,n) mx = std::max(mx,a[i]);mx++;
	FOR(i,1,m){
		int l,r;scanf("%d%d",&l,&r);
		q[r].pb(MP(l,i));
	}
	FOR(i,1,m) ans[i] = 1e18;
	work();
	FOR(i,1,n) a[i] = -a[i];
	work();
	FOR(i,1,m) printf("%lld\n",ans[i]);
	return 0;
}
