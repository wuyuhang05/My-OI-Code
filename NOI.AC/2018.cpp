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

const int MAXN = 1e6 + 5;
const int ha = 1e9 + 7;

inline int qpow(int a,int n=ha-2){
	int res = 1;
	while(n){
		if(n & 1) res = 1ll*res*a%ha;
		a = 1ll*a*a%ha;
		n >>= 1;
	}
	return res;
}

int G[MAXN];
int n,p;
int pp[MAXN],ipp[MAXN];
int pw1[MAXN],pw2[MAXN];
// pw1: 1/(1-p^i) pw2:1/(1-p^{-i})

int main(){
    int x,y;scanf("%d%d%d",&n,&x,&y);p = 1ll*x*qpow(y)%ha;
    pp[0] = 1;FOR(i,1,MAXN-1) pp[i] = 1ll*pp[i-1]*p%ha;
    ipp[MAXN-1] = qpow(pp[MAXN-1]);
    ROF(i,MAXN-2,0) ipp[i] = 1ll*ipp[i+1]*p%ha;
    pw1[0] = pw2[0] = 1;
    FOR(i,1,MAXN-1) pw1[i] = 1ll*pw1[i-1]*qpow((pp[i]-1+ha)%ha)%ha;
    FOR(i,1,MAXN-1) pw2[i] = 1ll*pw2[i-1]*qpow((ipp[i]-1+ha)%ha)%ha;
    int q;scanf("%d",&q);
    int inv = qpow(n);
    FOR(cwdw,1,q){
        int k;scanf("%d",&k);--k;
        if(k == 0){
            printf("%d\n",inv);
            continue;
        }
        if(k == 1) G[1] = 1;
        else FOR(i,1,k) G[i] = 1ll*qpow((1-pp[i]+ha),k-1)%ha*qpow(ipp[i],k-1)%ha*pw1[k-i]%ha*pw2[i-1]%ha;
        int ans = 0;
        FOR(i,1,k){
            int t = (qpow((1-pp[i]+ha)%ha,n-k)+ha-1)%ha;
            t = 1ll*t*qpow(ha-pp[i])%ha;
            (ans += 1ll*t*G[i]%ha) %= ha;
        }
        ans = 1ll*ans*qpow(p,(1ll*k*(k+1)/2) % (ha-1))%ha*inv%ha;
        printf("%d\n",ans);
    }
    return 0;
}
