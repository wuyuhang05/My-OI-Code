/*
 * sto Qingyu orz
 * 感谢真神sqy无私的教诲。膜时队者处处阿克，只因大师sqy在他背后。不膜大师者违背了真神的旨意，真神必将降下天谴,
 * 使其天天爆零
 * 我不由自主地膜拜真神sqy。
 * Author: RainAir
 * Time: 2019-10-17 08:17:33
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

const int MAXN = 250000 + 5;
const LL ha = 1000000000000000031;
const LL BASE = 1e9+7;

inline LL mul(LL x,LL y){
    __int128_t t = (__int128_t)x*y%ha;
    return (LL)t;
}

inline LL add(LL x,LL y){
    x += y;x %= ha;
    return x;
}

inline LL qpow(LL a,LL n=ha-2){
    LL res = 1;
    while(n){
        if(n & 1) res = mul(res,a);
        a = mul(a,a);
        n >>= 1;
    }
    return res;
}

char str[MAXN];
int n;
LL hsh[MAXN],p[MAXN],inv;
std::map<LL,int> S;

int main(){
    scanf("%d",&n);
    scanf("%s",str+1);inv = qpow(BASE);
    p[0] = 1;//DEBUG(inv);
//    DEBUG(mul(inv,BASE));
    FOR(i,1,n){
        hsh[i] = hsh[i-1];
        p[i] = p[i-1];
        if(str[i] == '+'){
            hsh[i] = add(hsh[i],p[i]);
        }
        if(str[i] == '-'){
            hsh[i] = add(hsh[i],ha-p[i]);
        }
        if(str[i] == '<'){
            p[i] = mul(p[i],inv);
        }
        if(str[i] == '>'){
            p[i] = mul(p[i],BASE);
        }
    }
    LL ans = 0;
    ROF(i,n,1){ // hsh[r]== hsh[n]*base[l-1]+hsh[l-1]
        S[hsh[i]]++;
        ans += S[add(mul(hsh[n],p[i-1]),hsh[i-1])];
    }
    printf("%lld\n",ans);
    return 0;
}
