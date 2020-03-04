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

const int MAXN = 40+5;
const int MAXM = 3e5+5;
const int ha = 1e9 + 7;
const int BASE = 41;

int f[MAXN][MAXM];bool g[MAXN][MAXM],ep[MAXN],vis[MAXN];
std::map<int,int> S;
int rS[MAXM];
int tot;
int n;
char str[MAXN];
int sm[MAXN];
int fac[MAXN],base[MAXN],pw[MAXN];
int s[MAXM],t[MAXM];
int ans;
int A[MAXN],tp;

inline void work(int rem,int nxt,int now){
	if(!rem){
		now = S[now];
		int res = 1ll*s[now]*t[now]%ha;
		for(int l = 1,r = 1;r <= tp;l = r,r = l){
			while(r <= tp && A[r] == A[l]) ++r;
			res = 1ll*res*fac[r-l]%ha;
			if(A[l] != 1) res = 1ll*res*pw[r-l]%ha;
		}
		(ans += res) %= ha;
		return;
	}
	if(rem < nxt) return;
	A[++tp] = nxt;
	work(rem-nxt,nxt,(now+base[nxt])%ha);
	--tp;
	work(rem,nxt+1,now);
}
#include <cassert>
int main(){
	scanf("%d",&n);scanf("%s",str+1);str[n] = '0';
	fac[0] = base[0] = pw[0] = 1;
	FOR(i,1,MAXN-1) fac[i] = 1ll*fac[i-1]*i%ha,base[i] = 1ll*base[i-1]*BASE%ha,pw[i] = 2ll*pw[i-1]%ha;
	FOR(i,1,n) sm[i] = sm[i-1]+(str[i]=='0');
	f[0][0] = 1;g[0][0] = 1;
	FOR(i,0,n-1){
		int up = tot;
		FOR(j,0,up){
			if(!g[i][j]) continue;
			FOR(k,i+1,n){
				if(str[k] != '0') continue;
				int nxt = (rS[j]+base[k-i])%ha;
				if(!S.count(nxt)) S[nxt] = ++tot,rS[tot] = nxt;
				nxt = S[nxt];
				if((sm[k-1]-sm[i])&1) (f[k][nxt] += ha-f[i][j]) %= ha;
				else (f[k][nxt] += f[i][j]) %= ha;
				g[k][nxt] = 1;
			}
		}
	}
	// DEBUG(tot);
	FOR(i,0,tot) s[i] = f[n][i];CLR(f,0);
	f[0][0] = 1;CLR(g,0);g[0][0] = 1;
	int cnt = 0;
	FOR(i,1,n){
		if(vis[i]) continue;
		for(int j = i;j <= n;j*=2) vis[j] = 1,cnt++;
		ep[cnt] = true;
	}
	FOR(i,0,n-1){
		int up = tot;
		FOR(j,0,up){
			if(!g[i][j]) continue;
			FOR(k,i+1,n){
				int nxt = (rS[j]+base[k-i])%ha;
				if(!S.count(nxt)) S[nxt] = ++tot,rS[tot] = nxt;
				nxt = S[nxt];
				(f[k][nxt] += f[i][j]) %= ha;g[k][nxt] = 1;
				if(ep[k]) break;
			}
		}
	}
	FOR(i,0,tot) t[i] = f[n][i];
	work(n,1,0); // dfs 划分数
	printf("%d\n",ans);
	return 0;
}
/*
思考一个暴力的做法:我们对序列做一个容斥 把要求不是倍数的关系容斥掉 按照无限制的点序列被分成了一块一块的
然后我们把1...40这些数按照倍数的顺序排一下(比如1 2 4 8|3 6|5|7) 然后对它也做一个类似的划分 但是注意不能把不同组的划分到一起
然后发现如果两边的划分状态相同的话 只需要相同大小的配对一下乘一些东西就可以合并答案了
*/