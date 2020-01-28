/*
一个字符串在另一个字符串出现了多少次,等价于找到这个字符串在 SAM 上对应的状态的点的 endpos 大小
于是我们需要动态维护 endpos 大小
注意到 endpos 大小的求法是将所有代表前缀的点记为 1 然后求 fail 树子树和
所以我们需要动态维护出 fail 树(支持 link,cut) 然后支持子树查询(维护虚儿子信息即可)
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

const int MAXN = 2e6 + 5;

struct LCT{
	int ch[MAXN][2],f[MAXN],val[MAXN],tag[MAXN];
	#define lc (ch[x][0])
	#define rc (ch[x][1])

	inline bool nroot(int x){
		return ch[f[x]][0] == x || ch[f[x]][1] == x;
	}

	inline void cover(int x,int d){
		val[x] += d;
		tag[x] += d;
	}

	inline void pushdown(int x){
		if(tag[x]){
			if(lc) cover(lc,tag[x]);
			if(rc) cover(rc,tag[x]);
			tag[x] = 0;
		}
	}

	inline void rotate(int x){
		int y = f[x],z = f[y],k = ch[y][1]==x,w = ch[x][!k];
		if(nroot(y)) ch[z][ch[z][1]==y] = x;f[x] = z;
		ch[x][!k] = y;f[y] = x;
		ch[y][k] = w;if(w) f[w] = y;
	}

	inline void pd(int x){
		if(nroot(x)) pd(f[x]);
		pushdown(x);
	}

	inline void splay(int x){
		int y = x,z;
		pd(x);
		while(nroot(x)){
			y = f[x],z = f[y];
			if(nroot(y)) rotate((ch[z][1]==y)^(ch[y][1]==x)?x:y);
			rotate(x);
		}
	}

	inline void access(int x){
		for(int y = 0;x;x = f[y=x]){
			splay(x);rc = y;
		}
	}

	inline void link(int x,int y){
		f[x] = y;access(y);
		splay(y);
		cover(y,val[x]);
	}

	inline void cut(int x){
		access(x);splay(x);cover(lc,-val[x]);
		f[lc] = 0;lc = 0;
	}
}T;

struct SAM{
	int ch[MAXN][26],fail[MAXN],len[MAXN];
	int tot,lst;
	SAM(){tot = lst = 1;}

	inline void copy(int x,int y){
		FOR(i,0,25) ch[x][i] = ch[y][i];fail[x] = fail[y];len[x] = len[y];
	}

	inline void insert(int c){
		int p = lst,np = lst = ++tot;T.val[np] = 1;
		len[np] = len[p]+1;
		while(p&&!ch[p][c]) ch[p][c] = np,p = fail[p];
		if(!p) fail[np] = 1,T.link(np,fail[np]);
		else{
			int q = ch[p][c];
			if(len[q] == len[p]+1) fail[np] = q,T.link(np,fail[np]);
			else{
				int nq = ++tot;copy(nq,q);T.link(nq,fail[nq]);
				len[nq] = len[p]+1;
				fail[q] = fail[np] = nq;
				T.cut(q);
				T.link(np,fail[np]);T.link(q,fail[q]);
				while(p&&ch[p][c]==q) ch[p][c] = nq,p = fail[p];
			}
		}
	}

	inline int query(char str[]){
		int len = strlen(str);
		int v = 1;
		FOR(i,0,len-1){
			int x = str[i]-'A';
			if(!ch[v][x]) return 0;
			v = ch[v][x];
		}
		T.pd(v);
		return T.val[v];
	}
}sam;

char str[MAXN];
int q;
char opt[MAXN];

inline void Decode(char str[],int mask){
	int n = strlen(str);
	FOR(i,0,n-1){
		mask = (mask*131+i)%n;
		std::swap(str[i],str[mask]);
	}
}
int mask = 0;
int main(){
	scanf("%d%s",&q,str+1);
	int n = strlen(str+1);
	FOR(i,1,n) sam.insert(str[i]-'A');
	FOR(i,1,q){
		scanf("%s%s",opt,str);Decode(str,mask);
		if(opt[0] == 'A'){
			int n = strlen(str);
			FOR(i,0,n-1) sam.insert(str[i]-'A');
		}
		else{
			int res = sam.query(str);
			mask ^= res;printf("%d\n",res);
		}
	}
	return 0;
}