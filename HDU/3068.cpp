/*
 * Author: RainAir
 * Time: 2019-08-26 14:26:16
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
#define Re register
#define LL long long
#define pb push_back
#define MP std::make_pair
#define all(x) x.begin(),x.end()
#define CLR(i,a) memset(i,a,sizeof(i))
#define FOR(i,a,b) for(Re int i = a;i <= b;++i)
#define ROF(i,a,b) for(Re int i = a;i >= b;--i)
#define DEBUG(x) std::cerr << #x << '=' << x << std::endl

const int MAXN = 2e7 + 5;

char str[MAXN],a[MAXN<<1];
int p[MAXN<<1],n;

inline void manacher(){
    int maxlen = 0,mid = 0;
    FOR(i,1,n){
        if(i < maxlen) p[i] = std::min(p[2*mid-i],p[mid]-(i-mid));
        else p[i] = 1;
        while(a[i-p[i]] == a[i+p[i]]) p[i]++;
        if(i+p[i] > maxlen){
            maxlen = i+p[i];
            mid = i;
        }
    }
}

inline void clear(){
    CLR(a,0);CLR(p,0);
}

inline void Solve(){
    n = strlen(str+1);
    a[0] = '$';a[1] = '#';
    FOR(i,1,n){
        a[i<<1] = str[i];
        a[(i<<1)+1] = '#';
    }
    n = (n<<1)+1;
    manacher();int ans = 1;
    FOR(i,1,n) ans = std::max(ans,p[i]);
    printf("%d\n",ans-1);clear();
}

int main(){
//    freopen("a.in","r",stdin);
    while(~scanf("%s",str+1)) Solve();
    return 0;
}
