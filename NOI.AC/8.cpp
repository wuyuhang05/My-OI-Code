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

const int MAXN = 2e5 + 5;
const double EPS = 1e-6;
int n,k;
P o[MAXN];//<p,v>
double a[MAXN];
double stk[MAXN];
int tp;

inline bool chk(double mid){
	FOR(i,1,n) a[i] = 1.0*o[i].se*mid+o[i].fi,stk[i] = 0;
	stk[tp = 1] = a[1];
	FOR(i,2,n){
		int p = std::upper_bound(stk+1,stk+tp+1,a[i])-stk;
		if(p == tp+1) ++tp;
		stk[p] = a[i];
	}
	return n-tp <= k;
}

int main(){
	// DEBUG(1);
	scanf("%d%d",&n,&k);
	FOR(i,1,n) scanf("%d%d",&o[i].fi,&o[i].se);
	std::sort(o+1,o+n+1);
	double l = 0,r = 2e9,ans = -1;
	int ts = 100;
	while(ts--){
		double mid = (l+r)/2.0;
		if(chk(mid)) ans = mid,l = mid;
		else r = mid;
	}
	if(std::fabs(ans-2e9) <= EPS){
		puts("Forever");return 0;
	}
	if(ans == -1){
		puts("-1");return 0;
	}
	printf("%.10f\n",ans);
	return 0;
}