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

struct Node{
	LL v[2];
	Node(LL x=0,LL y=0){
		v[0] = x;v[1] = y;
	}
	inline LL& operator [] (const int &n){return v[n];}
	
	friend Node operator + (Node x,Node y){
		return Node(
		(x[1]&y[1])|(x[0]&(~(y[0]|y[1])))|(y[0]&(~(x[0]|x[1]))),
		(x[0]&y[0])|(x[1]&(~(y[0]|y[1])))|(y[1]&(~(x[0]|x[1])))
		);
	}
}b[60];
LL y[60],sm;

inline void insert(Node x,LL v){
	ROF(i,59,0){
		if(((x[0]|x[1])>>i)&1){
			if(!(((b[i][0]|b[i][1])>>i)&1)){
				b[i] = x;y[i] = v;sm += v;return;
			}
			if(v > y[i]) sm += v-y[i],std::swap(v,y[i]),std::swap(x,b[i]);
			if(MP((x[0]>>i)&1,(x[1]>>i)&1) == MP((b[i][0]>>i)&1,(b[i][1]>>i)&1)){
				x = x+b[i]+b[i];					
			}
			else{
				x = x+b[i];
			}
		}
	}
}

int main(){
	int n;scanf("%d",&n);
	FOR(i,1,n){
		LL x,y;scanf("%lld%lld",&x,&y);
		x ^= sm;
		insert(Node(x,0),y);
		printf("%lld\n",sm);
	}
	return 0;
}