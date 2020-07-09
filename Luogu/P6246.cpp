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
#define FOR(i,a,b) for(register int i = a;i <= b;++i)
#define ROF(i,a,b) for(register int i = a;i >= b;--i)
#define DEBUG(x) std::cerr << #x << '=' << x << std::endl

const int MAXN = 5e5 + 5;
LL sm[MAXN];
int n,k;
LL f[MAXN];int g[MAXN];

inline char nc(){
	#define SIZE 1000000+3
	static char buf[SIZE],*p1 = buf+SIZE,*p2 = buf+SIZE;
	if(p1 == p2){
		p1 = buf;p2 = buf+fread(buf,1,SIZE,stdin);
		if(p1 == p2) return -1;
	}
	return *p1++;
	#undef SIZE
}

template <typename T>
inline void read(T &x){
	x = 0;int flag = 0;char ch = nc();
	while(!isdigit(ch)){
		if(ch == '-') flag = 1;
		ch = nc();
	}
	while(isdigit(ch)){
		x = (x<<1) + (x<<3) + (ch^'0');
		ch = nc();
	}
	if(flag) x = -x;
}


inline LL w(int l,int r){//(l,r]
	int mid = (l + r + 1) >> 1;
	LL now = sm[mid]-sm[mid-1];
	return f[l]+sm[l]+sm[r]-2*sm[mid]+now*(2*mid-l-r);
}

struct Node{
	int l,r,v;
	Node(int l=0,int r=0,int v=0) : l(l),r(r),v(v) {}
};
std::deque<Node> q;

inline int chk(LL k){
	CLR(f,0x3f);CLR(g,0);
	f[0] = 0;q.clear();
	q.pb(Node(1,n,0));
	FOR(i,1,n){
		while(!q.empty() && q.front().r < i) q.pop_front();
		f[i] = w(q.front().v,i)+k;g[i] = g[q.front().v]+1;
		int now = n+1;
		while(!q.empty() && w(q.back().v,q.back().l) >= w(i,q.back().l)) now = q.back().l,q.pop_back();
		if(!q.empty()){
			int l = q.back().l,r = q.back().r;
			while(l <= r){
				int mid = (l + r) >> 1;
				if(w(q.back().v,mid) >= w(i,mid)) now = mid,r = mid-1;
				else l = mid+1;
			}
//            DEBUG(q.back().r);
			q.back().r = now-1;
//            DEBUG(now-1);
		}
		if(now != n+1) q.pb(Node(now,n,i));
	}
	return g[n];
}

signed main(){
	read(n);read(k);
	FOR(i,1,n) read(sm[i]),sm[i] += sm[i-1];
	LL l = 0,r = 1e15,ans = -1;
//    DEBUG(chk(0));
//    exit(0);
	while(l <= r){
		LL mid = (l + r) >> 1;
		if(chk(mid) >= k) ans = f[n]-k*mid,l = mid+1;
		else r = mid-1;
	}
	printf("%lld\n",ans);
//    DEBUG(g[n]);
//    assert(g[n]==k);
	return 0;
}
/*
 * [l,r] 一定放在中间最好 所以考虑将其分段
 * f[i][j] 考虑了前i个分成j段
 * f[i][j] = f[k][j-1]+w(k+1,i)
 */
