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

const int MAXN = 1e5 + 5;
const int ha = 1e9 + 7;
const int inv2 = 500000004;
int A[MAXN],B[MAXN];
int n,m,N;
int prime[MAXN],cnt;
bool p[MAXN];

inline void prework(){
    FOR(i,2,MAXN-1){
        if(!p[i]) prime[++cnt] = i;
        for(int j = 1;j <= cnt && i*prime[j] < MAXN;++j){
            p[i*prime[j]] = true;
            if(!(i%prime[j])) break;
        }
    }
}

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

inline void Solve(){
    CLR(A,0);CLR(B,0);
    FOR(i,1,cnt){
        if(prime[i] > m) break;
        B[prime[i]]++;
    }
    N = 1;while(N <= m) N <<= 1;
    A[0] = 1;FWT(A);FWT(B);
    while(n){
        if(n & 1){
            FOR(i,0,N-1) A[i] = 1ll*A[i]*B[i]%ha;
        }
        FOR(i,0,N-1) B[i] = 1ll*B[i]*B[i]%ha;
        n >>= 1;
    }
    iFWT(A);
    printf("%d\n",A[0]);
}

int main(){
    prework();
    while(~scanf("%d%d",&n,&m)) Solve();
    return 0;
}