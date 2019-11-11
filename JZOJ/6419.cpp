#pragma GCC optimize("Ofast")
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
#define P std::pair<LL,int>
#define MP std::make_pair
#define FOR(i,a,b) for(register int i = a;i <= b;++i)
#define ROF(i,a,b) for(register int i = a;i >= b;--i)
#define DEBUG(x) std::cerr << #x << '=' << x << std::endl

inline char nc(){
	#define SIZE 1000000+3
	static char buf[SIZE],*p1 = buf+SIZE,*p2 = buf+SIZE;
	if(p1 == p2){
		p1 = buf;p2 = buf+fread(buf,1,SIZE,stdin);
		if(p1 == p2) return -1;
	}
	return *p1++;
}

inline void read(int &x){
	x = 0;char ch = nc();int flag = 0;
	while(!isdigit(ch)){
		if(ch == '-') flag = 1;
		ch = nc();
	}
	while(isdigit(ch)){
		x = (x<<1) + (x<<3) + (ch^'0');
		ch = nc();
	}
	if(flag) x = -x;
}

int n,m,k;

const int MAXN = 1e6 + 5;

struct Edge{
	int to,w,nxt;
}e[MAXN<<2];

int head[MAXN],th[MAXN],cnt,tcnt;

inline void add(int u,int v,int w){
	e[++cnt] = (Edge){v,w,head[u]};head[u] = cnt;
}

int S,T,N;
LL dis[2][MAXN];
int fr[2][MAXN];
bool used[MAXN];

inline void dij(int xx){
	std::priority_queue<P,std::vector<P>,std::greater<P> > q;
	FOR(i,1,N) dis[xx][i] = 1e18,used[i] = false;
	q.push(MP(dis[xx][S] = 0,S));
	while(!q.empty()){
		int v = q.top().se;q.pop();
		if(used[v]) continue;
		used[v] = true;
		for(int i = head[v];i;i = e[i].nxt){
			if(dis[xx][e[i].to] > dis[xx][v] + e[i].w){
				dis[xx][e[i].to] = dis[xx][v] + e[i].w;
                if(v != S) fr[xx][e[i].to] = fr[xx][v];
				q.push(MP(dis[xx][e[i].to],e[i].to));
			}
		}
	}
}

int a[MAXN];

inline int pc(int x){
	int res = 0;
	while(x) res++,x >>= 1;
	return res;
}

inline bool sub(){
	if(n <= 1000 && m <= 5000) return false;
	if(n <= 1e5 && m <= 1e5){
		if(k <= 5000) return false;
		return true;	
	}
	return true;
}

struct Node{
    int u,v,w;

    Node(int u=0,int v=0,int w=0) : u(u),v(v),w(w) {}
}edge[MAXN];
bool D[MAXN];
int main(){
    freopen("tour.in","r",stdin);
	//freopen("tour.out","w",stdout);
	scanf("%d%d%d",&n,&m,&k);
	FOR(i,1,m){
		int u,v,w;scanf("%d%d%d",&u,&v,&w);
		add(u,v,w);edge[i] = Node(u,v,w);
    }
	FOR(i,1,k) scanf("%d",a+i),D[a[i]] = 1,fr[0][a[i]] = fr[1][a[i]] = a[i];
    S = N = n+1;
    FOR(i,1,k) add(S,a[i],0);
    dij(0);
    cnt = 0;FOR(i,1,N) head[i] = 0;
    FOR(i,1,m) add(edge[i].v,edge[i].u,edge[i].w);
    FOR(i,1,k) add(S,a[i],0);
    dij(1);
    LL ans = 1e18;
    FOR(i,1,m){
        if(D[edge[i].u] && D[edge[i].v]) ans = std::min(ans,(LL)edge[i].w);
        else if(fr[0][edge[i].u] != fr[1][edge[i].v]) ans = std::min(ans,edge[i].w+dis[0][edge[i].u]+dis[1][edge[i].v]);
//            if(edge[i].w+dis[0][edge[i].u]+dis[1][edge[i].v] == 2) DEBUG(i)
    }
    printf("%lld\n",ans);
	return 0;
}

