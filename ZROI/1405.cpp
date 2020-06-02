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

const int MAXN = 15+1;
const int ha = 1e9 + 7;
int f[MAXN][(1<<MAXN)+3];// i S
int n,m;
int R[MAXN];
int e[MAXN];
int id[MAXN],di[MAXN];
int pc[(1<<MAXN)+3],pd[(1<<MAXN)+3];
bool g[(1<<MAXN)+3];

inline bool cmp(int x,int y){
	return R[x] < R[y];
}

int main(){
	scanf("%d%d",&n,&m);
	FOR(i,0,n-1) scanf("%d",R+i);
	std::iota(id,id+n,0);
	std::sort(id,id+n,cmp);
	FOR(i,0,n-1) di[id[i]] = i;
	pc[0] = 0;FOR(i,1,(1<<MAXN)-1) pc[i] = pc[i>>1]+(i&1);
	pd[0] = 0;FOR(i,1,(1<<MAXN)-1) pd[i] = pd[i>>1]+1;
	FOR(i,1,m){
		int u,v;scanf("%d%d",&u,&v);u--;v--;//u = id[u-1];v = id[v-1];
		e[u] |= (1<<di[v]);e[v] |= (1<<di[u]);
	}
	g[0] = 1;
	// FOR(i,0,n-1) DEBUG(id[i]);
	FOR(S,1,(1<<n)-1){
		bool flag = 1;
		FOR(i,0,n-1){
			if(!((S>>i)&1)) continue;
			if(e[id[i]]&S){flag = 0;break;}
		}
		g[S] = flag;
	}
	f[0][0] = 1;int all = (1<<n)-1;
	FOR(i,0,n-1){
		// FOR(S,0,(1<<n)-1) DEBUG(f[i][S]); 
		FOR(S,0,(1<<n)-2){
			if(!f[i][S]) continue;
			int oth = all^S,low = oth&(-oth);
			// DEBUG(oth);
			oth ^= low;int t = pd[low]-1;
			// DEBUG(t);
			if(R[id[t]]+1-i <= 0) continue;
			// DEBUG(oth);
			for(int T = oth;;T=(T-1)&oth){
				if(g[T|low]) (f[i+1][S|T|low] += 1ll*f[i][S]*(R[id[t]]+1-i)%ha)%=ha;
				if(!T) break;
			}
		}
	}
	// DEBUG(1);
	int ans = 0;
	FOR(i,1,n) (ans += 1ll*f[i][all]*i%ha) %= ha;//,DEBUG(f[i][all]);
	printf("%d\n",ans);
	return 0;
}