/*
 * Author: RainAir
 * Time: 2019-07-31 19:03:20
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

const int MAXN = (1<<20)+1;
double p[MAXN];
int cnt[MAXN];
int n,N;

int main(){
    scanf("%d",&n);N = 1<<n;
    FOR(i,0,N-1) scanf("%lf",p+i),cnt[i] = cnt[i>>1]+(i&1);
    FOR(i,0,N-1) cnt[i] = (cnt[i]&1) ? 1 : -1;
    for(int mid = 1;mid < N;mid <<= 1){
        for(int i = 0;i < N;i += (mid<<1)){
            for(int j = 0;j < mid;++j){
                p[i+j+mid] += p[i+j];
            }
        }
    }
    double ans = 0.0;
    FOR(i,1,N-1) if(1-p[(N-1)^i] > 1e-8)ans += cnt[i]/(1-p[(N-1)^i]);
    if(ans < 1e-10){
        puts("INF");return 0;
    }
    printf("%.8f\n",ans);
    return 0;
}
