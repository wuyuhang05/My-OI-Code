#include <algorithm>
#include <iostream>
#include <cstring>
#include <climits>
#include <cstdio>
#include <vector>
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
#define CLR(i,a) memset(i,a,sizeof(i))
#define BR printf("--------------------\n")
#define DEBUG(x) std::cerr << #x << '=' << x << std::endl
#define int LL
const int MAXN = 30+5;
const int MAXM = 50000+5;

int N,M,L,R,ans;
int s[MAXN][MAXM],sum[MAXN][MAXM];
char str[MAXM];

signed main(){
    scanf("%lld%lld%lld%lld",&N,&M,&L,&R);
    char ch=getchar();
    while(ch != '0' && ch != '1') ch = getchar();
    FOR(i,1,N){
        FOR(j,1,M){
            s[i][j] = ch-'0';ch = getchar();
        }
    }
    FOR(i,1,M) FOR(j,1,N) sum[j][i] += sum[j-1][i]+s[j][i];
    // FOR(i,1,M) FOR(j,1,N) printf("%d%c",sum[j][i],(j == N) ? '\n' : ' ');
    FOR(i,1,N){
        FOR(j,i,N){
            int l1=1,l2=0,r,sum1=0,sum2=0;
            FOR(r,1,M){
                sum1 += sum[j][r]-sum[i-1][r];
                sum2 += sum[j][r]-sum[i-1][r];
                if(sum2 < L) continue;
                while(sum2-(sum[j][l2]-sum[i-1][l2]) >= L && l2 < r) sum2 -= sum[j][l2]-sum[i-1][l2],l2++;
                while(sum1 > R) sum1 -= sum[j][l1]-sum[i-1][l1],l1++;
                ans += l2-l1+1;
            }
        }
    }
    printf("%lld\n",ans);
    return 0;
}
