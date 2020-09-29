#include <bits/stdc++.h>

#define fi first
#define se second
#define db double
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

const int MAXN = 1e5 + 5;
const int ha = 1e9 + 7;
const int inv2 = (ha+1)>>1;
int w[MAXN],h[MAXN],n,g[MAXN];

inline void add(int &x,int y){
	x += y;if(x >= ha) x -= ha;
}

inline int C(int n){
	return 1ll*n*(n+1)%ha*inv2%ha;
}

int st[MAXN],tp = 0;
int sm[MAXN];
int x[MAXN];

int main(){
	scanf("%d",&n);
	FOR(i,1,n) scanf("%d",h+i);
	FOR(i,1,n) scanf("%d",w+i),x[i] = w[i];
	FOR(i,1,n) add(x[i],x[i-1]);
	int ans = 0,sm = 0;
	FOR(i,1,n){
		while(tp && h[st[tp]] >= h[i]){
			int gx = 1ll*(x[st[tp]]-x[st[tp-1]]+ha)%ha*C(h[st[tp]])%ha;
			add(sm,ha-gx),--tp;
		}
		add(ans,1ll*C(h[i])*C(w[i])%ha);
		int a = w[i];
		add(ans,1ll*a*sm%ha);
		add(ans,1ll*a*(x[i-1]-x[st[tp]]+ha)%ha*C(h[i])%ha);
		st[++tp] = i;
		int gx = 1ll*(x[st[tp]]-x[st[tp-1]]+ha)%ha*C(h[st[tp]])%ha;
		add(sm,gx);
	}
	printf("%d\n",ans);
	return 0;
}