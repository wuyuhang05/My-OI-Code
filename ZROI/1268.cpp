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
const int ha = 998244353;

struct Node{
	int x0,y0,x1,y1;
	int yy0,yy1;
	int ry0,ry1;

	inline void read(){
		scanf("%d%d%d%d",&x0,&y0,&x1,&y1);
	}
}A[MAXN];

std::vector<int> S;
int n;
int f[MAXN];

struct BIT{
	#define lowbit(x) ((x)&(-(x)))
	int tree[MAXN];std::vector<int> Opt;

	inline void add(int pos,int x){
		Opt.pb(pos);
		while(pos < MAXN){
			(tree[pos] += x) %= ha;
			pos += lowbit(pos);
		}
	}

	inline int query(int pos){
		int res = 0;
		while(pos){
			(res += tree[pos]) %= ha;
			pos -= lowbit(pos);
		}
		return res;
	}

	inline void clr(int pos){
		while(pos < MAXN){
			tree[pos] = 0;
			pos += lowbit(pos);
		}
	}

	inline void clear(){
		for(auto x:Opt) clr(x);
		Opt.clear();
	}
}sma,smb,smab,smf;

struct NODE{
	int x,y,d,opt,id,pos;
	NODE(int x=0,int y=0,int d=0,int opt=0,int id=0,int pos=0) : x(x),y(y),d(d),opt(opt),id(id),pos(pos) {}

	inline bool operator < (const NODE &t) const {
		if(x != t.x) return x < t.x;
		return opt < t.opt;
	}
};
std::vector<NODE> G;

inline void cdq(int l,int r){
	if(l == r){
		(f[l] += 1) %= ha;return;
	}
	int mid = (l + r) >> 1;
	cdq(l,mid);G.clear();
	FOR(i,l,mid) G.pb(NODE(A[i].x0,A[i].y0,f[i],1,i,A[i].ry0)),G.pb(NODE(A[i].x1+1,A[i].y0,ha-f[i],1,i,A[i].ry0)),
	G.pb(NODE(A[i].x0,A[i].y1+1,ha-f[i],1,i,A[i].yy1)),G.pb(NODE(A[i].x1+1,A[i].y1+1,f[i],1,i,A[i].yy1));
	FOR(i,mid+1,r) G.pb(NODE(A[i].x1,A[i].y1,1,2,i,A[i].ry1)),G.pb(NODE(A[i].x0-1,A[i].y1,-1,2,i,A[i].ry1)),
	G.pb(NODE(A[i].x1,A[i].y0-1,-1,2,i,A[i].yy0)),G.pb(NODE(A[i].x0-1,A[i].y0-1,1,2,i,A[i].yy0));
	std::sort(all(G));
	sma.clear();smb.clear();smab.clear();smf.clear();
	for(auto x:G){
		int p = x.pos;
		if(x.opt == 1){
			smf.add(p,x.d);
			sma.add(p,1ll*x.x*x.d%ha);
			smb.add(p,1ll*x.y*x.d%ha);
			smab.add(p,1ll*x.x*x.y%ha*x.d%ha);
		}
		else{
			int res = 0;
			res += 1ll*(x.x+1)*(x.y+1)%ha*smf.query(p)%ha;
			(res += smab.query(p))%=ha;
			res = (res+ha-1ll*(x.x+1)*smb.query(p)%ha)%ha;
			res = (res+ha-1ll*(x.y+1)*sma.query(p)%ha)%ha;
			if(x.d == -1) res = ha-res;
			(f[x.id] += res) %= ha;
		}
	}
	cdq(mid+1,r);
}

int main(){
	scanf("%d",&n);
	FOR(i,1,n) A[i].read(),S.pb(A[i].y0),S.pb(A[i].y1),S.pb(A[i].y1+1),S.pb(A[i].y0-1);
	std::sort(all(S));S.erase(std::unique(all(S)),S.end());
	FOR(i,1,n) 
	A[i].yy0 = std::lower_bound(all(S),A[i].y0-1)-S.begin()+1,
	A[i].yy1 = std::lower_bound(all(S),A[i].y1+1)-S.begin()+1,
	A[i].ry0 = std::lower_bound(all(S),A[i].y0)-S.begin()+1,
	A[i].ry1 = std::lower_bound(all(S),A[i].y1)-S.begin()+1;
	cdq(1,n);
	int ans = 0;FOR(i,1,n) (ans += f[i]) %= ha;
	printf("%d\n",ans);
	return 0;
}