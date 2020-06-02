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

const int MAXN = 3e5 + 5;
const int ha = 10000;
int pw[MAXN];
int a[MAXN];
int nxt[MAXN];

int main(){
	int n,t;scanf("%d%d",&n,&t);
	pw[0] = 1;FOR(i,1,MAXN-1) pw[i] = 1ll*pw[i-1]*n%ha;
	while(t--){
		int m;scanf("%d",&m);
		FOR(i,1,m) scanf("%d",a+i);
		nxt[1] = 0;
		FOR(i,2,m){
			int j = nxt[i-1];
			while(j && a[j+1] != a[i]) j = nxt[j];
			if(a[j+1] == a[i]) j++;nxt[i] = j;
		}
		int p = m,ans = 0;
		while(p){
			(ans += pw[p])%=ha;
			p = nxt[p];
		}
		printf("%04d\n",ans);
	}
	return 0;
}