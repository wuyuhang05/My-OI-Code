#include <algorithm>
#include <iostream>
#include <cstring>
#include <climits>
#include <cstdlib>
#include <cstdio>
#include <bitset>
#include <vector>
#include <cmath>
#include <ctime>
#include <queue>
#include <stack>
#include <map>
#include <set>

#define fi first
#define se second
#define U unsigned
#define P std::pair
#define LL long long
#define pb push_back
#define MP std::make_pair
#define all(x) x.begin(),x.end()
#define CLR(i,a) memset(i,a,sizeof(i))
#define FOR(i,a,b) for(int i = a;i <= b;++i)
#define ROF(i,a,b) for(int i = a;i >= b;--i)
#define DEBUG(x) std::cerr << #x << '=' << x << std::endl

const int MAXN = 200+5;
const int ha = 1e9 + 7;

int n;
int a[MAXN];
char g[MAXN][MAXN];
int f[MAXN][MAXN],sm[MAXN][MAXN];

inline void add(int &a,int b){
	(a += b);if(a >= ha) a -= ha;
}

inline void Solve(){
	scanf("%d",&n);
	FOR(i,1,n) scanf("%d",a+i);
	FOR(i,1,n) scanf("%s",g[i]+1);
	FOR(i,0,n) FOR(j,0,n) f[i][j] = 0;
	int ans = 0;
	FOR(i,1,n){
		FOR(j,1,n){
			FOR(k,1,n){
				sm[j][k] = (g[a[j]][a[i]]=='1')*f[j][k];
			}
		}
		FOR(j,1,n){
			FOR(k,1,n){
				add(sm[j][k],sm[j-1][k]);
				add(sm[j][k],sm[j][k-1]);
				add(sm[j][k],ha-sm[j-1][k-1]);
			}
		}
		FOR(j,1,n){
			FOR(k,1,n){
				if(a[i] == a[j] && a[j] == a[k]){
					int t = 1;add(t,sm[j-1][k-1]);
					add(f[j][k],t);
					add(ans,t);
				}
			}
		}
	}
	printf("%d\n",ans);
}

int main(){
	int T;scanf("%d",&T);
	while(T--) Solve();
	return 0;
}
/*
n^3 = \sum_{i=1}^n \sum_{j=1}^n \sum_{k=1}^n 1
所以变成把序列复制三份 a[],b[],c[] 然后算有多少对(a,b,c) 满足是好的并且相同
设 f[i][j][k] 表示当前 a[1..i],b[1..j],c[1..k] 并且 a 结尾 i ,b 结尾 j,c结尾k 的方案数
朴素的 O(n^6) dp:f[i][j][k] = f[i'][j'][k']*g[a[i']][a[i]] 我们规定 dp 数组仅在 a[i]=b[j]=c[k] 有值
可以考虑把 f 关于 i 做个前缀和来转移 然后每次转移都做个前缀和 O(n^3)
*/
