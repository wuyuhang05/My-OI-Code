/*
 * Author: RainAir
 * Time: 2019-08-20 18:47:39
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

const int ha = 10000+7;
const int inv6 = 1668;
LL n;
char str[1000+5];

int main(){
    scanf("%s",str+1);int len = strlen(str+1);
    FOR(i,1,len){
        (n *= 10)%=ha;(n += (str[i]-'0')) %= ha;
    }
    printf("%lld\n",1ll*n*(n+1)%ha*(n+2)%ha*inv6%ha);
    return 0;
}
