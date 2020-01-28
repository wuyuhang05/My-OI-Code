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

const int MAXN = 2e5 + 5;
int n,m;
int l[MAXN],r[MAXN],t[MAXN];
P a[MAXN];

int sm[MAXN<<5],root[MAXN],lc[MAXN<<5],rc[MAXN<<5],tot;

inline void update(int prev,int &v,int l,int r,int ps){
	v = ++tot;
	sm[v] = sm[prev]+1;lc[v] = lc[prev];rc[v] = rc[prev];
	if(l == r) return;
	int mid = (l + r) >> 1;
	if(ps <= mid) update(lc[prev],lc[v],l,mid,ps);
	else update(rc[prev],rc[v],mid+1,r,ps);
}

inline int query(int x,int y,int l,int r,int k){
	if(l == r) return l;
	int mid = (l + r) >> 1,ls = sm[lc[y]]-sm[lc[x]];
	if(ls >= k) return query(lc[x],lc[y],l,mid,k);
	else return query(rc[x],rc[y],mid+1,r,k-ls);
}

int ans[MAXN],N,ps[MAXN];
int pre[MAXN];

int main(){
	// freopen("shooting1.in","r",stdin);
	// freopen("a.out","w",stdout);
	read(n);read(m);
	FOR(i,1,n) read(l[i]),read(r[i]),read(t[i]),N = std::max(N,r[i]);
	FOR(i,1,m) read(a[i].fi),a[i].se = i,pre[a[i].fi]++,N = std::max(N,a[i].fi);
	FOR(i,1,N) pre[i] += pre[i-1];
	std::sort(a+1,a+m+1);
	FOR(i,1,m) update(root[i-1],root[i],1,m,a[i].se),ps[i] = a[i].fi;
	FOR(i,1,n){
		if(pre[r[i]]-pre[l[i]-1] < t[i]) continue;
		// DEBUG(i);
		int L = std::lower_bound(ps+1,ps+m+1,l[i])-ps,R = std::upper_bound(ps+1,ps+m+1,r[i])-ps-1;
		ans[query(root[L-1],root[R],1,m,t[i])]++;
	}
	FOR(i,1,m) printf("%d\n",ans[i]);
	return 0;
}