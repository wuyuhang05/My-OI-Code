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

const int MAXN = 2e6 + 5;
const int ha = 998244353;
const int inv2 = 499122177;
const int inv4 = 1ll*inv2*inv2%ha;

int N,mx;
int A[MAXN];
inline void FWT(int f[]){
    for(int mid = 1;mid < N;mid <<= 1){
        for(int i = 0;i < N;i += (mid<<1)){
            FOR(j,0,mid-1){
                int x = f[i+j],y = f[i+mid+j];
                f[i+j] = (x+y)%ha;
                f[i+mid+j] = (x+ha-y)%ha;
            }
        }
    }
}

inline void iFWT(int f[]){
    for(int mid = N>>1;mid;mid >>= 1){
        for(int i = 0;i < N;i += (mid<<1)){
            FOR(j,0,mid-1){
                int x = f[i+j],y = f[i+mid+j];
                f[i+j] = 1ll*(x+y)*inv2%ha;
                f[i+mid+j] = 1ll*(x+ha-y)*inv2%ha;
            }
        }
    }
}

inline int qpow(int a,int n=ha-2){
    int res = 1;
    while(n){
        if(n & 1) res = 1ll*res*a%ha;
        a = 1ll*a*a%ha;
        n >>= 1;
    }return res;
}

int n;

int main(){//DEBUG(1);
    scanf("%d",&n);
    FOR(i,1,n){
        int x;scanf("%d",&x);
        mx = std::max(mx,x);
        A[x] += 2;A[0]++;
    }
    N = 1;while(N <= mx) N <<= 1;FWT(A);
    FOR(i,0,N-1){
        int x = 1ll*(n+A[i])%ha*inv4%ha;
        // DEBUG(x);DEBUG(n);DEBUG(A[i]);
        A[i] = qpow(3,x);
        if((n-x)&1) A[i] = ha-A[i];
    }
    // DEBUG(A[0]);
    iFWT(A);
    // DEBUG(A[0]);
    printf("%d\n",(A[0]+ha-1)%ha);
    return 0;
}