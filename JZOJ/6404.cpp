/*
 * Author: RainAir
 * Time: 2019-11-04 17:13:47
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

const int MAXN = 3000 + 5;
const int MAXM = 1e5 + 5;
std::bitset<MAXN> S[MAXM],rS[MAXM];
// 第 i 列是否存在第 j 个数
int n,m,k;
int a[MAXN][MAXN];
int f[MAXN],cnt[MAXM],cf[MAXN];
int g[MAXN][MAXN],lst[MAXM],mx;

int main(){
    scanf("%d%d%d",&n,&m,&k);
    FOR(i,1,n) FOR(j,1,m) scanf("%d",&a[i][j]),mx = std::max(mx,a[i][j]);
    FOR(i,1,k){
        FOR(j,1,m){
            S[a[i][j]][j] = 1;
            rS[a[i][j]][m-j+1] = 1;
        }
    }
    FOR(i,1,mx) lst[i] = n+1;
    FOR(j,1,m){
        ROF(i,n,1){
            g[i][j] = lst[a[i][j]] <= std::min(i+k-1,n);
            lst[a[i][j]] = i;
        }
        ROF(i,n,1) lst[a[i][j]] = n+1;
    }
    int now = 0;
    FOR(i,1,k){
        FOR(j,1,k){
            now += !cnt[a[i][j]];
            ++cnt[a[i][j]];
        }
    }
    int ans1 = 0;LL ans2 = 0;
    f[1] = now;
    FOR(j,2,m-k+1){
        FOR(i,1,k){
            --cnt[a[i][j-1]];
            now -= !cnt[a[i][j-1]];
        }
        FOR(i,1,k){
            now += !cnt[a[i][j+k-1]];
            ++cnt[a[i][j+k-1]];
        }
        f[j] = now;
    }
    FOR(i,1,m-k+1) ans1 = std::max(ans1,f[i]),ans2 += f[i];
    FOR(i,2,n-k+1){
        CLR(cf,0);
        FOR(j,1,m){
            if(g[i][j]){
                S[a[i][j]][j] = rS[a[i][j]][m-j+1] = 0;
                int pre = m-rS[a[i][j]]._Find_next(m-j+1)+1;
                int suf = S[a[i][j]]._Find_next(j);
                // [pre+1,suf-k]
                cf[std::max(pre+1,j-k+1)]--;cf[std::min(j,suf-k)+1]++;
            }
        }
        FOR(j,1,m){
            if(!S[a[i][j]][j]){
                int pre = m-rS[a[i][j]]._Find_next(m-j+1);
                int suf = S[a[i][j]]._Find_next(j);
                S[a[i][j]][j] = rS[a[i][j]][m-j+1] = 0;
                cf[std::max(pre+1,j-k+1)]++;cf[std::min(j,suf-k)+1]--;
            }
        }
        FOR(j,1,m-k+1) cf[i] += cf[i-1],f[i] += cf[i];
        FOR(j,1,m-k+1) ans1 = std::max(ans1,f[j]),ans2 += f[j];
    }
    printf("%d %lld\n",ans1,ans2);
    return 0;
}
