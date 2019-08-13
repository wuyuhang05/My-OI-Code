/*
 * Author: RainAir
 * Time: 2019-08-06 19:34:56
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
#define P std::pair<int,int>
#define Re register
#define LL long long
#define pb push_back
#define MP std::make_pair
#define all(x) x.begin(),x.end()
#define CLR(i,a) memset(i,a,sizeof(i))
#define FOR(i,a,b) for(Re int i = a;i <= b;++i)
#define ROF(i,a,b) for(Re int i = a;i >= b;--i)
#define DEBUG(x) std::cerr << #x << '=' << x << std::endl

const int MAXN = 1e5 + 5;
const int ha = 1e9 + 7;
int a[MAXN],b[MAXN],n;

inline int qpow(int a,int n){
    int res = 1;
    while(n){
        if(n & 1) res = 1ll*res*a%ha;
        a = 1ll*a*a%ha;
        n >>= 1;
    }
    return res;
}

inline void Solve(){
    scanf("%d",&n);
    FOR(i,1,n) scanf("%d",a+i);
    FOR(i,1,n) scanf("%d",b+i);
    P p1 = MP(1,1),p2 = MP(1,1);int tp = 1,cnt = 1,flag = 1;
    a[1]--;b[1]--;
    FOR(i,1,2*n-2){
        if(a[p1.fi] > 0 && p1.se < n) p1.se++;
        else p1.fi++;
        if(b[p2.se] > 0 && p2.fi < n) p2.fi++;
        else p2.se++;
        a[p1.fi]--;b[p1.se]--;
        if(p1.fi != p2.fi || p1.se != p2.se) a[p2.fi]--,b[p2.se]--,flag = 0;
        else if(!flag) cnt++,flag = true;
    }
    FOR(i,1,n) if(a[i] || b[i]) {puts("0");return;}
    printf("%d\n",qpow(2,cnt-1)%ha);
}

int main(){
    int T;scanf("%d",&T);
    while(T--) Solve();
    return 0;
}
