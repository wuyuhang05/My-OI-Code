/*
 * Author: RainAir
 * Time: 2019-11-01 20:45:06
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

const int MAXN = 200+5;
const int MAXM = 20+5;
const int MAXL = 10+5;
int f[MAXN][MAXN],g[MAXN][MAXN][MAXM][MAXL],h[MAXN][MAXN];
char str[MAXM][MAXL],A[MAXN];
int len[MAXM];
int n,m,k;

int main(){
    freopen("a.in","r",stdin);
    scanf("%d%d%d",&n,&m,&k);
    scanf("%s",A+1);
    FOR(i,1,m){
        scanf("%s",str[i]+1);
        len[i] = strlen(str[i]+1);
    }
    CLR(f,0x3f);CLR(g,0x3f);
    FOR(i,1,n) FOR(j,1,m) g[i][i-1][j][0] = 0;
    FOR(len,1,n){
        FOR(l,1,n){
            int r = l+len-1;
            if(r > n) break;
            FOR(i,1,m){
                FOR(j,1,::len[i]){
                    if(str[i][j] == A[r])
                        g[l][r][i][j] = std::min(g[l][r][i][j],g[l][r-1][i][j-1]);
                    FOR(k,l,r)
                        g[l][r][i][j] = std::min(g[l][r][i][j],g[l][k-1][i][j]+f[k][r]);
                }
            }
            FOR(i,1,m) f[l][r] = std::min(f[l][r],g[l][r][i][::len[i]]+1);
        }
    }
    FOR(i,1,n){
        FOR(j,0,::k){
            h[i][j] = h[i-1][j] + 1;
            FOR(k,0,i){
                if(f[k][i] <= j) h[i][j] = std::min(h[i][j],h[k-1][j-f[k][i]]);
            }
        }
    }
    int ans = 1e9;
    FOR(i,0,k) ans = std::min(ans,h[n][i]);
    printf("%d\n",ans);
    return 0;
}
