#include <algorithm>
#include <iostream>
#include <cstring>
#include <climits>
#include <cstdio>
#include <vector>
#include <cstdlib>
#include <ctime>
#include <cmath>
#include <queue>
#include <stack>
#include <map>
#include <set>

#define Re register
#define LL long long
#define U unsigned
#define FOR(i,a,b) for(Re int i = a;i <= b;++i)
#define ROF(i,a,b) for(Re int i = a;i >= b;--i)
#define SFOR(i,a,b,c) for(Re int i = a;i <= b;i+=c)
#define SROF(i,a,b,c) for(Re int i = a;i >= b;i-=c)
#define CLR(i,a) memset(i,a,sizeof(i))
#define BR printf("--------------------\n")
#define DEBUG(x) std::cerr << #x << '=' << x << std::endl
#define int LL
const int MAXN = 300000+5;
const int ha = 998244353;

int a[MAXN],N,K;
std::vector<int> t1,t2;
// -1 12345
// -1 -1
signed main(){
	scanf("%lld%lld",&N,&K);
	FOR(i,1,N) scanf("%lld",a+i);
	FOR(i,1,N){
		if(i & 1) t1.push_back(a[i]);
		else t2.push_back(a[i]);
	}
	int ans=0,t=1;
	FOR(i,0,(int)t1.size()-1){
		if(i > 0 && t1[i] != -1 && t1[i-1] != -1 && t1[i] == t1[i-1]){
			puts("0");
			return 0;
		}
		if(i > 0 && i<t1.size()-1 && K == 2){
			if(t1[i-1] != -1 && t1[i+1] != -1 && t1[i-1] != t1[i+1]){
				puts("0");
				return 0;
			}
		}
		if(t1[i] == -1){
			int l = i == 0 ? INT_MAX : t1[i-1];
			int r = i == t1.size()-1 ? INT_MAX : t1[i+1];
			if(l == INT_MAX && r == INT_MAX){
				t = 1ll*t*K%ha;//DEBUG(t);
			}
			else if(l == INT_MAX && t1[1] == -1){
				t = 1ll*t*K%ha;
			}
			else if(l == INT_MAX || r == INT_MAX){
				t = 1ll*t*(K-1)%ha;//DEBUG(t);
			}
			else if(t1[i-1] != -1 && t1[i+1] != -1 && l == r){
				t = 1ll*t*(K-1)%ha;//DEBUG(t);
			}
			else t = 1ll*t*(K-2)%ha;
		}
	}
	FOR(i,0,(int)t2.size()-1){
		//if(i == -1) t = t*(K-1)%ha;
		if(i > 0 && t2[i] != -1 && t2[i-1] != -1 && t2[i] == t2[i-1]){
			puts("0");
			return 0;
		}
		if(i > 0 && i<t2.size()-1 && K == 2){
			if(t2[i-1] != -1 && t2[i+1] != -1 && t2[i-1] != t2[i+1]){
				puts("0");
				return 0;
			}
		}
		if(t2[i] == -1){
			int l = i == 0 ? INT_MAX : t2[i-1];
			int r = i == t2.size()-1 ? INT_MAX : t2[i+1];
			if(l == INT_MAX && r == INT_MAX){
				t = 1ll*t*K%ha;
			}
			else if(l == INT_MAX && t2[1] == -1){
				t = 1ll*t*K%ha;
			}
			else if(l == INT_MAX || r == INT_MAX){
				t = 1ll*t*(K-1)%ha;
			}
			else if(t2[i-1] != -1 && t2[i+1] != -1 && l == r){
				t = 1ll*t*(K-1)%ha;
			}
			else t = 1ll*t*(K-2)%ha;
		}
	}
	printf("%lld\n",std::max(t,0ll));
	return 0;
}
/*
9 3
-1 -1 -1 -1 1 2 3 -1 -1 

-1 -1 1 3 -1
-1 -1 2 -1
*/
// 3*1*2*