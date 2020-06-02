/*
 * Author: RainAir
 * Time: 2020-05-29 15:26:05
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

const int MAXN = 2e5 + 5;
int n,d1,d2;
int a[MAXN];
bool f[MAXN];

inline void Solve(){
    scanf("%d%d%d",&n,&d1,&d2);
    FOR(i,1,n) scanf("%d",a+i),f[i] = 0;
    f[1] = 1;
    FOR(i,1,n-1){
        if(!f[i]) continue;
        if(i+1 <= n && std::abs(a[i]-a[i+1]) <= d1){
            f[i+1] = 1;
        }
        if(i+2 <= n && a[i] > a[i+1] && a[i+1] < a[i+2] && std::abs(a[i]-a[i+2]) <= d2){
            f[i+2] = 1;
        }
    }
    puts(f[n] ? "Yes" : "No");
}

int main(){
    int T;scanf("%d",&T);
    while(T--) Solve();
    return 0;
}
