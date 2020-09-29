#include <bits/stdc++.h>

#define fi first
#define se second
#define db double
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

const int MAXN = 1e5 + 5;

struct Node{
	int mx,ps;
	
	Node(int mx=0,int ps=-1) : mx(mx),ps(ps) {}
	
	friend Node operator + (const Node &x,const Node &y){
		Node res;
		if(x.mx >= y.mx) res.mx = x.mx,res.ps = x.ps;
		else res.mx = y.mx,res.ps = y.ps;
		return res;
	}
}sm[MAXN<<5];
// 最大值,非0位置个数
int lc[MAXN<<5],rc[MAXN<<5],tot;

inline Node query(int x,int l,int r,int L,int R){
	if(!x) return Node();
	if(l == L && r == R) return sm[x];
	int mid = (l + r) >> 1;
	if(R <= mid) return query(lc[x],l,mid,L,R);
	if(L > mid) return query(rc[x],mid+1,r,L,R);
	return query(lc[x],l,mid,L,mid)+query(rc[x],mid+1,r,mid+1,R);
}

inline void update(int &x,int l,int r,int p){
	if(!x) x = ++tot;
	if(l == r){
		sm[x].mx++;sm[x].ps = l;
		return;
	}
	int mid = (l + r) >> 1;
	if(p <= mid) update(lc[x],l,mid,p);
	else update(rc[x],mid+1,r,p);
	sm[x] = sm[lc[x]]+sm[rc[x]];
}

inline int merge(int x,int y,int l,int r){
	if(!x || !y) return x|y;
	int now = ++tot;
	if(l == r){
		sm[now] = sm[x];
		sm[now].mx += sm[y].mx;
		return now;
	}
	int mid = (l + r) >> 1;
	lc[now] = merge(lc[x],lc[y],l,mid);
	rc[now] = merge(rc[x],rc[y],mid+1,r);
	sm[now] = sm[lc[now]]+sm[rc[now]];
	return now;
}

int ch[MAXN][26],fail[MAXN],len[MAXN],_tot = 1,las = 1;
int rt[MAXN];

inline void copy(int x,int y){
	FOR(i,0,25) ch[x][i] = ch[y][i];
	fail[x] = fail[y];len[x] = len[y];
}

inline int work(int p,int c){
	int q = ch[p][c],nq = ++_tot;
	copy(nq,q);len[nq] = len[p]+1;fail[q] = nq;
	for(;p&&ch[p][c]==q;p=fail[p]) ch[p][c] = nq;
	return nq;
}

inline int insert(int p,int c){
	int q = ch[p][c];
	if(q){
		if(len[q] == len[p]+1) return q;
		return work(p,c);
	}
	int np = ++_tot;len[np] = len[p]+1;
	for(;p&&!ch[p][c];p=fail[p]) ch[p][c] = np;
	if(!p) fail[np] = 1;
	else{
		q = ch[p][c];
		if(len[q] == len[p]+1) fail[np] = q;
		else fail[np] = work(p,c);
	}
	return np;
}

const int MAXK = 5e5 + 5;

char S[MAXK],str[MAXN];
int n;
std::vector<int> G[MAXN];
const int MAXM = 16;
int f[MAXN][MAXM+1],m;

inline void dfs(int v){
	FOR(i,1,MAXM) f[v][i] = f[f[v][i-1]][i-1];
	for(auto x:G[v]){
		f[x][0] = v;dfs(x);
		rt[v] = merge(rt[v],rt[x],1,m);
	}
}

int to[MAXK],le[MAXK];

int main(){
	scanf("%s",S+1);n = strlen(S+1);
	scanf("%d",&m);
	FOR(i,1,m){
		las = 1;
		scanf("%s",str+1);int len = strlen(str+1);
		FOR(j,1,len) las = insert(las,str[j]-'a'),update(rt[las],1,m,i);
	}
	// DEBUG(query(rt[12],1,m,1,2).mx);
	// exit(0);
	FOR(i,2,_tot) G[fail[i]].pb(i);
	// for(auto x:G[81]){
		// DEBUG(x);
		// DEBUG(sm[rt[x]].mx);
		// for(auto y:G[x]){
			// DEBUG(y);
			// DEBUG(sm[rt[y]].mx);
		// }
	// }
	// exit(0);
	dfs(1);to[0] = 1;
	int now=1,len = 0;
	FOR(i,1,n){
		int c = S[i]-'a';
		if(ch[now][c]) len++,now = ch[now][c];
		else{
			while(now && !ch[now][c]) now = fail[now];
			if(!now) now = 1,len = 0;
			else len = ::len[now]+1,now = ch[now][c];
		}
		to[i] = now;le[i] = len;
	}
	int q;scanf("%d",&q);
	while(q--){
		int l,r,pl,pr;scanf("%d%d%d%d",&l,&r,&pl,&pr);
		int v = to[pr];
		if(le[pr] < pr-pl+1){
			printf("%d %d\n",l,0);
			continue;
		}
		ROF(i,MAXM,0){
			if(::len[f[v][i]] >= pr-pl+1){
				v = f[v][i];
			}
		}
		Node ans = query(rt[v],1,m,l,r);
		if(ans.ps == -1) printf("%d %d\n",l,0);
		else printf("%d %d\n",ans.ps,ans.mx);
	}
	return 0;
}