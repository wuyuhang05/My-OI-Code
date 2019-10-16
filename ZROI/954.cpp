/*
 * Author: RainAir
 * Time: 2019-09-02 18:26:10
 */
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
const int MAXM = 1000 + 5; //sqrt
const int rules[] = {0,3,1,2};

#define int LL
int f[2][MAXM][MAXM];
int n,m,now;

struct Node{
    int w,s,p;

    bool operator < (const Node &t) const {
        return w == t.w ? rules[p] < rules[t.p] : w < t.w;
    }
}a[MAXN];

signed main(){
    scanf("%lld%lld",&n,&m);
    if(2*m > n){
        puts("-1");return 0;
    }
    FOR(i,1,n) scanf("%lld%lld%lld",&a[i].w,&a[i].s,&a[i].p);
    std::sort(a+1,a+n+1);
    FOR(i,0,MAXM-1) FOR(j,0,MAXM-1) f[now][i][j] = f[now^1][i][j] = 1e18;
    f[now][0][0] = 0;
    FOR(i,1,n){
        now ^= 1;
        FOR(j,0,2*m){
            FOR(k,0,m){
                f[now][j][k] = std::min(f[now][j][k],f[now^1][j][k]);
                if(a[i].p == 2 || a[i].p == 3) //2 :zu yuan
                    f[now][j+1][k+1] = std::min(f[now][j+1][k+1],f[now^1][j][k]+a[i].s);
                if(a[i].p == 1 || a[i].p == 3)
                    if(k >= 1)
                        f[now][j+1][k-1] = std::min(f[now][j+1][k-1],f[now^1][j][k]+a[i].s);
                f[now^1][j][k] = 1e18;
            }
        }
    }
    printf("%lld\n",f[now][2*m][0] == 1e18 ? -1ll : f[now][2*m][0]);
    return 0;
}
