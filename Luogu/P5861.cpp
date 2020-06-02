#include<bits/stdc++.h>

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

const int MAXN = 5e5 + 5;

int sm[MAXN<<5],lc[MAXN<<5],rc[MAXN<<5],root[MAXN],tot;

inline void update(int prev,int &v,int l,int r,int p,int d){
	sm[v = ++tot] = sm[prev]+d;lc[v] = lc[prev];rc[v] = rc[prev];
	if(l == r) return;
	int mid = (l + r) >> 1;
	if(p <= mid) update(lc[prev],lc[v],l,mid,p,d);
	else update(rc[prev],rc[v],mid+1,r,p,d);
}

inline int query(int x,int y,int l,int r,int L,int R){
	if(!y) return 0;
	if(l == L && r == R) return sm[y]-sm[x];
	int mid = (l + r) >> 1;
	if(R <= mid) return query(lc[x],lc[y],l,mid,L,R);
	if(L > mid) return query(rc[x],rc[y],mid+1,r,L,R);
	return query(lc[x],lc[y],l,mid,L,mid)+query(rc[x],rc[y],mid+1,r,mid+1,R);
}

inline int queryk(int x,int y,int l,int r,int k){
	if(l == r) return l;
	int mid = (l + r) >> 1;
	int rs = sm[rc[y]]-sm[rc[x]];
	if(k <= rs) return queryk(rc[x],rc[y],mid+1,r,k);
	else return queryk(lc[x],lc[y],l,mid,k-rs);
}

int n,q,a[MAXN],b[MAXN];
int m,k[MAXN];
std::map<int,int> S[MAXN];
int st[MAXN],tp;
int h[MAXN],sz[MAXN];

int main(){
	// freopen("6.in","r",stdin);
	// freopen("6.out","w",stdout);
	scanf("%d",&n);
	FOR(i,1,n){
		int l,r;scanf("%d%d",&l,&r);
		S[l][r]++;
	}
	FOR(i,1,n){
		root[i] = root[i-1];
		for(auto x:S[i]) FOR(j,1,x.se) update(root[i],root[i],1,n,x.fi,1);
	}
	// DEBUG(tot);
	scanf("%d",&q);
	FOR(xx,1,q){
		scanf("%d",&m);FOR(i,1,m) scanf("%d",k+i);
		std::sort(k+1,k+m+1);tp = 0;
		// if(xx != 156) continue;
		FOR(i,1,m){
			while(tp && h[tp] < k[i]) tp--;
			int res = sz[tp];
			res += query(root[k[st[tp]]],root[k[i]],1,n,k[i],n)-k[i];
			if(res < 0){
				puts("0");
				break;
			}
			if(i == m){
				puts("1");
				break;
			}
			int t = queryk(root[k[st[tp]]],root[k[i]],1,n,res-sz[tp]);
			while(tp && t>h[tp]){
				tp--;
				t = queryk(root[k[st[tp]]],root[k[i]],1,n,res-sz[tp]);
			}
			st[++tp] = i;sz[tp] = res;h[tp] = t;
		}
	}
	return 0;
}