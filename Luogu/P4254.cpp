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
	double a,b;
};

inline double intersect(Node A,Node B){
	return 1.0*(B.b-A.b)/(A.a-B.a);
}

Node sm[MAXN<<2];
#define lc ((x)<<1)
#define rc ((x)<<1|1)

inline double w(Node a,int x){
	return a.a*x+a.b;
}

inline void modify(int x,int l,int r,Node d){
	if(w(sm[x],l) >= w(d,l) && w(sm[x],r) >= w(d,r)){
		return;
	}
	if(w(sm[x],l) <= w(d,l) && w(sm[x],r) <= w(d,r)){
		sm[x] = d;return;
	}
	int mid = (l + r) >> 1;
	if(d.a >= sm[x].a){
		if(w(d,mid) >= w(sm[x],mid)) sm[x] = d,modify(lc,l,mid,d);
		else modify(rc,mid+1,r,d);
	}
	else{
		if(w(d,mid) >= w(sm[x],mid)) sm[x] = d,modify(rc,mid+1,r,d);
		else modify(lc,l,mid,d);
	}
}

inline double query(int x,int l,int r,int p){
	if(l == r) return w(sm[x],p);
	int mid = (l + r) >> 1;
	if(p <= mid) return std::max(query(lc,l,mid,p),w(sm[x],p));
	else return std::max(query(rc,mid+1,r,p),w(sm[x],p));
}

int main(){
	int T;scanf("%d",&T);
	int n = 50000;
	while(T--){
		char str[123];scanf("%s",str+1);
		if(str[1] == 'P'){
			Node d;scanf("%lf%lf",&d.a,&d.b);
			modify(1,1,n,d);
		}
		else{
			int x;scanf("%d",&x);printf("%d\n",(int)(query(1,1,n,x)/100.0));
		}
	}
	return 0;
}