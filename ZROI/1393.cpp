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
const int ha = 998244353;

int a[MAXN],n;
bool vis[MAXN];
int p[MAXN],cnt[MAXN];

inline int qpow(int a,int n=ha-2){
	int res = 1;
	while(n){
		if(n & 1) res = 1ll*res*a%ha;
		a = 1ll*a*a%ha;
		n >>= 1;
	}
	return res;
}

inline void Solve(){
	scanf("%d",&n);
	FOR(i,1,n) scanf("%d",a+i),vis[i] = p[i] = cnt[i] = 0;
	FOR(i,1,n){
		if(!vis[i]){
			int t = i,len = 0;
			do{
				t = a[t];vis[t] = 1;++len;
			}while(t != i);
			p[len]++;
		}
	}
	FOR(i,1,n){
		for(int j = 2*i;j <= n;j += i){
			cnt[j] += i*p[i];
		}
	}
	int ans = 1;
	FOR(i,1,n){
		if(!p[i]) continue;
		if(i == 1){
			if(p[1] != 1) ans = qpow(p[1],p[1]-2);
		}
		else if(i == 2 && !p[1]){
			ans = qpow(2ll*p[2]%ha,p[2]-1);
		}
		else ans = 1ll*ans*cnt[i]%ha*qpow((cnt[i]+1ll*i*p[i]%ha)%ha,p[i]-1)%ha;
	}
	printf("%d\n",ans);
}

int main(){
	int T;scanf("%d",&T);
	while(T--) Solve();
	return 0;
}