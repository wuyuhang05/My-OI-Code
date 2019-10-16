/*
 * sto Qingyu orz
 * 感谢真神sqy无私的教诲。膜时队者处处阿克，只因大师sqy在他背后。不膜大师者违背了真神的旨意，真神必将降下天谴,
 * 使其天天爆零
 * 我不由自主地膜拜真神sqy。
 * Author: RainAir
 * Time: 2019-10-14 09:07:00
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

const int MAXN = 1e5 + 5;
int n,a[MAXN],b[MAXN];

inline void Solve(){
    scanf("%d",&n);
    FOR(i,1,n) scanf("%d",a+i);
    FOR(i,1,n) scanf("%d",b+i);
    std::sort(a+1,a+n+1);std::sort(b+1,b+n+1);
    int ansA = 0,ansB = 0;
    int j = 1;
    FOR(i,1,n){
        while(j <= n && b[j] < a[i]) ++j;
        ansA += j-1;
    }
    j = 1;
    FOR(i,1,n){
        while(j <= n && a[j] < b[i]) ++j;
        ansB += j-1;
    }
    puts(ansA == ansB ? "Tie" : (ansA > ansB ? "Alice" : "Bob"));
}

int main(){
    int T;scanf("%d",&T);
    while(T--) Solve();
    return 0;
}
