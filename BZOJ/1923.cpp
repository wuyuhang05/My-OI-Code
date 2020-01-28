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

const int MAXN = 2000+5;

std::bitset<MAXN> S[MAXN];
int n,sz,m;
inline void insert(std::bitset<MAXN> x){
	FOR(i,0,n-1){
		if(!x[i]) continue;
		if(S[i][i]) x ^= S[i];
		else{
			S[i] = x;
			++sz;return;
		}
	}
}

char str[MAXN];std::bitset<MAXN> t;
int main(){
	scanf("%d%d",&n,&m);
	FOR(i,1,m){
		scanf("%s",str);t.reset();
		FOR(i,0,n-1) t[i] = str[i]-'0';
		int x;scanf("%d",&x);t[n] = x;
		insert(t);
		if(sz == n){
			printf("%d\n",i);
			break;
		}
	}
	if(sz < n) {puts("Cannot Determine");return 0;}
	ROF(i,n-1,0){
		ROF(j,i-1,0) if(S[j][i]) S[j][i] = 0,S[j][n] = S[i][n]^S[j][n];
	}
	FOR(i,0,n-1) puts(S[i][n] ? "?y7M#" : "Earth");
	return 0;
}