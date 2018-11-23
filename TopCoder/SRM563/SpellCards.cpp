#include <algorithm>
#include <iostream>
#include <cstring>
#include <climits>
#include <cstdio>
#include <vector>
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
#define CLR(i,a) memset(i,a,sizeof(i))
#define BR printf("--------------------\n")
#define DEBUG(x) std::cerr << #x << '=' << x << std::endl

class SpellCards{
	static const int MAXN = 100+5;
	int f[MAXN];
	public:
		int maxDamage(std::vector<int> l,std::vector<int> d){
			int N = l.size();
			FOR(i,0,N-1){
				ROF(j,N,l[i]){
					f[j] = std::max(f[j],f[j-l[i]]+d[i]);
				}
			}
			int ans = 0;
			FOR(i,1,N) ans = std::max(ans,f[i]);
			return ans;
		}
};
