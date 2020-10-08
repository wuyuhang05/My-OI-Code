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

const int MAXN = 1e6 + 5;
const int MAXM = 3e7 + 5;
int n,e,a[MAXN];
LL f[2][MAXM];int now;

int main(){
	scanf("%d%d",&n,&e);
	FOR(i,1,n) scanf("%d",a+i);
	FOR(i,1,MAXM-1) f[now][i] = 1e18;
	int ans = 0;
	ROF(i,n,1){
		int lim = e/i;
		FOR(j,0,lim) f[now^1][j] = 1e18;
		FOR(j,0,lim){
			f[now^1][j] = (j<=e/(i+1))?f[now][j]:1e18;
			if(j >= a[i] && j-a[i] <= e/(i+1)) f[now^1][j] = std::min(f[now^1][j],f[now][j-a[i]]+1ll*i*a[i]+(j==a[i])*2*i);
		}
		now ^= 1;
	}
	ROF(i,e,0){
		if(f[now][i] <= e){
			printf("%d\n",i);
			return 0;
		}
	}
	return 0;
}
/*
第i个位置只能选择重量<e/i
所以有时候要考虑答案能否扔到状态！！
所以可以扩展到>=i的位置只能选择重量<e/i 所以要倒着才能缩状态
*/