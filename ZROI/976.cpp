/*
 * Author: RainAir
 * Time: 2019-10-27 22:06:21
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
#define int LL
const int MAXN = 100+5;
char S[MAXN],T[MAXN];
int n,m;
std::map<LL,int> f[MAXN];
int gS[MAXN][2],gT[MAXN][2];

signed main(){
    scanf("%s%s",S+1,T+1);
    n = strlen(S+1);m = strlen(T+1);
    FOR(i,1,n+m){
        FOR(j,1,std::max(n,m)){
            FOR(k,0,1){
                if(j >= 1 && j <= m && (T[j] == '1') == k){
                    gT[i][k] |= (1ll<<(j-1));
                }
                if(i-j >= 1 && i-j <= n && (S[i-j] == '1') == k){
                    gS[i][k] |= (1ll<<(j-1));
                }
            }
        }
    }
    f[0][1] = 1;
    FOR(i,0,n+m-1){
        for(auto x:f[i]){
            FOR(k,0,1){
                f[i+1][(gS[i+1][k]&(x.fi))|(gT[i+1][k]&(x.fi<<1))] += x.se;
            }
        }
    }
    int ans = 0;
    printf("%lld\n",f[n+m][(1<<m)]);
    return 0;
}
