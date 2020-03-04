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

const int ha = 1e9 + 7;
const int MAXN = 20+5;
int n,m,c;
int a[MAXN],b[MAXN];
char str[MAXN];
int nxt[MAXN],ta[MAXN][MAXN],tb[MAXN][MAXN];

inline int id(char c){
	return c == 'B' ? 0 : (c == 'W' ? 1 : 2);
}

inline void getnxt(int str[]){

}

inline void Solve(){
	scanf("%s",str+1);FOR(i,1,m) a[i] = id(str[i]);
	scanf("%s",str+1);FOR(i,1,m) b[i] = id(str[i]);
	getnxt(a);
	FOR(i,0,m-1){
		FOR(j,0,2){
			int p = i;
			while(p && a[p+1] != j) p = nxt[p];
			if(a[p+1] == j) ++p;
			ta[i][j] = p;
		}
	}
	getnxt(b);
	FOR(i,0,m-1){
		FOR(j,0,2){
			int p = i;
			while(p && b[p+1] != j) p = nxt[p];
			if(b[p+1] == j) ++p;
			tb[i][j] = p;
		}
	}
}

int main(){
	int T;scanf("%d%d%d%d",&n,&m,&c,&T);
	while(T--) Solve();
	return 0;
}