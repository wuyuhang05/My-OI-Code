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

const int MAXN = 5000+5;
LL f[MAXN][MAXN];
// 所有数字都移动肯定能有序 所以要对不移动的位置 dp
int A,B;
int n,p[MAXN];

int main(){
    scanf("%d%d%d",&n,&A,&B);
    FOR(i,1,n) scanf("%d",p+i);
    CLR(f,0x3f);f[0][0] = 0;
    FOR(i,1,n){
        FOR(j,0,n){
            if(p[i] > j){
                f[i][j] = std::min(f[i][j],f[i-1][j]+A);
                f[i][p[i]] = std::min(f[i][p[i]],f[i-1][j]);
            }
            else{
                f[i][j] = std::min(f[i][j],f[i-1][j]+B);
            }
        }
    }
    LL ans = 1e18;
    FOR(i,1,n) ans = std::min(ans,f[n][i]);
    printf("%lld\n",ans);
    return 0;
}
