#include <algorithm>
#include <iostream>
#include <cstring>
#include <climits>
#include <cstdlib>
#include <cstdio>
#include <bitset>
#include <vector>
#include <cmath>
#include <ctime>
#include <queue>
#include <stack>
#include <map>
#include <set>

#define fi first
#define se second
#define U unsigned
#define P std::pair
#define LL long long
#define pb push_back
#define MP std::make_pair
#define all(x) x.begin(),x.end()
#define CLR(i,a) memset(i,a,sizeof(i))
#define FOR(i,a,b) for(int i = a;i <= b;++i)
#define ROF(i,a,b) for(int i = a;i >= b;--i)
#define DEBUG(x) std::cerr << #x << '=' << x << std::endl

const int MAXN = 2e6 + 5;

struct Edge{
    int to,w,nxt;
}e[MAXN<<1];
int head[MAXN],cnt;
int du[MAXN],pw[MAXN];

inline void add(int u,int v,int w){
    e[++cnt] = (Edge){v,w,head[u]};head[u] = cnt;
    e[++cnt] = (Edge){u,w,head[v]};head[v] = cnt;
    du[u]++;du[v]++;
}
int n,m;

int dis[20][20];

inline void Floyd(){
	FOR(k,1,n){
		FOR(i,1,n){
			FOR(j,1,n){
				dis[i][j] = std::min(dis[i][j],dis[i][k]+dis[k][j]);
			}
		}
	}
}
int f[MAXN],g[MAXN];
inline void prework(){
	Floyd();FOR(i,1,(1<<n)) g[i] = 1e9;
	FOR(S,0,(1<<n)-1){
		FOR(i,1,n){
			if((S>>(i-1))&1) continue;
			FOR(j,i+1,n){
				if((S>>(j-1))&1) continue;
				g[S|(1<<(i-1))|(1<<(j-1))] = std::min(g[S|(1<<(i-1))|(1<<(j-1))],g[S]+dis[i][j]);
			}
		}
	}
}

inline void print(int S){
	FOR(i,1,n) putchar('0'+S/pw[i-1]%3);puts("");
}

inline void work(){
	FOR(i,0,pw[n]) f[i] = 1e9;
	std::queue<int> q;q.push(2);f[2] = 0;
	while(!q.empty()){
		int S = q.front();q.pop();
		std::vector<int> p;
		FOR(i,1,n) if((S/pw[i-1])%3) p.pb(i);
		FOR(i,1,n){
			if((S/pw[i-1])%3) continue;
			for(int j = head[i];j;j = e[j].nxt){
				if((S/pw[e[j].to-1])%3){
					int nxt = S+pw[i-1]*2;
					if(f[nxt] == 1e9) q.push(nxt);
					// print(nxt);print(S);DEBUG(f[S]);
					f[nxt] = std::min(f[nxt],f[S]);
				}
			}
			for(auto x:p){
				int nxt = S+pw[i-1];
				if((nxt/pw[x-1])%3 == 1) nxt += pw[x-1];
				else nxt -= pw[x-1];
				if(f[nxt] == 1e9) q.push(nxt);
				// print(nxt);print(S);DEBUG(f[S]);DEBUG(dis[i][x]);
				f[nxt] = std::min(f[nxt],f[S]+dis[i][x]);
			}
		}
	}
	// (1,2) (2,3) [(1,4)] (4,5)
	// int x = pw[0]+2*pw[1]+2*pw[2]+pw[3]+2*pw[4];
	// DEBUG(x);
	// DEBUG(f[x]);
}

int main(){
	pw[0] = 1;
	FOR(i,1,15) pw[i] = pw[i-1]*3;
	scanf("%d%d",&n,&m);
	FOR(i,1,n) FOR(j,1,i-1) dis[i][j] = dis[j][i] = 1e9;
	int ext = 0;
	FOR(i,1,m){
		int u,v,w;scanf("%d%d%d",&u,&v,&w);ext += w;
		add(u,v,w);dis[u][v] = dis[v][u] = std::min(dis[u][v],w);
	}
	scanf("%d",&m);
	FOR(i,1,m){
		int u,v,w;scanf("%d%d%d",&u,&v,&w);
		dis[u][v] = dis[v][u] = std::min(dis[u][v],w);	
	}
	prework();work();
	int ans = 1e9;
	FOR(S,0,pw[n]-1){
		int now = S;
		bool flag = true;
		FOR(i,1,n) if(du[i]) flag &= (bool)((S/pw[i-1])%3);
		if(!flag) continue;
		// DEBUG(S);
		FOR(i,1,n){
			if(du[i]&1){
				if(now/pw[i-1]%3 == 1) now += pw[i-1];
				else now -= pw[i-1];
			}
		}
		int t = 0;
		FOR(i,1,n) if(now/pw[i-1]%3 == 1) t |= (1<<(i-1));
		ans = std::min(ans,f[S]+g[t]);
	}
	printf("%d\n",ans+ext);
	return 0;
}
/*
考虑存在欧拉回路的充要条件是所有点的度数为偶数
朴素的想法是我们从 1 开始搜,设 f[S][i] 表示当前到 i 点 每个点的状态(未被选过,度数为奇,度数为偶) 但是我们这样不太好处理限制条件了
现在我们考虑先扔掉所有度数都要是偶的条件 考虑这个 dp 如何转移,我们枚举一个新点:
我们先不考虑被限制了的边的贡献
1. 这个新点是一个必选边的端点且另外一个端点在点集内: 我们直接加入点集转移
2. otherwise: 必定加入两点之间的一个路径 发现我们贪心加入最短路即可 更新一下奇偶性和代价
有人会疑惑为什么这样不会算重:实际上因为这里的权值是一条边经过几次算几次 所以我们这样算是合法的
统计答案是我们再手动 fix 一下奇数点:把奇数点两两用最短路连起来
总结:构造/计数回路可以先考虑如何加上一段路径 
*/