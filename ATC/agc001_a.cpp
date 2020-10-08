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
int n;
int a[MAXN];

int main(){
	scanf("%d",&n);n <<= 1;
	FOR(i,1,n) scanf("%d",a+i);
	std::sort(a+1,a+n+1);
	int ans = 0;
	for(int i = 1;i <= n;i += 2) ans += a[i];
	printf("%d\n",ans);
	return 0;
}