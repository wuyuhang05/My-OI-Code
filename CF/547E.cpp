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

const int MAXN = 5e5 + 5;

char str[MAXN];
int n;

int sa[MAXN],tax[MAXN],pool1[MAXN],pool2[MAXN],M;
int *tp=pool1,*rk=pool2;

inline void sort(){
	FOR(i,0,M) tax[i] = 0;
	FOR(i,1,n) tax[rk[i]]++;
	FOR(i,1,M) tax[i] += tax[i-1];
	ROF(i,n,1) sa[tax[rk[tp[i]]]--] = tp[i];
}

inline void build(){
	M = 0;
	FOR(i,1,n) rk[i] = str[i],tp[i] = i,M = std::max(M,rk[i]+1);
	sort();
	for(int w = 1,p = 0;p < n;w <<= 1,M = p){
		p = 0;
		FOR(i,1,w) tp[++p] = n-w+i;
		FOR(i,1,n) if(sa[i] > w) tp[++p] = sa[i]-w;
		sort();
		std::swap(rk,tp);
		rk[sa[1]] = p = 1;
		FOR(i,2,n) rk[sa[i]] = (tp[sa[i-1]] == tp[sa[i]] && tp[sa[i-1]+w] == tp[sa[i]+w]) ? p : ++p;
	}	
}
int hei[MAXN];
inline void getheight(){
	int k = 0;
	FOR(i,1,n){ // hei[i] = lcp(sa[i],sa[i-1])
		// hei[rk[i]] >= hei[rk[i-1]]-1
		if(k) k--;
		int j = sa[rk[i]-1];
		while(str[i+k] == str[j+k]) ++k;
		hei[rk[i]] = k;
	}
}

const int MAXM = 19;
int mn[MAXM+1][MAXN];
int Log[MAXN];

inline void build2(){
	FOR(i,1,n) mn[0][i] = hei[i];
	FOR(i,1,Log[n]){
		for(int j = 1;j+(1<<(i-1)) < MAXN;++j){
			mn[i][j] = std::min(mn[i-1][j],mn[i-1][j+(1<<(i-1))]);
		}
	}
}

inline int calc(int l,int r){
	int c = Log[r-l+1];
	return std::min(mn[c][l],mn[c][r-(1<<c)+1]);
}
char tmp[MAXN];
int id[MAXN],dd[MAXN],ep[MAXN],len[MAXN];
int root[MAXN];
int sm[MAXN<<5],tot,lc[MAXN<<5],rc[MAXN<<5];

inline void insert(int prev,int &v,int l,int r,int p,int d){
	v = ++tot;sm[v] = sm[prev]+d;lc[v] = lc[prev];rc[v] = rc[prev];
	if(l == r) return;
	int mid = (l + r) >> 1;
	if(p <= mid) insert(lc[prev],lc[v],l,mid,p,d);
	else insert(rc[prev],rc[v],mid+1,r,p,d);
}

inline int query(int x,int y,int l,int r,int L,int R){
	if(l == L && r == R) return sm[y]-sm[x];
	int mid = (l + r) >> 1;
	if(R <= mid) return query(lc[x],lc[y],l,mid,L,R);
	if(L > mid) return query(rc[x],rc[y],mid+1,r,L,R);
	return query(lc[x],lc[y],l,mid,L,mid)+query(rc[x],rc[y],mid+1,r,mid+1,R);
}

int main(){
	n = 0;
	Log[0] = -1;
	FOR(i,1,MAXN-1) Log[i] = Log[i>>1]+1;
	int m,q;scanf("%d%d",&m,&q);
	FOR(i,1,m){
		if(i != 1) str[++n] = '$';
		scanf("%s",tmp+1);
		int l = strlen(tmp+1);
		FOR(j,1,l) str[++n] = tmp[j],dd[n] = i;
		ep[i] = n;len[i] = l;
	}
	build();
	getheight();build2();
	// DEBUG(calc(6,11));
	// FOR(i,1,n) DEBUG(hei[i]);DEBUG(n);
	FOR(i,1,n) id[rk[i]] = dd[i];
	FOR(i,1,n) insert(root[i-1],root[i],1,n,id[i],1);
	// DEBUG(id[9]);
	// FOR(i,1,n) DEBUG(sa[i]);
	// DEBUG(sa[9]);
	while(q--){
		int l,r,k;scanf("%d%d%d",&l,&r,&k);
		// 求 l <= id <= r , L <= rk <= R 的 id 种类
		// 先搞出 id[i] 表示 rk 为 i 的 id
		// 然后搞出 L R
		int kk = k==1?1:ep[k-1]+2;
		kk = rk[kk];int L = kk,R = kk;
		int ll = 1,rr = kk-1;
		while(ll <= rr){
			int mid = (ll+rr)>>1;
			if(calc(mid+1,kk) >= len[k]) L = mid,rr = mid-1;
			else ll = mid+1;
		}
		ll = kk+1,rr = n;
		while(ll <= rr){
			int mid = (ll+rr)>>1;
			// DEBUG(ll);DEBUG(rr);
			if(calc(kk+1,mid) >= len[k]) R = mid,ll = mid+1;
			else rr = mid-1;
		}
		// DEBUG(L);DEBUG(R);
		printf("%d\n",query(root[L-1],root[R],1,n,l,r));
	}
	return 0;
}