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

const int MAXN = 2e5 + 5;
int A[MAXN],B[MAXN],C[MAXN];
int a[MAXN],b[MAXN],t[MAXN],c[MAXN],n;
int now,sm[MAXN];
std::vector<int> dec[MAXN];
int mu[MAXN];
int q[MAXN];

inline void work(int l,int r,int L,int R){
	if(l > r) return;
	if(L == R){
		FOR(i,l,r) c[q[i]] = L;
		return;
	}
	int mid = (L + R) >> 1;
	while(now > mid){
		int x = b[now--];
		for(auto t:dec[x]) --sm[t];
	}
	while(now < mid){
		int x = b[now++];
		for(auto t:dec[x]) ++sm[t];
	}
	std::vector<int> toL,toR;
	FOR(i,l,r){
		int res = 0;
		for(auto x:dec[q[i]]) res += mu[x]*sm[x];
		if(res > 0) toR.pb(q[i]);
		else toL.pb(q[i]);
	}
	int tot = l-1,sz = toL.size();
	for(auto x:toL) q[++tot] = x;
	for(auto x:toR) q[++tot] = x;
	toL.clear();toR.clear();
	work(l,l+sz-1,L,mid);work(l+sz,r,mid+1,R);
}

inline int tosolve(int n){
	std::vector<int> S;
	FOR(i,1,n) S.pb(t[i] = b[i]);
	std::sort(all(S));S.erase(std::unique(all(S)),S.end());
	FOR(i,1,n) q[i] = i,b[i] = std::lower_bound(all(S),b[i])-S.begin()+1;
	work(1,n,1,S.size());int ans = -1e9;
	FOR(i,1,n) ans = std::max(ans,a[i]+t[c[i]]);
	return ans;
}

inline void solve(){
	FOR(i,1,n){
		for(int j = 1;j*i <= n;j++){
			a[j] = A[j*i];b[j] = B[j*i];
		}
		C[i] = std::max(C[i],tosolve(n/i));
	}
}

int main(){
	scanf("%d",&n);
	FOR(i,1,n) scanf("%d",A+i);
	FOR(i,1,n) scanf("%d",B+i),B[i] = -B[i];
	solve();
	FOR(i,1,n) A[i] = -A[i],B[i] = -B[i];
	solve();
	FOR(i,1,n) printf("%d ",C[i]);puts("");
	return 0;
}
