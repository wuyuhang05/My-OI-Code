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

const int MAXM = 30;
const int ha = 10086;
int b[MAXM+1];
int n;

inline void insert(int x){
	ROF(i,MAXM,0){
		if((x>>i)&1){
			if(b[i]) x ^= b[i];
			else{b[i] = x;break;}
		} 
	}
} 

int main(){
	scanf("%d",&n);
	FOR(i,1,n){
		int x;scanf("%d",&x);
		insert(x);
	}
	int sz = 0;
	int k;scanf("%d",&k);
	int t = 1,res = 0;
	FOR(i,0,MAXM){
		if(b[i]){
			if((k>>i)&1) res |= t;
			t <<= 1;++sz;
		}
	}
	FOR(i,1,n-sz) res = 2*res%ha;
	printf("%d\n",(res+1)%ha);
	return 0;
}
