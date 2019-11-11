/*
 * Time: 2019-11-10 17:07:02
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

const int MAXN = 20+1;
int f[(1<<MAXN)+3];
int w[MAXN][MAXN];
int c[MAXN][MAXN],d[MAXN][MAXN];
// i 串 j 位
int n,m;
char str[MAXN][MAXN];

int main(){
    scanf("%d%d",&n,&m);
    FOR(i,0,n-1) scanf("%s",str[i]);
    FOR(i,0,n-1) FOR(j,0,m-1) scanf("%d",&w[i][j]);
    FOR(i,0,n-1){
        FOR(j,0,m-1){
            int mx = 0;
            FOR(k,0,n-1){
                if(str[k][j] == str[i][j]) c[i][j] |= (1<<k),mx = std::max(mx,w[k][j]),d[i][j] += w[k][j];
            }
            d[i][j] -= mx;
        }
    }
    FOR(i,1,(1<<n)-1) f[i] = 1e9;
    FOR(S,0,(1<<n)-1){
        FOR(i,0,n-1){
            if(!((1<<i)&S)){
                FOR(j,0,m-1){
                    f[S|(1<<i)] = std::min(f[S|(1<<i)],f[S]+w[i][j]);
                    f[S|c[i][j]] = std::min(f[S|c[i][j]],f[S]+d[i][j]);
                }
                break;
            }
        }
    }
    printf("%d\n",f[(1<<n)-1]);
    return 0;
}
