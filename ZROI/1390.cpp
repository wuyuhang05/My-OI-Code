#include<bits/stdc++.h>

#define fi first
#define se second
#define U unsigned
#define LL long long
#define pb push_back
#define MP std::make_pair
#define all(x) x.begin(),x.end()
#define CLR(i,a) memset(i,a,sizeof(i))
#define FOR(i,a,b) for(int i = a;i <= b;++i)
#define ROF(i,a,b) for(int i = a;i >= b;--i)
#define DEBUG(x) std::cerr << #x << '=' << x << std::endl

const int MAXN = 1e7 + 5;
const int ha = 998244353;
int n,k,x;
int P[MAXN],Q[MAXN];

inline int qpow(int a,int n=ha-2){
	int res = 1;
	while(n){
		if(n & 1) res = 1ll*res*a%ha;
		a = 1ll*a*a%ha;
		n >>= 1;
	}
	return res;
}

int main(){
	scanf("%d%d%d",&n,&k,&x);
	int sm = 0;
	FOR(i,0,k) scanf("%d",P+i),sm += P[i];
	sm = qpow(sm);
	FOR(i,0,k) P[i] = 1ll*P[i]*sm%ha;
	Q[0] = qpow(P[0],n);int inv=qpow(P[0]);
	int ans = 0;sm = Q[0];
	FOR(i,1,x-1){
		FOR(j,1,std::min(i,k)){
			(Q[i] += 1ll*j*P[j]%ha*Q[i-j]%ha) %= ha;
			// if(i == 1) DEBUG(j),DEBUG(P[j]),DEBUG(Q[i-j]);
		}
		Q[i] = 1ll*Q[i]*n%ha;
		FOR(j,1,std::min(i,k)) (Q[i] += ha-1ll*(i-j)*P[j]%ha*Q[i-j]%ha) %= ha;
		Q[i] = 1ll*Q[i]*inv%ha*qpow(i)%ha;
		// DEBUG(Q[i]);
		(ans += 1ll*i*Q[i]%ha) %= ha;
		(sm += Q[i]) %= ha;
	}
	(ans += 1ll*x*(ha+1-sm)%ha) %= ha;
	printf("%d\n",ans);
	return 0;
}