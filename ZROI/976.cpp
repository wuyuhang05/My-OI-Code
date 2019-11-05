/*
 * Author: RainAir
 * Time: 2019-11-03 19:22:05
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

const int MAXN = 100+5;
const int ha = 1e9 + 7;
int n,m;
char S[MAXN],T[MAXN];
LL gS[MAXN][2],gT[MAXN][2];
std::map<LL,int> f[MAXN];

int main(){
    scanf("%s%s",S,T);
    n = strlen(S);m = strlen(T);
    if(n < m) std::swap(n,m),std::swap(S,T);
    FOR(i,0,n+m-1){
        FOR(j,0,m){
            FOR(k,0,1){
                if(i-j < n && i-j >= 0 && k == (S[i-j]-'0')) gS[i][k] |= (1ll<<j);
            }
        }
        FOR(j,0,m){
            FOR(k,0,1){
                if(k == (T[j]-'0')) gT[i][k] |= (1ll<<j);
            }
        }
    }
    f[0][1] = 1;
    FOR(i,0,n+m-1){
        for(auto x:f[i]){
            FOR(k,0,1){
                LL nxt = (x.fi&gS[i][k])|(((x.fi&gT[i][k])<<1));
                f[i+1][nxt] += x.se;
                f[i+1][nxt] %= ha;
            }
        }
    }
    printf("%d\n",f[n+m][(1ll<<m)]);
    return 0;
}
