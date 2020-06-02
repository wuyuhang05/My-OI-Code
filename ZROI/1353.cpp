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

const int MAXN = 5e5 + 5;
const int ha = 998244353;

int n,m;
int b[MAXN],p[MAXN];
int fac[MAXN],inv[MAXN];
std::set<int> S;

inline int qpow(int a,int n=ha-2){
	int res = 1;
	while(n){
		if(n & 1) res = 1ll*res*a%ha;
		a = 1ll*a*a%ha;
		n >>= 1;
	}
	return res;
}

inline void prework(){
    fac[0] = 1;FOR(i,1,MAXN-1) fac[i] = 1ll*fac[i-1]*i%ha;
    inv[MAXN-1] = qpow(fac[MAXN-1]);ROF(i,MAXN-2,0) inv[i] = 1ll*inv[i+1]*(i+1)%ha;
}

inline int C(int n,int m){
    if(n < m) return 0;
    return 1ll*fac[n]*inv[m]%ha*inv[n-m]%ha;
}

inline int iC(int n,int m){
    if(n < 0 || m < 0) return 0;
    if(n < m) return 0;
    return 1ll*inv[n]*fac[m]%ha*fac[n-m]%ha;
}

int main(){prework();
    scanf("%d%d",&n,&m);
    FOR(i,1,n) scanf("%d",b+i);std::sort(b+1,b+n+1);
    FOR(i,1,n) scanf("%d",p+i);
    S.insert(0);S.insert(n+1);b[n+1] = m+1;int now = C(m,n),ans = 0;
    FOR(i,1,n){
        auto it = S.upper_bound(p[i]);--it;
        int pl = *it;++it;int pr = *it;
        int vl = b[pl],vr = b[pr];
        now = 1ll*now*iC(vr-vl-1,pr-pl-1)%ha;
        if(b[p[i]]-vl <= vr-b[p[i]]){
            FOR(j,vl+p[i]-pl,b[p[i]]-1){
                (ans += 1ll*now*C(j-vl-1,p[i]-pl-1)%ha*C(vr-j-1,pr-p[i]-1)%ha) %= ha;
            }
        }
        else{
            int sm = C(vr-vl-1,pr-pl-1);
            FOR(j,b[p[i]],vr-pr+p[i]){
                (sm += ha-1ll*C(j-vl-1,p[i]-pl-1)%ha*C(vr-j-1,pr-p[i]-1)%ha) %= ha;
            }
            (ans += 1ll*now*sm%ha) %= ha;
        }
        S.insert(p[i]);
        now = 1ll*now*C(b[p[i]]-vl-1,p[i]-pl-1)%ha*C(vr-b[p[i]]-1,pr-p[i]-1)%ha;
    }
    printf("%d\n",ans);
    return 0;
}
