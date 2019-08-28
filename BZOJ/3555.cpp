/*
 * Author: RainAir
 * Time: 2019-08-26 09:59:14
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
#define int LL
const int BASE = 131;
const int MAXN = 30000+5;
const int MAXL = 200+5;

U LL sm[MAXN][MAXL],a[MAXN],b[MAXN];
int n,m,s;
char str[MAXN];

inline U LL calc(int i,int l,int r){
    return sm[i][r]-sm[i][l-1]*b[r-l+1];
}

signed main(){
    scanf("%lld%lld%lld",&n,&m,&s);
    FOR(i,1,n){
        scanf("%s",str+1);
        FOR(j,1,m) sm[i][j] = sm[i][j-1]*BASE+str[j];
    }b[0] = 1;
    FOR(i,1,n) b[i] = b[i-1]*BASE;int ans = 0;
    FOR(i,1,m){
        FOR(j,1,n) a[j] = sm[j][m]-sm[j][i]*b[m-i]+sm[j][i-1]*b[m-i+1];
        std::sort(a+1,a+n+1);int cnt = 0;
        FOR(j,2,n){
            if(a[j] == a[j-1]) cnt++;
            else cnt = 0;
            ans += cnt;
        }
    }
    printf("%lld\n",ans);
    return 0;
}
