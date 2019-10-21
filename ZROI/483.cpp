/*
 * sto Qingyu orz
 * 感谢真神sqy无私的教诲。膜时队者处处阿克，只因大师sqy在他背后。不膜大师者违背了真神的旨意，真神必将降下天谴,
 * 使其天天爆零
 * 我不由自主地膜拜真神sqy。
 * Author: RainAir
 * Time: 2019-10-21 20:47:20
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
#define P std::pair<int,int>
#define LL long long
#define pb push_back
#define MP std::make_pair
#define all(x) x.begin(),x.end()
#define CLR(i,a) memset(i,a,sizeof(i))
#define FOR(i,a,b) for(int i = a;i <= b;++i)
#define ROF(i,a,b) for(int i = a;i >= b;--i)
#define DEBUG(x) std::cerr << #x << '=' << x << std::endl

const int MAXN = 5e5 + 5;
int n;
P a[MAXN];
int b[MAXN],tp;

inline bool cmp(P a,P b){
    return a.fi == b.fi ? a.se < b.se : a.fi > b.fi;
}

int main(){
    scanf("%d",&n);
    FOR(i,1,n) scanf("%d%d",&a[i].fi,&a[i].se);
    std::sort(a+1,a+n+1,cmp);
    b[tp = 1] = a[1].se;
    FOR(i,2,n){
        if(a[i].se >= b[tp]) b[++tp] = a[i].se;
        else{
            int ps = std::upper_bound(b+1,b+tp+1,a[i].se)-b;
            b[ps] = a[i].se;
        }
    }
    printf("%d\n",tp);
    return 0;
}
