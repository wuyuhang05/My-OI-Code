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

const int MAXN = 5e4 + 5;
int p[MAXN],q[MAXN];
int f[MAXN];
P fa[MAXN];

int main(){
	int n,T;scanf("%d%d",&n,&T);
	FOR(i,1,n) scanf("%d",p+i),q[p[i]] = i;
	int t = 0;f[1] = 1;
	FOR(i,2,n){
		if(q[i-1] > q[i]) f[i] = f[i-1]+1,t++;
		else f[i] = f[i-1];
	}
	int ans = 0;
	// FOR(i,1,n) DEBUG(f[i]);
	while(t) t>>=1,ans++;
	printf("%d\n",ans);
	if(T == 1){
		FOR(i,1,n){
			fa[i] = MP(p[i],f[p[i]]-1);//DEBUG(f[p[i]]);
			printf("%d ",p[i]);
		}puts("");
		FOR(k,0,ans-1){
			std::vector<P> toL,toR;
			FOR(i,1,n){
				if((fa[i].se>>k)&1) toR.pb(fa[i]);
				else toL.pb(fa[i]);
			}
			int tot = 0;
			for(auto x:toL) fa[++tot] = x;
			for(auto x:toR) fa[++tot] = x;
			FOR(i,1,n) printf("%d ",fa[i].fi);puts("");
		}
	}
	return 0;
}