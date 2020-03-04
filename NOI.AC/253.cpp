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

const int ha = 998244353;
const int MAXN = 1000+5;
const int inv3 = 332748118;
const int inv4 = 748683265;
int f[MAXN][MAXN];
int n,m;
int A[MAXN],B[MAXN];
// f[i][j] = A[j]f[i][1]+B[j]

inline int qpow(int a,int n=ha-2){
    int res = 1;
    while(n){
        if(n & 1) res = 1ll*res*a%ha;
        a = 1ll*a*a%ha;
        n >>= 1;
    }
    return res;
}
int x,y;
int main(){
    DEBUG(qpow(3));
    DEBUG(qpow(4));
    scanf("%d%d%d%d",&n,&m,&x,&y);
    if(m == 1){
        printf("%lld\n",2ll*(n-x)%ha);return 0;
    }
    ROF(i,n-1,1){
        A[1] = 1;B[1] = 0;
        A[2] = 2;B[2] = (ha+ha-3-f[i+1][1])%ha;
        FOR(j,2,m-1){
            int C = (1+1ll*inv4*f[i+1][j]%ha)%ha;
            A[j+1] = (3ll*A[j]+ha-A[j-1])%ha;
            B[j+1] = ((3ll*B[j]%ha+ha-B[j-1])%ha+ha-4ll*C%ha)%ha;
        }
        int C = (1+1ll*inv3*f[i+1][m]%ha) % ha;
        f[i][1] = 1ll*(B[m-1]+3ll*C%ha+ha-2ll*B[m]%ha)*qpow((2ll*A[m]%ha+ha-A[m-1])%ha)%ha;
        FOR(j,2,m) f[i][j] = (1ll*f[i][1]*A[j]%ha+B[j])%ha;
    }
    printf("%d\n",f[x][y]);
    return 0;
}