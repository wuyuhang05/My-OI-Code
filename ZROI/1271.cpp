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
#define P std::pair<int,int>
#define LL long long
#define pb push_back
#define MP std::make_pair
#define all(x) x.begin(),x.end()
#define CLR(i,a) memset(i,a,sizeof(i))
#define FOR(i,a,b) for(int i = a;i <= b;++i)
#define ROF(i,a,b) for(int i = a;i >= b;--i)
#define DEBUG(x) std::cerr << #x << '=' << x << std::endl

const int MAXN = 5e5 + 5;

int ch[MAXN][26],tot,dfn[MAXN],sz[MAXN],ts;
std::vector<int> G[MAXN],R[MAXN],D[MAXN];
std::vector<P> q[MAXN];
int ans[MAXN];
int pos[MAXN][3];
int lc[MAXN<<5],rc[MAXN<<5],sm[MAXN<<5],tott;

inline void insert(int prev,int &v,int l,int r,int p){
	v = ++tott;lc[v] = lc[prev];rc[v] = rc[prev];sm[v] = sm[prev]+1;
	if(l == r) return;
	int mid = (l + r) >> 1;
	if(p <= mid) insert(lc[prev],lc[v],l,mid,p);
	else insert(rc[prev],rc[v],mid+1,r,p);
}

inline int query(int x,int y,int l,int r,int L,int R){
	if(l == L && r == R) return sm[y]-sm[x];
	int mid = (l + r) >> 1;
	if(R <= mid) return query(lc[x],lc[y],l,mid,L,R);
	if(L > mid) return query(rc[x],rc[y],mid+1,r,L,R);
	return query(lc[x],lc[y],l,mid,L,mid)+query(rc[x],rc[y],mid+1,r,mid+1,R);
}

inline bool cmp(int x,int y){
	return dfn[pos[x][1]] < dfn[pos[y][1]];
}

struct DS{
	int rt;

	inline void insert(char str[],int id,int j){
		int len = strlen(str+1),v = rt;G[v].pb(id);
		FOR(i,1,len){
			int x = str[i]-'a';
			if(!ch[v][x]) ch[v][x] = ++tot;
			v = ch[v][x];G[v].pb(id);
		}
		pos[id][j] = v;
	}

	inline void dfs(int v){
		dfn[v] = ++ts;sz[v] = 1;
		FOR(i,0,25){
			if(!ch[v][i]) continue;
			dfs(ch[v][i]);sz[v] += sz[ch[v][i]];
		}
	}

	inline void DFS(int v){
		std::sort(all(G[v]),cmp);R[v].pb(0);
		for(auto x:G[v]) D[v].pb(dfn[pos[x][1]]);
		for(auto x:G[v]){
			R[v].pb(0);int t = (int)R[v].size()-1;
			::insert(R[v][t-1],R[v][t],1,tot,dfn[pos[x][2]]);
		}
		FOR(i,0,25){
			if(!ch[v][i]) continue;
			DFS(ch[v][i]);
		}
	}

	inline void build(){
		ts = 0;dfs(rt);
	}
}trie[3];

int n;
char str[MAXN];
int pt[3][MAXN],tp[3];

int main(){
	scanf("%d",&n);FOR(i,0,2) pt[i][tp[i]=1] = trie[i].rt = i+1;
	tot = 3;
	FOR(i,1,n){
		FOR(j,0,2) scanf("%s",str+1),trie[j].insert(str,i,j);
	}
	FOR(i,0,2) trie[i].build();
	trie[0].DFS(trie[0].rt);
	int q;scanf("%d",&q);
	while(q--){
		scanf("%s",str+1);
		if(str[1] == '+'){
			int x;
			scanf("%d%s",&x,str+1);--x;
			++tp[x];pt[x][tp[x]] = ch[pt[x][tp[x]-1]][str[1]-'a'];
		}
		else{
			int x;scanf("%d",&x);--x;
			--tp[x];
		}
		int v = pt[0][tp[0]];//DEBUG(G[v].size());DEBUG(v);
		// for(auto x:G[v]) DEBUG(x),printf("%d %d\n",dfn[pos[x][1]],dfn[pos[x][2]]);
		// FOR(i,1,2) DEBUG(dfn[pt[i][tp[i]]]),DEBUG(dfn[pt[i][tp[i]]]+sz[pt[i][tp[i]]]-1);	
		if(!pt[0][tp[0]] || !pt[1][tp[1]] || !pt[2][tp[2]]) puts("0");
		else{
			int l = std::lower_bound(all(D[v]),dfn[pt[1][tp[1]]])-D[v].begin()+1,r = std::upper_bound(all(D[v]),dfn[pt[1][tp[1]]]+sz[pt[1][tp[1]]]-1)-D[v].begin()+1;
			if(l > r) puts("0");
			else if(l > G[v].size()) puts("0");
			else{
				r = std::min(r,(int)R[v].size()-1);
				while(D[v][r-1] > dfn[pt[1][tp[1]]]+sz[pt[1][tp[1]]]-1) r--;
				// DEBUG(l);DEBUG(r);
				printf("%d\n",query(R[v][l-1],R[v][r],1,tot,dfn[pt[2][tp[2]]],dfn[pt[2][tp[2]]]+sz[pt[2][tp[2]]]-1));
			}
		}
	}
	return 0;
}