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
const int MAXN = 3e5 + 5;
const int MAXM = 60;
const int ha = 998244353;
int a[MAXN],n,k;

int ch[MAXN*MAXM][2],sm[MAXN*MAXM],tot = 1;
int root = 1;

inline void insert(int x,int val){
	int v = root;
	ROF(i,MAXM,0){
		int d = (x>>i)&1;
		if(!ch[v][d]) ch[v][d] = ++tot;
		(sm[v] += val) %= ha;
		v = ch[v][d];
	}
	sm[v] += val;
}

inline int query(int x){
	int res = 0,v = root;
	ROF(i,MAXM,0){
		int d = (k>>i)&1;
		int t = (x>>i)&1;
		if(!ch[v][d^t]){
			if(d) return res;
			else return (res+sm[v])%ha;
		}
		else{
			if(!d) (res += sm[ch[v][d^t^1]]) %= ha;
			v = ch[v][d^t];
		}
	}
	return (res+sm[v])%ha;
}

int f[MAXN];

signed main(){
	scanf("%lld%lld",&n,&k);
	FOR(i,1,n) scanf("%lld",a+i);
	std::sort(a+1,a+n+1);
	FOR(i,1,n){
		f[i] = (query(a[i]) + 1)%ha;
		insert(a[i],f[i]);
	}
	int ans = 0;
	FOR(i,1,n) (ans += f[i]) %= ha;
	printf("%lld\n",ans);
	return 0;
}