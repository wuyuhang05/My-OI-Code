/*
十分有意思的一个小题
遇到这种题 发现自己只会暴力 可以想自己会哪些暴力
首先多串匹配问题 建个广义 SAM 肯定没问题(注意广义 SAM 与普通 SAM 构造略有不同 请看代码!!!)
然后发现两种暴力:
1. 在 s[k] 中出现等价于是 s[k] 某些前缀的后缀,于是枚举 s[k] 的所有前缀 求一下 fail 树上到根路径上编号在[l,r]点的数量
2. 枚举[l,r]内所有的串 相当于询问 fail 树上子树里编号=k的串的数量
发现 1 与长度严格有关 2 只要数量不太多貌似也还可以
于是我们考虑根号分治 QAQ 我们设一个变量 T=√n
询问离线下来是肯定的.下面我们认为 n 与 T 同阶
对于 >=T 的串,数量不会超过 O(n/T) 个 直接暴力使用方法 2 求出所有串的答案 做个前缀和批量解决关于这个点答案
对于 <T 的串 可以把每个询问拆成 O(T) 个询问,询问就变成了(v,l,r) 表示询问fail 树上 v 号点到根的路径上 编号在[l,r] 范围内的数个数(v 就是这个前缀对应的点了)
询问总共是有 O(nT) 个的,如果使用主席树那种做法看来复杂度会爆炸
我们考虑离线来做 询问现在为(v,p) 表示询问fail 树上 v 点到根的路径上 <=l 的个数
于是我们边处理询问边加入 发现总共会有 O(n)次单点加入 O(nT) 次到根查询
转化为 O(n) 次区间加1和 O(nT) 次单点查询
使用线段树复杂度不是很理想:O(nlogn+nTlogn)
如果遇到操作很少的情况,我们考虑对次数少的操作用较大的复杂度,让询问复杂度变少来平衡
我们使用 O(√n)-O(1) 的分块完成即可
最后使用 SAM 的代价是要卡空间的...不是像我这样无聊学习广义 SAM 的可以使用随便一种其他算法构 fail 树
 */
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

const int MAXN = 2e5 + 5;
const int MAXM = 1e5 + 5;
int ans[MAXN];LL tmp[MAXM];
int T;
std::vector<int> pos[MAXM],suf[MAXN];// 是谁的后缀
struct SAM{
	int fail[MAXN],len[MAXN];
	std::map<char,int> ch[MAXN];
	int tot = 1,las = 1;

	inline void copy(int x,int y){
		// FOR(i,0,25) ch[x][i] = ch[y][i];
		ch[x] = ch[y];
		fail[x] = fail[y];len[x] = len[y];
	}

	inline int split(int p,int c){
		int q = ch[p][c],nq = ++tot;
		copy(nq,q);len[nq] = len[p]+1;
		fail[q] = nq;
		while(p&&ch[p][c] == q) ch[p][c] = nq,p = fail[p];
		return nq;
	}

	inline int insert(int c){
		int p = las,q = ch[p][c];
		if(q){
			if(len[q] == len[p]+1) return q;
			else return split(p,c);
		}
		int np = ++tot;len[np] = len[p]+1;
		while(p&&!ch[p][c]) ch[p][c] = np,p = fail[p];
		if(!p) fail[np] = 1;
		else{
			int q = ch[p][c];
			if(len[q] == len[p]+1) fail[np] = q;
			else fail[np] = split(p,c);
		}
		return np;
 	}

	std::vector<int> G[MAXN];
	int dfn[MAXN],sz[MAXN];
	inline void dfs(int v){
		static int ts = 0;
		dfn[v] = ++ts;sz[v] = 1;
		for(auto x:G[v]){
			dfs(x);
			sz[v] += sz[x];
		}
	}

	inline void build(){
		FOR(i,2,tot) G[fail[i]].pb(i);
		dfs(1);
	}

	inline void dfs1(int v){
		for(auto x:G[v]){
			dfs1(x);
			ans[v] += ans[x];
		}
		for(auto x:suf[v]) tmp[x] += ans[v];
	}
}sam;

struct DS{
	int blo[MAXN];LL tag[MAXN],val[MAXN];
	int BASE;

	inline void init(int n){
		BASE = std::sqrt(1.0*n);BASE = std::max(BASE,1);
		FOR(i,1,n) blo[i] = (i-1)/BASE+1;
	}

	inline void modify(int l,int r,int d){
		if(blo[l] == blo[r]){
			FOR(i,l,r) val[i] += d;
			return;
		}
		FOR(i,l,blo[l]*BASE) val[i] += d;
		FOR(i,blo[l]+1,blo[r]-1) tag[i] += d;
		FOR(i,(blo[r]-1)*BASE+1,r) val[i] += d;
	}

	inline int query(int x){
		return val[x]+tag[blo[x]];
	}
}Tr;

int n,q;
char str[MAXM];

struct Node{
	LL l:19;
	LL r:19;
	LL id:19;
	Node(int l=0,int r=0,int id=0) : l(l),r(r),id(id) {}
};

std::vector<Node> qu[MAXM];
std::vector<Node> qq[MAXM]; // <v,id,+-1>
LL res[MAXM];

int main(){
	scanf("%d%d",&n,&q);
	FOR(i,1,n){
		scanf("%s",str+1);
		sam.las = 1;
		int len = strlen(str+1);
		FOR(j,1,len){
			sam.las = sam.insert(str[j]-'a');
			pos[i].pb(sam.las);
		}
		suf[pos[i][(int)pos[i].size()-1]].pb(i);
		T += len;
	}
	// DEBUG(pos[5][0]);
	sam.build(); 
	T = std::sqrt(1.0*T);
	FOR(i,1,q){
		int l,r,v;scanf("%d%d%d",&l,&r,&v);
		qu[v].pb(Node(l,r,i));
	}
	FOR(i,1,n){
		if(pos[i].size() >= T){
			FOR(i,1,sam.tot) ans[i] = 0;
			FOR(i,1,n) tmp[i] = 0;
			for(auto x:pos[i]) ans[x] = 1;
			sam.dfs1(1);
			// FOR(i,1,n) DEBUG(tmp[i]);
			FOR(i,1,n) tmp[i] += tmp[i-1];
			for(auto x:qu[i]){
				res[x.id] += tmp[x.r]-tmp[x.l-1];
			}
			qu[i].clear();
		}
	}
	FOR(i,1,sam.tot) suf[i].clear();
	FOR(i,1,n){
		if(pos[i].size() < T){
			for(auto x:qu[i]){
				for(auto v:pos[i]){
					qq[x.r].pb(Node(v,(int)x.id,1));
					qq[x.l-1].pb(Node(v,(int)x.id,-1));
				}
			}
			qu[i].clear();
		}
	}
	Tr.init(sam.tot);
	// exit(0);
	FOR(i,1,n){
		int t = pos[i][(int)pos[i].size()-1];
		Tr.modify(sam.dfn[t],sam.dfn[t]+sam.sz[t]-1,1);
		for(auto x:qq[i]) res[(int)x.r] += (int)x.id*Tr.query(sam.dfn[(int)x.l]);
		pos[i].clear();
	}
	FOR(i,1,q) printf("%lld\n",res[i]);
	return 0;
}