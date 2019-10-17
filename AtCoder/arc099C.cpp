/*
 * sto Qingyu orz
 * 感谢真神sqy无私的教诲。膜时队者处处阿克，只因大师sqy在他背后。不膜大师者违背了真神的旨意，真神必将降下天谴,
 * 使其天天爆零
 * 我不由自主地膜拜真神sqy。
 * Author: RainAir
 * Time: 2019-10-16 20:30:37
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
int k,n;
int a[MAXN];

int main(){
    scanf("%d%d",&n,&k);--k;
    FOR(i,1,n) scanf("%d",a+i);
    int ps = 0,ans = 1e9;
    FOR(i,1,n) if(a[i] == 1) ps = i;
    FOR(l,1,n){
        int r = l+k;
        if(l <= ps && ps <= r){
            ans = std::min(ans,(int)(std::ceil(1.0*(l-1)/k)+std::ceil(1.0*(n-r)/k)));
        }
    }
    printf("%d\n",ans+1);
    return 0;
}
