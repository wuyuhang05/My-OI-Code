/*
 * sto Qingyu orz
 * 感谢真神sqy无私的教诲。膜时队者处处阿克，只因大师sqy在他背后。不膜大师者违背了真神的旨意，真神必将降下天谴,
 * 使其天天爆零
 * 我不由自主地膜拜真神sqy。
 * Author: RainAir
 * Time: 2019-10-14 09:10:40
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
#define int LL
const int MAXN = 2e6 + 5;
char str[MAXN];
int pre[MAXN];
int n,p,q,x,y;
std::deque<int> id,val;

signed main(){
    scanf("%lld%lld%lld%lld%lld",&n,&p,&q,&x,&y);
    scanf("%s",str+1);
    FOR(i,1,n) pre[i] = pre[i+n] = str[i] == '+' ? 1 : -1;
    FOR(i,1,2*n) pre[i] += pre[i-1];
    FOR(i,1,n-1){
        while(!val.empty() && val.back() >= pre[i]) val.pop_back(),id.pop_back();
        val.pb(pre[i]);id.pb(i);
    }
    LL ans = 1e18;
    FOR(i,0,n-1){
        if(id.front() == i) id.pop_front(),val.pop_front();
        while(!val.empty() && val.back() >= pre[n+i]) val.pop_back(),id.pop_back();
        val.pb(pre[n+i]);id.pb(n+i);
        int t = val.front() - pre[i];// min val
        LL gx = 0;
        if(p+t < 0) gx += std::ceil(std::abs((p+t))/2.0);
        gx += std::abs(p+pre[n+i]-pre[i]+2*gx-q)/2;
        ans = std::min(ans,(n-i)%n*y+gx*x);
    }
    printf("%lld\n",ans);
    return 0;
}
