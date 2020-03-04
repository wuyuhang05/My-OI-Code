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

const int MAXN = (1<<17)+233;
const int ha = 998244353;
const int inv2 = 499122177;
int A[MAXN],B[MAXN],n,N;
int a[MAXN],b[MAXN];

inline void init(){
    FOR(i,0,N) a[i] = A[i],b[i] = B[i];
}

inline void OR(int f[]){
    for(int mid = 1;mid < N;mid <<= 1){
        for(int i = 0;i < N;i += (mid<<1)){
            FOR(j,0,mid-1){
                (f[i+mid+j] += f[i+j]) %= ha;
            }
        }
    }
}

inline void iOR(int f[]){
    for(int mid = N>>1;mid;mid >>= 1){
        for(int i = 0;i < N;i += (mid<<1)){
            FOR(j,0,mid-1){
                (f[i+mid+j] += ha-f[i+j]) %= ha;
            }
        }
    }
}

inline void AND(int f[]){
    for(int mid = 1;mid < N;mid <<= 1){
        for(int i = 0;i < N;i += (mid<<1)){
            FOR(j,0,mid-1){
                (f[i+j] += f[i+mid+j]) %= ha;
            }
        }
    }
}

inline void iAND(int f[]){
    for(int mid = N>>1;mid;mid >>= 1){
        for(int i = 0;i < N;i += (mid<<1)){
            FOR(j,0,mid-1){
                (f[i+j] += ha-f[i+mid+j]) %= ha;
            }
        }
    }
}

inline void XOR(int f[]){
    for(int mid = 1;mid < N;mid <<= 1){
        for(int i = 0;i < N;i += (mid<<1)){
            FOR(j,0,mid-1){
                int x = f[i+j],y = f[i+mid+j];
                f[i+j] = (x+y)%ha;f[i+mid+j] = (x+ha-y)%ha;
            }
        }
    }
}

inline void iXOR(int f[]){
    for(int mid = N>>1;mid;mid >>= 1){
        for(int i = 0;i < N;i += (mid<<1)){
            FOR(j,0,mid-1){
                int x = f[i+j],y = f[i+mid+j];
                f[i+j] = 1ll*(x+y)%ha*inv2%ha;f[i+mid+j] = 1ll*(x+ha-y)%ha*inv2%ha;
            }
        }
    }
}

int main(){
    DEBUG(1);
    scanf("%d",&n);N = (1<<n);
    FOR(i,0,N-1) scanf("%d",A+i);FOR(i,0,N-1) scanf("%d",B+i);
    init();
    OR(a);OR(b);FOR(i,0,N-1) a[i] = 1ll*a[i]*b[i]%ha;
    iOR(a);FOR(i,0,N-1) printf("%d ",a[i]);puts("");
    init();
    AND(a);AND(b);FOR(i,0,N-1) a[i] = 1ll*a[i]*b[i]%ha;
    iAND(a);FOR(i,0,N-1) printf("%d ",a[i]);puts("");
    init();
    XOR(a);XOR(b);FOR(i,0,N-1) a[i] = 1ll*a[i]*b[i]%ha;
    iXOR(a);FOR(i,0,N-1) printf("%d ",a[i]);puts("");
    return 0;
}