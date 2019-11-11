#include <algorithm>
#include <iostream>
#include <climits>
#include <cstring>
#include <cstdio>
#include <ctime>
#include <cstdlib>
#include <vector>
#include <queue>
#include <stack>
#include <map>
#include <set>

#define LL long long
#define fi first
#define se second
#define pb push_back
#define all(x) x.begin(),x.end()
#define CLR(a,b) memset(a,b,sizeof(a))
#define P std::pair<LL,LL>
#define MP std::make_pair
#define FOR(i,a,b) for(int i = a;i <= b;++i)
#define ROF(i,a,b) for(int i = a;i >= b;--i)
#define DEBUG(x) std::cerr << #x << '=' << x << std::endl

const int MAXN = 1000+5;
const int ha = 998244353;

struct Edge{
	int to,nxt;
}e[MAXN<<3];

int head[MAXN],cnt;

inline void add(int u,int v){
	e[++cnt] = (Edge){v,head[u]};head[u] = cnt;
	e[++cnt] = (Edge){u,head[v]};head[v] = cnt;
}

int dis[MAXN][MAXN],n,m,inv[MAXN];

inline void dij(int s){
	std::queue<int> q;
	FOR(i,1,n) dis[s][i] = 1e9;
	dis[s][s] = 0;q.push(s);
	while(!q.empty()){
		int v = q.front();q.pop();
		for(int i = head[v];i;i = e[i].nxt){
			if(dis[s][e[i].to] > dis[s][v] + 1){
				dis[s][e[i].to] = dis[s][v] + 1;
				q.push(e[i].to);
			}
		}
	}
}
#include <assert.h>
int pro[MAXN][MAXN];
bool vis[MAXN];
bool used[MAXN];

inline void bfs(int x,int s,int t){
	pro[x][s] = 1;
	std::queue<int> q;
    FOR(i,1,n) used[i] = false;
	q.push(s);
	while(!q.empty()){
		int v = q.front();q.pop();int cnt = 0;
        if(used[v]) continue;
        used[v] = true;
		for(int i = head[v];i;i = e[i].nxt){
			if(dis[s][v]+1+dis[e[i].to][t] == dis[s][t]){
    //            printf("%d %d\n",v,e[i].to);
				++cnt;
			}
		}
		cnt = inv[cnt];
		for(int i = head[v];i;i = e[i].nxt){
			if(dis[s][v]+1+dis[e[i].to][t] == dis[s][t]){
				(pro[x][e[i].to] += 1ll*pro[x][v]*cnt%ha) %= ha;
				q.push(e[i].to);
			}
		}
	}
//    DEBUG(pro[x][24]);
}

int k;

struct Node{
	int a,b,c,id;
	
	Node(int a=0,int b=0,int c=0,int id=0) : a(a),b(b),c(c),id(id) {}
}a[MAXN];
int sl[MAXN][MAXN],mx;
int pre[MAXN],suf[MAXN];
std::vector<int> S;

inline void clear(){
	CLR(sl,0);CLR(pre,0);CLR(suf,0);mx = 0;CLR(a,0);CLR(pro,0);
	CLR(head,0);cnt = 0;S.clear();
}

inline void Solve(){
	scanf("%d%d%d",&n,&m,&k);mx = 0;
	FOR(i,1,m){
		int u,v;scanf("%d%d",&u,&v);
		add(u,v);
	}
	FOR(i,1,n) dij(i);
	FOR(i,1,k) FOR(j,1,n) sl[i][j] = 1;
	FOR(i,1,k){
		int c,a,b;
		scanf("%d%d%d",&c,&a,&b);
		::a[i] = Node(a,b,c,i);
		S.pb(c);	
	}
	std::sort(all(S));S.erase(std::unique(all(S)),S.end());
	FOR(i,1,k) a[i].c = std::lower_bound(all(S),a[i].c)-S.begin()+1,mx = std::max(mx,a[i].c);
	FOR(i,1,k){
		bfs(i,a[i].a,a[i].b);
		FOR(j,1,n) sl[a[i].c][j] = 1ll*sl[a[i].c][j]*((1-pro[i][j]+ha)%ha)%ha;
	}
	FOR(i,1,mx) FOR(j,1,n) sl[i][j] = (1-sl[i][j]+ha)%ha;
	FOR(i,1,n){
		int ans0 = 1,ans1 = 0;
		pre[0] = 1;suf[mx+1] = 1;
		FOR(x,1,mx){
			ans0 = 1ll*ans0*((1-sl[x][i]+ha)%ha)%ha;
			pre[x] = 1ll*pre[x-1]*((1-sl[x][i]+ha)%ha)%ha;
		}
		ROF(x,mx,1) suf[x] = 1ll*suf[x+1]*((1-sl[x][i]+ha)%ha)%ha;//,DEBUG(sl[x][i]);
		FOR(x,1,mx){
			int sm = sl[x][i];
			sm = 1ll*sm*pre[x-1]%ha*suf[x+1]%ha;
			(ans1 += sm) %= ha;
		}
    //    if(i == 24) DEBUG(ans1);
		(ans0 += ans1) %= ha;
		int ans = (1-ans0+ha)%ha;
		printf("%d\n",ans);
	}
	clear();
}

int main(){
	freopen("sukeban.in","r",stdin);
	freopen("sukeban.out","w",stdout);
	inv[1] = 1;
	FOR(i,2,MAXN-1) inv[i] = 1ll*(ha-ha/i)*inv[ha%i]%ha;
	int T;scanf("%d",&T);
	while(T--) Solve();
	return 0;
}

