/*
 * sto Qingyu orz
 * 感谢真神sqy无私的教诲。膜时队者处处阿克，只因大师sqy在他背后。不膜大师者违背了真神的旨意，真神必将降下天谴,
 * 使其天天爆零
 * 我不由自主地膜拜真神sqy。
 * Author: RainAir
 * Time: 2019-10-16 16:45:44
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

const int MAXN = 100000+5;
int n,a[MAXN],k;

int main(){
    scanf("%d%d",&n,&k);
    FOR(i,1,n) scanf("%d",a+i);
    std::sort(a+1,a+n+1);
    int ans = 1e9;
    FOR(l,1,n){
        int r = l+k-1;
        if(r > n) break;
        int gx = 0;
        if(a[r] <= 0) gx = std::abs(a[l]);
        else if(a[l] >= 0) gx = a[r];
        else gx = std::min(2*std::abs(a[l])+a[r],std::abs(a[l])+2*a[r]);
        ans = std::min(ans,gx);
    }
    printf("%d\n",ans);
    return 0;
}

