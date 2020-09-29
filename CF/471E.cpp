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

const int MAXN = 5e5 + 5;
int n;

struct Node{
	int opt,d,l,r,x;
	Node(int opt=0,int d=0,int l=0,int r=0,int x=0) : opt(opt),d(d),l(l),r(r),x(x) {}
	
	bool operator < (const Node &t) const {
		return opt < t.opt;
	}
};

std::vector<Node> col,row;
std::vector<int> S;
std::tuple<int,int,int,int> a[MAXN];
std::vector<Node> G[MAXN];

struct BIT{
	#define lowbit(x) ((x)&(-(x)))
	int tree[MAXN];
	
	inline void add(int pos,int x){
		++pos;
		while(pos < MAXN){
			tree[pos] += x;
			pos += lowbit(pos);
		}
	}
	
	inline int query(int pos){
		int res = 0;++pos;
		while(pos){
			res += tree[pos];
			pos -= lowbit(pos);
		}
		return res;
	}
}bit;

int main(){
	scanf("%d",&n);
	LL edge = 0,node = 0;
	FOR(i,1,n){
		int x1,y1,x2,y2;scanf("%d%d%d%d",&x1,&y1,&x2,&y2);
		a[i] = {x1,y1,x2,y2};
		edge += std::abs(x1-x2);
		edge += std::abs(y1-y2);
		S.pb(x1);S.pb(y1);S.pb(x2);S.pb(y2);
	}
	node = edge;
	std::sort(all(S));S.erase(std::unique(all(S)),S.end());
	FOR(i,1,n){
		int x1,y1,x2,y2;
		std::tie(x1,y1,x2,y2) = a[i];
		x1 = std::lower_bound(all(S),x1)-S.begin()+1;
		x2 = std::lower_bound(all(S),x2)-S.begin()+1;
		y1 = std::lower_bound(all(S),y1)-S.begin()+1;
		y2 = std::lower_bound(all(S),y2)-S.begin()+1;
		if(y1 == y2){
			G[x1].pb(Node(1,1,0,0,y1));
			G[x2+1].pb(Node(1,-1,0,0,y1));
		}
		else{
			assert(x1==x2);
			if(y1 >y2) std::swap(y1,y2);
			G[x1].pb(Node(2,1,y1,y2,0));
		}
	}
	int M = S.back()+1;
	FOR(i,1,M){
		std::sort(all(G[i]));
		for(auto x:G[i]){
			if(x.opt == 1){
				bit.add(x.x,x.d);
			}
			if(x.opt == 2){
				node -= bit.query(x.r)-bit.query(x.l-1);
			}
		}
	}
	printf("%lld\n",edge-node+1);
	return 0;
}