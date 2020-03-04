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

const int MAXN = (1<<21)+3;
const int ha = 1e9 + 7;
const int inv2 = 500000004;

char str[MAXN];
int n,N;
int pw[MAXN],pc[MAXN];
int f[MAXN];

inline void FWT(int f[]){
    for(int mid = 1;mid < N;mid <<= 1){
        for(int i = 0;i < N;i += (mid<<1)){
            FOR(j,0,mid-1){
                int x = f[i+j],y = f[i+mid+j];
                f[i+j] = (x+y)%ha;f[i+mid+j] = (x+ha-y)%ha;
            }
        }
    }
}

inline void iFWT(int f[]){
    for(int mid = N>>1;mid;mid >>= 1){
        for(int i = 0;i < N;i += (mid<<1)){
            FOR(j,0,mid-1){
                int x = f[i+j],y = f[i+mid+j];
                f[i+j] = 1ll*(x+y)*inv2%ha;f[i+mid+j] = 1ll*(x+ha-y)*inv2%ha;
            }
        }
    }
}

int main(){
    scanf("%d",&n);scanf("%s",str);
    N = (1<<(n+1));pw[0] = 1;
    FOR(i,1,MAXN-1) pw[i] = 2ll*pw[i-1]%ha,pc[i] = pc[i>>1]+(i&1);
    FOR(i,0,(1<<n)-1) f[i] = str[i]-'0';
    FWT(f);
    FOR(i,0,N-1) f[i] = 1ll*f[i]*f[i]%ha;
    iFWT(f);int ans = 0;
    FOR(i,0,N-1) (ans += 1ll*f[i]*pw[n-pc[i]]%ha) %= ha;//,DEBUG(f[i]),DEBUG(pc[i]);
    ans = 3ll*ans%ha;
    printf("%d\n",ans);
    return 0;
}
/*
我们先钦定A获胜两次，答案*3就好了
考虑枚举两个 f(S)=1 的串 S1 S2 表示A和B打 A和C打
每一位实际上是独立的 我们按位考虑如何达到这个条件，记这两位是x1 x2：
x1=0 x2=0 : BCA CBA
x1=1 x2=0 : CAB
x1=0 x2=1 : BAC
x1=1 x2=1 : ABC ACB
所以发现如果(x1 xor x2)=0 就可以造成2的贡献
所以两个串的贡献是2^(n-pc[S1 xor S2]) 可以用 FWT 方便维护
*/