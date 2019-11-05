/*
 * Author: RainAir
 * Time: 2019-11-04 08:53:39
 */
#pragma GCC optimize("Ofast")
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

const int MAXN = 5000 + 5;
const int MAXM = 4e5 + 5;
const int ha = 1e9 + 7;

struct Node{
    int x,y,z;
    Node(int x=0,int y=0,int z=0) : x(x),y(y),z(z) {}

    bool operator < (const Node &t) const {
        return (x == t.x ? (y == t.y ? z < t.z : y < t.y) : x < t.x);
    }
}a[MAXN];

inline int qpow(int a,int n=ha-2){
    int res = 1;
    while(n){
        if(n & 1) res = 1ll*res*a%ha;
        a = 1ll*a*a%ha;n >>= 1;
    }
    return res;
}

int fac[MAXM],inv[MAXM];

inline void prework(){
    fac[0] = 1;
    FOR(i,1,MAXM-1) fac[i] = 1ll*fac[i-1]*i%ha;
    inv[MAXM-1] = qpow(fac[MAXM-1]);
    ROF(i,MAXM-2,0) inv[i] = 1ll*inv[i+1]*(i+1)%ha;
}

inline int C(int n,int m){
    if(n < m) return 0;
    return 1ll*fac[n]*inv[m]%ha*inv[n-m]%ha;
}

inline int F(int a,int b,int c){ // (0,0,0) to (a,b,c)
    return 1ll*C(a+b+c,a)*C(b+c,b)%ha;
}

int n,m;
int f[MAXN];

int main(){
    freopen("a.in","r",stdin);
    freopen("a.out","w",stdout);
    scanf("%d%d",&n,&m);
    prework();
    FOR(i,1,m) scanf("%d%d%d",&a[i].x,&a[i].y,&a[i].z);
    std::sort(a+1,a+m+1);
    f[0] = 1;a[0] = Node(0,0,0);
//    f[0] = F(n,n,n); // cond
    FOR(i,1,m){
        FOR(j,0,i-1){
            if(a[j].x <= a[i].x && a[j].y <= a[i].y && a[j].z <= a[i].z){
                int gx = 1ll*f[j]*F(a[i].x-a[j].x,a[i].y-a[j].y,a[i].z-a[j].z)%ha;
                gx = ha-gx;
                (f[i] += gx) %= ha;
            }
        }
    }
    int ans = 0;
    FOR(i,1,m){
        f[i] = 1ll*f[i]*F(n-a[i].x,n-a[i].y,n-a[i].z)%ha;
        (ans += f[i]) %= ha;
    }
    (ans += F(n,n,n)) %= ha;
    printf("%d\n",ans);
    return 0;
}
