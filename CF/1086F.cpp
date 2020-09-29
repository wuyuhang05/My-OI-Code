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

const int ha = 998244353;
const int inv2 = 499122177;
const int inv6 = 166374059;
const int MAXN = 300+5;
std::vector<LL> Sx,Sy;

namespace DS{
	int sm[MAXN<<2],tag[MAXN<<2];
	#define lc ((x)<<1)
	#define rc ((x)<<1|1)
	
	inline void modify(int x,int l,int r,int L,int R,int d){
		int len = Sy[r]-Sy[l-1];
		if(l == L && r == R){
			tag[x] += d;
			sm[x] = tag[x] ? len : (l==r?0:(sm[lc]+sm[rc])%ha);
			return;
		}
		int mid = (l + r) >> 1;
		if(R <= mid) modify(lc,l,mid,L,R,d);
		else if(L > mid) modify(rc,mid+1,r,L,R,d);
		else modify(lc,l,mid,L,mid,d),modify(rc,mid+1,r,mid+1,R,d);
		sm[x] = tag[x]?len:(l==r?0:(sm[lc]+sm[rc])%ha);
	}
}
using DS::modify;

int x[MAXN],y[MAXN],n;

inline void add(int &x,int y){
	x += y;if(x >= ha) x -= ha;
}

struct Node{
	int x1,y1,x2,y2;//(x1,y1) <= (x2,y2)
	Node(int x1=0,int y1=0,int x2=0,int y2=0) : x1(x1),y1(y1),x2(x2),y2(y2) {}
}a[MAXN];

std::vector<std::pair<P,int> > G[MAXN];

inline int f(int k){
	Sx.clear();Sy.clear();
	FOR(i,1,n){
		a[i] = Node(x[i]-k,y[i]-k,x[i]+k+1,y[i]+k+1);
		Sx.pb(x[i]-k);Sy.pb(y[i]-k);Sx.pb(x[i]+k+1);Sy.pb(y[i]+k+1);
	}
	std::sort(all(Sx));Sx.erase(std::unique(all(Sx)),Sx.end());
	std::sort(all(Sy));Sy.erase(std::unique(all(Sy)),Sy.end());
	int m = Sx.size(),M = Sy.size();
	FOR(i,0,m+1) G[i].clear();
	FOR(i,1,n){
		a[i].x1 = std::lower_bound(all(Sx),a[i].x1)-Sx.begin()+1;
		a[i].x2 = std::lower_bound(all(Sx),a[i].x2)-Sx.begin()+1;
		a[i].y1 = std::lower_bound(all(Sy),a[i].y1)-Sy.begin()+1;
		a[i].y2 = std::lower_bound(all(Sy),a[i].y2)-Sy.begin()+1;
		G[a[i].x1].pb(MP(MP(a[i].y1,a[i].y2),1));
		G[a[i].x2].pb(MP(MP(a[i].y1,a[i].y2),-1));
	}
	Sy.pb(Sy.back());
	CLR(DS::sm,0);CLR(DS::tag,0);
	int ans = 0;
	FOR(i,1,m){
		int t = (Sx[i-1]-Sx[std::max(i-2,0)])%ha;
		add(ans,1ll*t*DS::sm[1]%ha);
		for(auto x:G[i]) modify(1,1,M,x.fi.fi,x.fi.se-1,x.se);
	}
	return ans;
}

inline int sm2(int n){
	int res = 0;if(n < 0) return 0;
	if(n <= 5){
		FOR(i,1,n) add(res,i*i);
	}
	else{
		res = 1ll*n*(n+1)%ha*(2ll*n+1)%ha*inv6%ha;
	}
	return res;
}

inline int sm(int n){
	int res = 0;if(n < 0) return 0;
	if(n <= 5){
		FOR(i,1,n) add(res,i);
	}
	else{
		res = 1ll*n*(n+1)%ha*inv2%ha;
	}
	return res;
}

inline int sm(int l,int r){
	return (sm(r)+ha-sm(l-1))%ha;
}

inline int sm2(int l,int r){
	return (sm2(r)+ha-sm2(l-1))%ha;
}

int main(){
	int t;scanf("%d%d",&n,&t);
	FOR(i,1,n) scanf("%d%d",x+i,y+i);
	std::vector<int> part;part.pb(0);part.pb(t);
	FOR(i,1,n){
		FOR(j,i+1,n){
			int d = std::max(std::abs(x[i]-x[j]),std::abs(y[i]-y[j]));
			d = (d+1)/2;
			if(d >= t) continue;
			part.pb(d);
		}
	}
	std::sort(all(part));part.erase(std::unique(all(part)),part.end());
	int ans = 0;
	FOR(i,1,(int)part.size()-1){
		int l = part[i-1],r = part[i]-1;
		if(r-l+1 <= 3){
			FOR(k,l,r) add(ans,f(k));
			continue;
		}
		int x[3],y[3];
		FOR(j,0,2) y[j] = f(x[j]=l+j);
		int a = 1ll*y[0]*inv2%ha;
		add(a,ha-y[1]);add(a,1ll*y[2]*inv2%ha);
		int b = 1ll*y[0]*inv2%ha*(x[1]+x[2])%ha;
		add(b,ha-1ll*y[1]*((x[0]+x[2])%ha)%ha);
		add(b,1ll*y[2]*inv2%ha*(x[1]+x[0])%ha);
		b = ha-b;
		
		int c = 1ll*x[1]*x[2]%ha*y[0]%ha*inv2%ha;
		add(c,ha-1ll*x[0]*x[2]%ha*y[1]%ha);
		add(c,1ll*x[0]*x[1]%ha*y[2]%ha*inv2%ha);
		add(ans,1ll*sm2(l,r)*a%ha);
		add(ans,1ll*sm(l,r)*b%ha);
		add(ans,1ll*(r-l+1)*c%ha);
	}
	add(ans,ha-1ll*t*f(t)%ha);
	ans = (ha-ans)%ha;
	printf("%d\n",ans);
	return 0;
}
/*
设 f(i) 表示 i 时间有多少个格子着火了
答案就是 tf(t)-\sum_{i=0}^{t-1}f(i)
单次询问 f(i) 是可以求矩阵面积并的,但是你不能询问1e8次
考虑用容斥原理将矩形面积并变成交
观察一个子集 发现只有在某两个矩形由不交变成相交的时候才会分段
所以只有 n^2 段 插值 每一段需要做3/4次矩形面积并
矩形面积并就是离散化后排序 支持区间加删线段 全局查询 修改到对应线段即可
*/