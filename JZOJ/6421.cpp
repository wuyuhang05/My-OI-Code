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

#define lc ((x)<<1)
#define rc ((x)<<1|1)
const int MAXN = 5e6+5;
//#include <assert.h>
//LL f[MAXN][2],g[MAXN][2];
const int ha = 998244353;

struct Node{
    LL f0,f1,g0,g1;
    Node(LL f0=0,LL f1=0,LL g0=0,LL g1=0) : f0(f0),f1(f1),g0(g0),g1(g1) {}
};

std::map<LL,Node> S;

inline Node dfs(LL x,LL l,LL r){
	if(l == r){
        return Node(0,1,1,1);
	}
    if(S.count(r-l+1)) return S[r-l+1];
	LL mid = (l + r) >> 1;
	Node L = dfs(lc,l,mid);
    Node R = dfs(rc,mid+1,r);
    Node res;
    res.f1 = L.f0+R.f0+1;
    res.g1 = L.g0*R.g0%ha;
    /*
	f[x][1] = f[lc][0]+f[rc][0]+1;
	g[x][1] = g[lc][0]*g[rc][0]%ha;
	*/
    LL mx = std::max(std::max(L.f0+R.f1,L.f1+R.f0),L.f0+R.f0);
	res.f0 = mx;
	if(L.f0+R.f1 == mx) (res.g0 += 1ll*L.g0*R.g1%ha)%=ha;
	if(L.f1+R.f0 == mx) (res.g0 += 1ll*L.g1*R.g0%ha)%=ha;
	if(L.f0+R.f0 == mx) (res.g0 += L.g0*R.g0%ha)%=ha;
    return S[r-l+1] = res;
}

int main(){
	freopen("match.in","r",stdin);
	freopen("match.out","w",stdout);
    int T;scanf("%d",&T);
    while(T--){
	    LL n;scanf("%lld",&n);
//        FOR(i,1,2*n+2) f[i][0] = f[i][1] = g[i][0] = g[i][1] = 0;
	    S.clear();
        Node res = dfs(1,1,n);
	    printf("%lld %lld\n",res.f0,res.g0);
    }
	return 0;
}

