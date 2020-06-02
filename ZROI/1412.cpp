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

const int MAXN = 2e5 + 5;

struct Edge{
	int u,v,w;
	inline bool operator < (const Edge &t) const {
		return w > t.w;
	}
}e[MAXN];
int f[MAXN];
int du[MAXN],n,now;
bool v[MAXN];

inline int find(int x){
	return x == f[x] ? x : f[x] = find(f[x]);
}

int main(){
	scanf("%d",&n);int m = 0;
	LL sm = 0;FOR(i,1,2*n) f[i] = i;int tt = 0;
	FOR(i,2,n){
		int u,v,w;scanf("%d%d%d",&u,&v,&w);
		e[++m] = (Edge){u,v,w};du[u]++;du[v]++;sm += w;
	}
	FOR(i,2,n) if(du[i] == 1) v[i] = v[i+n] = 1,tt++;
	now = tt*2;
	FOR(i,2,n){
		int u,v,w;scanf("%d%d%d",&u,&v,&w);
		u += n;v += n;e[++m] = (Edge){u,v,w};sm += w;
	}
	f[n+1] = 1;std::sort(e+1,e+m+1);
	FOR(i,1,m){
		int x = find(e[i].u),y = find(e[i].v);
		if(x != y){
			if(now > tt+1 || (!v[x] || !v[y])){
				if(v[x]&&v[y]) now--;
				sm -= e[i].w;
				f[y] = x;v[x] |= v[y];
			}
		}
	}
	printf("%lld\n",sm);
	return 0;
}