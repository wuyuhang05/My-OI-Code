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
#define int LL
const int MAXN = 3000+5;
int a[MAXN],b[MAXN],n,ct[6];
std::vector<int> G[MAXN];

namespace Subtask1{// 全都互不相同
	int f[6],cnt[MAXN];
	inline int Solve(){
		FOR(i,1,n) cnt[a[i]]++;f[0] = 1;
		FOR(i,1,n){
			if(!cnt[i]) continue;
			ROF(j,4,0) f[j+1] += f[j]*cnt[i];
		}
		return f[5];
	}
}
#define DEB (1+1==2)
namespace Subtask2{ // 两个出现次数>=2的
	int f[MAXN][6];
	int ps[MAXN],tot;
	inline int Solve(){
		int x=-1,y=-1,ext = -1;
		FOR(i,1,5) ct[i] = 0;FOR(i,1,5) ct[b[i]]++;
		FOR(i,1,5) if(ct[i] >= 2) x==-1 ? x=i : y=i;
		FOR(i,1,5) if(b[i] != x && b[i] != y) ext = i;
		// FOR(i,1,5) printf("%d ",b[i]);puts("");
		// DEBUG(x);DEBUG(y);DEBUG(ext);
		int ans = 0;
		FOR(i,1,n){ // x <=> i
			if(G[i].empty()) continue;
			FOR(j,1,n){ //y <=> j
				if(G[j].empty()) continue;
				if(i == j) continue;
				tot = 0;
				int t1 = 0,t2 = 0;
				while(t1 < G[i].size() && t2 < G[j].size()){
					ps[++tot] = G[i][t1] < G[j][t2] ? G[i][t1++] : G[j][t2++];
				}
				while(t1 < G[i].size()) ps[++tot] = G[i][t1++];
				while(t2 < G[j].size()) ps[++tot] = G[j][t2++];
				// FOR(i,1,tot) FOR(j,0,5) f[i][j] = 0;
				f[0][0] = 1;
				FOR(k,1,tot){
					FOR(l,0,5) f[k][l] = f[k-1][l];
					if(ext != -1) f[k][ext] += f[k-1][ext-1]*(ps[k]-ps[k-1]-1);
					int t[6] = {0};FOR(l,0,5) t[l] = f[k][l];
					if(a[ps[k]] == i){
						FOR(l,1,5) if(b[l] == x) f[k][l] += t[l-1];
					}
					if(a[ps[k]] == j){
						FOR(l,1,5) if(b[l] == y) f[k][l] += t[l-1];
					}
				}
				// DEBUG(f[tot][5]);
				if(ext == 5) f[tot][5] += f[tot][4]*(n-ps[tot]);
				// if(DEB) DEBUG(i),DEBUG(j);
				// if(DEB) FOR(i,1,tot) printf("%d\n",ps[i]);puts("");
				ans += f[tot][5];
			}
		}
		// exit(0);
		// DEBUG(ans);
		return ans;
	}
}

namespace Subtask3{
	int mor = 0;
	int f[MAXN][6];
	inline int Solve(){
		FOR(i,1,5) if(ct[i] >= 2) mor = i;
		int t = 5-ct[mor];
		int ans = 0;
		FOR(S,0,(1<<t)-1){
			int res = 0,t = __builtin_popcount(S);
			if(t == 1) continue;
			if(!S){
				FOR(x,1,n){ // mor <=> x
					f[0][0] = 1;
					FOR(i,1,n){
						FOR(j,0,5) f[i][j] = f[i-1][j];
						if(a[i] == x) {FOR(j,1,5) if(b[j] == mor) f[i][j] += f[i-1][j-1];}
						else FOR(j,1,5) if(b[j] != mor) f[i][j] += f[i-1][j-1];
					}
					res += f[n][5];
				}
			}
			else{
				int all = -1,now = -1;
				int tb[6]={0};FOR(i,1,5) tb[i] = b[i];
				FOR(i,1,5){
					if(b[i] == mor) continue;
					now++;
					if((S>>now)&1){
						if(all == -1) all = b[i];
						else b[i] = all;
					}
				}
				res = Subtask2::Solve();
				FOR(i,1,5) b[i] = tb[i];
			}
			ans += res*(t?-1:1);
		}
		return ans;
	}
}

signed main(){
	scanf("%lld",&n);
	FOR(i,1,n) scanf("%lld",a+i),G[a[i]].pb(i);
	FOR(i,1,5) scanf("%lld",b+i);
	int mx = 0,cnt = 0;
	FOR(i,1,5) ct[b[i]]++;
	FOR(i,1,5){
		mx = std::max(mx,ct[i]);
		if(ct[i] >= 2) cnt++;
	}
	if(mx == 1) printf("%lld\n",Subtask1::Solve());
	if(cnt == 2) printf("%lld\n",Subtask2::Solve());
	if(cnt == 1) printf("%lld\n",Subtask3::Solve());
	return 0;
}