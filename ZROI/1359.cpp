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

const int MAXN = 5000+5;
const int ha = 1e9 + 7;

inline void add(int &x,int y){
    (x += y);if(x >= ha) x -= ha;
}

int f[MAXN][MAXN][2];

struct Edge{
    int to,nxt;
}e[MAXN<<1];
int head[MAXN],cnt;

inline void adde(int u,int v){
    e[++cnt] = (Edge){v,head[u]};head[u] = cnt;
    e[++cnt] = (Edge){u,head[v]};head[v] = cnt;
}

int sz[MAXN];

int tmp[MAXN][2];

inline void merge(int x,int y){
    FOR(i,0,sz[x]+sz[y]+2) tmp[i][0] = tmp[i][1] = 0;
    FOR(i,1,sz[x]){
        FOR(j,1,sz[y]){// 结束前一定要选一个
            add(tmp[i+j][0],1ll*f[x][i][0]*f[y][j][1]%ha);
            add(tmp[i+j][1],1ll*f[x][i][1]*f[y][j][1]%ha);
            add(tmp[i+j-1][0],1ll*f[x][i][0]*f[y][j][0]%ha);
            add(tmp[i+j-1][1],1ll*f[x][i][1]*f[y][j][0]%ha);
            add(tmp[i+j-1][1],1ll*f[x][i][0]*f[y][j][1]%ha);
        }
    }
    sz[x] += sz[y];
    FOR(i,0,sz[x]) FOR(j,0,1) f[x][i][j] = tmp[i][j];
}

inline void dfs(int v,int fa=0){
    sz[v] = 1;f[v][1][0] = f[v][1][1] = 1;
    for(int i = head[v];i;i = e[i].nxt){
        if(e[i].to == fa) continue;
        dfs(e[i].to,v);merge(v,e[i].to);
    }
}

inline int qpow(int a,int n=ha-2){
	int res = 1;
	while(n){
		if(n & 1) res = 1ll*res*a%ha;
		a = 1ll*a*a%ha;
		n >>= 1;
	}
	return res;
}

int fac[MAXN],inv[MAXN];

inline void prework(){
    fac[0] = 1;FOR(i,1,MAXN-1) fac[i] = 1ll*fac[i-1]*i%ha;
    inv[MAXN-1] = qpow(fac[MAXN-1]);ROF(i,MAXN-2,0) inv[i] = 1ll*inv[i+1]*(i+1)%ha;
}

inline int C(int n,int m){
    return 1ll*fac[n]*inv[m]%ha*inv[n-m]%ha;
}

int n,k;
int g[MAXN];

int main(){
    prework();
    scanf("%d%d",&n,&k);
    FOR(i,2,n){
        int u,v;scanf("%d%d",&u,&v);adde(u,v);
    }
    dfs(1);g[1] = 1;
    FOR(i,2,n) g[i] = 1ll*f[1][i][1]*qpow(n,i-2)%ha;
    // 连通块 个数为 i  边数 n-i
    int ans = 0;
    FOR(i,std::max(0,n-1-k),n){
        FOR(j,i,n){
            int t = 1ll*C(j,i)*g[n-j]%ha;
            if((j-i)&1) t = ha-t;
            (ans += t) %= ha;
        }
    }
    printf("%d\n",ans);
    return 0;
}
/*
题目实际上是问相同的边 >=k 的方案数 设这个答案是 f[k]
一个自然的想法是去枚举 k 个相同的边 但是发现设 这个算出来的是 g[k] 一个有 x 个相同的边会被算 C(x,k) 次
所以二项式反演去重 
枚举边之后 方案数就是这些连通块缩起来组成的无根树个数 乘上每个连通块选一个代表的方案数
对着这个东西写一个 dp：f[v][i][0/1] 考虑 v 子树 重了 i 个边 当前连通块是否选了 代表
转移合并子树 考虑这个边是否选进来就好
*/
