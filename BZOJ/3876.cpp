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

const int MAXN = 1e3 + 5;
const int MAXM = 1e5 + 5;

struct Edge{
	int to,nxt,flow,cap,w;
}e[MAXM<<1];
int head[MAXN],cnt;

inline void add(int u,int v,int cap,int w){
	e[++cnt] = (Edge){v,head[u],0,cap,w};head[u] = cnt;
	e[++cnt] = (Edge){u,head[v],0,0,-w};head[v] = cnt;
}

inline void spfa(){
	
}

int main(){

	return 0;
}