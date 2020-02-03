/*
先考虑部分分:l=1,r=|S|
然后考虑如果子串可以重复计算怎么做
我们可以枚举ION2018 的每一个前缀 找到在 ION2017 SAM 中的匹配长度x 对答案贡献 i-x
现在我们需要去重 我们对 ION2018 也建 SAM,在 INO2018SAM 上定位到点 相当于这个点到根的所有路径都可能有贡献 暴力跳到根挨个统计路径上有多少个当前前缀的后缀被计算了就好了 标记一下经过的
注意我们跳到不能更新就停复杂度才是对的
然后我们现在考虑 l,r 任意
相当于你建出 SAM 但是这个点在[l,r]上不一定存在 我们怎么判断是否存在呢?
我们只需要维护处所有点的 endpos 集合就好了 可以用线段树合并
然后走之前判断一下这个点在[l,r]上存在与否就可以了
注意在跳 fail 时首先应该尝试缩小 len,缩小到不能缩小再跳
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
int tax[MAXN],sa[MAXN];
struct SAM{
	int ch[MAXN][26],fail[MAXN],len[MAXN],f[MAXN];
	int tot,las;

	inline void clr(){
		FOR(i,1,tot){
			fail[i] = len[i] = 0;
			FOR(j,0,25) ch[i][j] = 0;
		}
		tot = las = 1;
	}

	inline void copy(int x,int y){
		FOR(i,0,25) ch[x][i] = ch[y][i];
		fail[x] = fail[y];len[x] = len[y];
	}

	inline int work(int p,int c){
		int q = ch[p][c],nq = ++tot;
		copy(nq,q);
		len[nq] = len[p]+1;fail[q] = nq;
		while(p&&ch[p][c]==q) ch[p][c] = nq,p = fail[p];
		return nq;
	}

	inline int insert(int c){
		int p = las,np = las = ++tot;
		len[np] = len[p]+1;
		while(p&&!ch[p][c]) ch[p][c] = np,p = fail[p];
		if(!p) fail[np] = 1;
		else fail[np] = len[ch[p][c]]==len[p]+1?ch[p][c]:work(p,c);
		return np;
	}
}sam1,sam2;

struct Node{
	int sm;
	int lc,rc;
}t[MAXN<<4];
int tot,root[MAXN];

inline void update(int &x,int l,int r,int p){
	t[x=++tot].sm++;
	if(l == r) return;
	int mid = (l + r) >> 1;
	if(p <= mid) update(t[x].lc,l,mid,p);
	else update(t[x].rc,mid+1,r,p);
}

inline int query(int x,int l,int r,int L,int R){
	if(!x) return 0;
	if(L > R) return 0;
	if(l == L && r == R) return t[x].sm;
	int mid = (l + r) >> 1;
	if(R <= mid) return query(t[x].lc,l,mid,L,R);
	if(L > mid) return query(t[x].rc,mid+1,r,L,R);
	return query(t[x].lc,l,mid,L,mid)+query(t[x].rc,mid+1,r,mid+1,R);
}

inline int merge(int x,int y){
	int v = ++tot;
	if(!x || !y) return x+y;
	t[v].sm = t[x].sm+t[y].sm;
	t[v].lc = merge(t[x].lc,t[y].lc);
	t[v].rc = merge(t[x].rc,t[y].rc);
	return v;
}

char str[MAXN];
int n,q;

int main(){
	scanf("%s",str+1);n = strlen(str+1);
	scanf("%d",&q);sam1.clr();
	FOR(i,1,n){
		int p = sam1.insert(str[i]-'a');
		update(root[p],1,n,i);
	}
	FOR(i,1,sam1.tot) tax[sam1.len[i]]++;
	FOR(i,1,n) tax[i] += tax[i-1];
	FOR(i,1,sam1.tot) sa[tax[sam1.len[i]]--] = i;
	ROF(i,sam1.tot,1) root[sam1.fail[sa[i]]] = merge(root[sam1.fail[sa[i]]],root[sa[i]]);
	while(q--){
		scanf("%s",str+1);int len = strlen(str+1);sam2.clr();
		FOR(i,1,len) sam2.insert(str[i]-'a');
		FOR(i,1,sam2.tot) sam2.f[i] = sam2.len[i];
		int u1 = 1,u2 = 1;int l,r;scanf("%d%d",&l,&r);
		int now = 0;LL ans = 0;
		FOR(i,1,len){
			int c = str[i]-'a';
			u2 = sam2.ch[u2][c];
			if(sam1.ch[u1][c]&&query(root[sam1.ch[u1][c]],1,n,l+now,r))
				now++,u1 = sam1.ch[u1][c];
			else{
				while(u1&&!(sam1.ch[u1][c]&&query(root[sam1.ch[u1][c]],1,n,l+now,r))){
					if(!now) {u1=0;break;}
					now--;
					if(now == sam1.len[sam1.fail[u1]]) u1 = sam1.fail[u1];
				}
				if(!u1) now = 0,u1 = 1;
				else u1 = sam1.ch[u1][c],++now;
			}
			int p = u2;
			while(p){
				if(now <= sam2.len[sam2.fail[p]]) ans += sam2.f[p]-sam2.len[sam2.fail[p]],sam2.f[p] = sam2.len[sam2.fail[p]];
				else{
					ans += sam2.f[p]-now;sam2.f[p] = now;
					break;
				}
				p = sam2.fail[p];
			}
		}
		printf("%lld\n",ans);
	}
	return 0;
}