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
int n,A[MAXN],B[MAXN],C[MAXN];
int a[MAXN],b[MAXN],c[MAXN];
int q[MAXN],tr[MAXN];
int now,sm[MAXN];
std::vector<int> dec[MAXN];
bool p[MAXN];
int prime[MAXN],mu[MAXN],cnt;

inline void prework(){
	mu[1] = 1;
	FOR(i,2,MAXN-1){
		if(!p[i]) prime[++cnt] = i,mu[i] = -1;
		for(int j = 1;j <= cnt && i*prime[j] < MAXN;++j){
			p[i*prime[j]] = 1;mu[i*prime[j]] = -mu[i];
			if(!(i%prime[j])) {mu[i*prime[j]] = 0;break;}
		}
	}
	FOR(i,1,MAXN-1) for(int j = i;j < MAXN;j += i) dec[j].pb(i);
}

inline void work(int l,int r,int L,int R){
	if(l > r) return;
	if(L == R){
		FOR(i,l,r) c[q[i]] = L;
		return;
	}
	int mid = (L+R)>>1;
	while(now > mid){
		int x = tr[now--];
		for(auto i:dec[x]) ++sm[i];
	}
	while(now < mid){
		int x = tr[++now];
		for(auto i:dec[x]) --sm[i];
	}
	std::vector<int> toL,toR;
	FOR(i,l,r){
		int t = 0;
		for(auto d:dec[q[i]]) t += mu[d]*sm[d];
		if(t > 0) toR.pb(q[i]);
		else toL.pb(q[i]);
	}
	int tp = l-1,sz = toL.size();
	for(auto x:toL) q[++tp] = x;
	for(auto x:toR) q[++tp] = x;
	toL.clear();toR.clear();
	work(l,l+sz-1,L,mid);work(l+sz,r,mid+1,R);
}

inline int solve(int n){
	std::vector<int> S;now = n;
	FOR(i,1,n) S.pb(b[i]);std::iota(q+1,q+n+1,1);
	std::fill(sm+1,sm+n+1,0);std::sort(all(S));
	FOR(i,1,n){
		int x = std::upper_bound(all(S),b[i])-S.begin();
		tr[x] = i;
		S[x-1]++;
	}
	work(1,n,1,n);int ans = -1e9;
	FOR(i,1,n) ans = std::max(ans,a[i]+S[c[i]-1]-1);
	return ans;
}

inline void Solve(){
	FOR(i,1,n){
		for(int j = 1;j*i <= n;++j){
			a[j] = A[i*j];
			b[j] = B[i*j];
		}
		C[i] = std::max(C[i],solve(n/i));
//		exit(0);
	}
}

int main(){
	scanf("%d",&n);prework();
	FOR(i,1,n) scanf("%d",A+i);
	FOR(i,1,n) scanf("%d",B+i),B[i] = -B[i];
	Solve();
	FOR(i,1,n) A[i] = -A[i],B[i] = -B[i];
	Solve();
	FOR(i,1,n) printf("%d ",C[i]);
	return 0;
}