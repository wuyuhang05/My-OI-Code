#pragma GCC optimize("Ofast")
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
#define FOR(i,a,b) for(int i = a;i <= b;++i)
#define ROF(i,a,b) for(int i = a;i >= b;--i)
#define DEBUG(x) std::cerr << #x << '=' << x << std::endl

const int MAXD = 20+5;
const int MAXN = 3e6+5;
int d;
struct Node{
	double a[MAXD];
	Node(){CLR(a,0);}

	friend Node operator * (const Node &x,const Node &y){
		Node res;
		FOR(i,0,d-1) FOR(j,0,d-1) res.a[i+j] += x.a[i]*y.a[j];
		FOR(i,d,d*2) res.a[i%d] += res.a[i],res.a[i] = 0;
		return res;
	}
};

inline Node qpow(Node a,int n){
	Node res;res.a[0] = 1;
	while(n){
		if(n & 1) res = res*a;
		a = a*a;
		n >>= 1;
	}
	return res;
}
int n,m;
char s[MAXN];
double ans[MAXD],val[MAXD][MAXD];
int main(){
	scanf("%d%d%d",&n,&d,&m);
	scanf("%s",s+1);
	if(d == 1){
		double res = 0;
		FOR(i,1,n) res += i*(i+1)/2.0;
		printf("%.10f\n",res);return 0;
	}
	for(int i = d;i <= n;i += d){
		FOR(j,i-d+1,i){
			val[s[j]-'0'][(s[j]-'0'-(j-1)%d+d)%d] += j;
		}
		Node a;a.a[0] = 1.0*(i-2)/i;a.a[d-1] += 1.0/i;a.a[1] += 1.0/i;
		Node res = qpow(a,m);
		FOR(a,0,d-1){
			FOR(b,0,d-1){
				ans[a] += res.a[b]*val[a][b];
			}
		}
	}
	FOR(i,0,d-1) printf("%.10f\n",ans[i]);
	return 0;
}