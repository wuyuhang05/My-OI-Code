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

const int MAXN = 2e5 + 5;

std::map<int,int> ch[MAXN];
int len[MAXN],fail[MAXN];
int tot = 1,lst = 1;
LL ans = 0;

inline void copy(int x,int y){
	len[x] = len[y];fail[x] = fail[y];
	ch[x] = ch[y];
}

inline void insert(int c){
	int p = lst,np = lst = ++tot;
	len[np] = len[p]+1;
	while(p&&!ch[p][c]) ch[p][c] = np,p = fail[p];
	if(!p) fail[np] = 1;
	else{
		int q = ch[p][c];
		if(len[q] == len[p]+1) fail[np] = q;
		else{
			int nq = ++tot;copy(nq,q);
			len[nq] = len[p]+1;
			fail[np] = fail[q] = nq;
			while(p&&ch[p][c]==q) ch[p][c] = nq,p = fail[p];
		}
	}
	ans += len[np]-len[fail[np]];
}

int main(){
	// freopen("1.in","r",stdin);
	// freopen("a.out","w",stdout);
	int n;scanf("%d",&n);//DEBUG(n);
	FOR(i,1,n){
		int x;scanf("%d",&x);
		insert(x);
		printf("%lld\n",ans);
		// DEBUG(tot);DEBUG(i);
	}
	return 0;
}