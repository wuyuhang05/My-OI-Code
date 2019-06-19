#include <algorithm>
#include <iostream>
#include <cstring>
#include <climits>
#include <cstdio>
#include <vector>
#include <cstdlib>
#include <ctime>
#include <cmath>
#include <queue>
#include <stack>
#include <map>
#include <set>

#define Re register
#define LL long long
#define U unsigned
#define FOR(i,a,b) for(Re int i = a;i <= b;++i)
#define ROF(i,a,b) for(Re int i = a;i >= b;--i)
#define SFOR(i,a,b,c) for(Re int i = a;i <= b;i+=c)
#define SROF(i,a,b,c) for(Re int i = a;i >= b;i-=c)
#define CLR(i,a) memset(i,a,sizeof(i))
#define BR printf("--------------------\n")
#define DEBUG(x) std::cerr << #x << '=' << x << std::endl

const int MAXN = 200 + 5;
const int MAXM = 20 + 5;

int f[MAXN][MAXN][MAXM][MAXM],g[MAXN][MAXN];
int n,m,k;
char str1[MAXN],str2[MAXN][MAXN];
int slen[MAXN],h[MAXN][MAXN];

inline void chkmin(int &a,int b){
    if(a > b) a = b;
}

int main(){
    scanf("%d%d%d",&n,&m,&k);
    scanf("%s",str1+1);
    FOR(i,1,m) scanf("%s",str2[i]+1),slen[i] = strlen(str2[i]+1);
    CLR(f,0x3f);CLR(g,0x3f);
    FOR(i,1,n){
        g[i][i-1] = 0;
        FOR(j,1,m) f[i][i-1][j][0] = 0;
    }
    FOR(len,1,n){
        FOR(l,1,n){
            int r = l+len-1;if(r > n) break;
            FOR(i,1,m){
                FOR(j,1,slen[i]){
                    if(str1[r] == str2[i][j]) chkmin(f[l][r][i][j],f[l][r-1][i][j-1]);
                }
            }
            FOR(k,l,r){
                FOR(i,1,m){
                    FOR(j,1,slen[i]){
                        chkmin(f[l][r][i][j],f[l][k-1][i][j]+g[k][r]);
                    }
                }
            }
            FOR(i,1,m) chkmin(g[l][r],f[l][r][i][slen[i]]+1);
        }
    }
    FOR(i,1,n){
        FOR(j,0,k){
            h[i][j] = h[i-1][j]+1;
            FOR(k,1,i) if(g[k][i] <= j) chkmin(h[i][j],h[k-1][j-g[k][i]]);
        }
    }
    int ans = INT_MAX;
    FOR(i,0,k) chkmin(ans,h[n][i]);
    printf("%d\n",ans);
    return 0;
}
