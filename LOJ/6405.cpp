#include<bits/stdc++.h>
#include<ext/pb_ds/priority_queue.hpp>

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
#define int LL
const int MAXN = 3e5 + 5;

struct Edge{
	int to,w,nxt;
}e[MAXN<<1];
int head[MAXN],cnt;

inline void add(int u,int v,int w){
	e[++cnt] = (Edge){v,w,head[u]};head[u] = cnt;
	e[++cnt] = (Edge){u,w,head[v]};head[v] = cnt;
}

int dep[MAXN];

inline void dfs1(int v,int fa=0){
	for(int i = head[v];i;i = e[i].nxt){
		if(e[i].to == fa) continue;
		dep[e[i].to] = dep[v]+e[i].w;dfs1(e[i].to,v);
	}
}

int n;
int a[MAXN];
// > 0 hole  < 0 mouse
int ans;
__gnu_pbds::priority_queue<int,std::greater<int> > q1[MAXN],q2[MAXN];

inline void dfs2(int v,int fa=0){
    if(a[v] > 0) while(a[v]--) q1[v].push(dep[v]);
    else if(a[v] < 0) while(a[v]++) q2[v].push(dep[v]-1e12);
    for(int i = head[v];i;i = e[i].nxt){
        if(e[i].to == fa) continue;
        dfs2(e[i].to,v);
        q1[v].join(q1[e[i].to]);
        q2[v].join(q2[e[i].to]);
    }
    while(!q1[v].empty() && !q2[v].empty() && q1[v].top()+q2[v].top()-2*dep[v] < 0){
        int h = q1[v].top(),m = q2[v].top();q1[v].pop();q2[v].pop();
        ans += h+m-2*dep[v];
        q1[v].push(2*dep[v]-m);q2[v].push(2*dep[v]-h);
    }
}

signed main(){
	scanf("%lld",&n);
	FOR(i,2,n){
		int u,v,w;scanf("%lld%lld%lld",&u,&v,&w);
		add(u,v,w);
	}
    int cnt = 0;
	FOR(i,1,n){
        int x,y;scanf("%lld%lld",&x,&y);
        a[i] = x-y;if(a[i] < 0) cnt -= a[i];
	}
	dfs1(1);
	dfs2(1);
	printf("%lld\n",ans+1000000000000*cnt);
	return 0;
}
