#include<bits/stdc++.h>

#define fi first
#define se second
#define U unsigned
#define P std::pair<LL,LL>
#define LL long long
#define pb push_back
#define MP std::make_pair
#define all(x) x.begin(),x.end()
#define CLR(i,a) memset(i,a,sizeof(i))
#define FOR(i,a,b) for(int i = a;i <= b;++i)
#define ROF(i,a,b) for(int i = a;i >= b;--i)
#define DEBUG(x) std::cerr << #x << '=' << x << std::endl
#define int LL
const int MAXN = 4e5 + 5;

struct Node{
	int x,w,c;
	Node(int x=0,int w=0,int c=0) : x(x),w(w),c(c) {}
	bool operator < (const Node &t) const {
		if(x == t.x) return w < t.w;
		return x < t.x;
	}
}a[MAXN];
int n,m,N;
std::priority_queue<P,std::vector<P>,std::greater<P> > q1,q2;
signed main(){
	// freopen("ex_hole3.in","r",stdin);
	scanf("%lld%lld",&n,&m);N = n+m;int sm = 0;
	FOR(i,1,n) scanf("%lld",&a[i].x),a[i].w = 1e9+9;
	FOR(i,1,m) scanf("%lld%lld%lld",&a[i+n].x,&a[i+n].w,&a[i+n].c),sm += a[i+n].c;
	a[++N] = Node(-1e9,0,1e9);
	if(sm < n){
		puts("-1");return 0;
	}
	std::sort(a+1,a+N+1);
	int ans = 0;
	FOR(i,1,N){
		if(a[i].w == 1e9+9){
			// DEBUG(q2.size());
			P v = q2.top();q2.pop();
			ans += v.fi+a[i].x;v.se--;
			if(v.se) q2.push(v);
			q1.push(MP(-v.fi-2*a[i].x,1));
		}
		else{
			int t = a[i].c;//DEBUG(q1.size());
			while(!q1.empty() && t){
				if(q1.top().fi+a[i].w+a[i].x >= 0) break;
				P v = q1.top();q1.pop();
				int num = std::min(t,v.se);t -= num;v.se -= num;
				ans += num*(v.fi+a[i].w+a[i].x);
				if(v.se) q1.push(v);
				q2.push(MP(-v.fi-2*a[i].x,num));
			}
			// DEBUG(a[i].c-t);
			if(a[i].c-t) q1.push(MP(-a[i].w-a[i].x,a[i].c-t));
			if(t) q2.push(MP(-a[i].x+a[i].w,t));
		}
	}
	// DEBUG(q1.size());DEBUG(q2.size());
	printf("%lld\n",ans);
	return 0;
}