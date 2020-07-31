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

const int MAXN = 20+5;
const int ha = 998244353;

inline void add(int &x,int y){
    (x += y);if(x >= ha) x -= ha;
}

int n,a[MAXN];
int f[2][MAXN],now;

int main(){
    scanf("%d",&n);FOR(i,1,n) scanf("%d",a+i);
    std::sort(a+1,a+n+1);std::reverse(a+1,a+n+1);
    FOR(i,1,n){
        CLR(f[now^1],0);
        FOR(j,0,n+1){
            if(!f[now][j] && !(i == 1 && j == n+1)) continue;
            FOR(k,1,j-1){
                add(f[now^1][std::max(0,j-2*std::min(k,j-k))],f[now][j]+1ll*std::min(k,j-k)*a[i]%ha);
            }
            // n-i-j
            if(n-i-j >= 0) add(f[now^1][j],1ll*(n-i-j)*f[now][j]%ha);
        }
        now ^= 1;
        if(i == 2){
            FOR(j,0,n+1) DEBUG(f[now][j]);
        }
    }
    printf("%d\n",f[now][0]);
    return 0;
}
