/*
 * Author: RainAir
 * Time: 2019-07-17 08:40:43
 * Fixed
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

int main(){
 //   LL x;scanf("%lld",&x);
   // puts((x & 1) && x != 1 ? "Yes" : "No");
    LL x;scanf("%lld",&x);
    LL q = std::sqrt(1.0*x);
    if(x == 1){
        puts("No");return 0;
    }
    FOR(b,1,q){
        if((x-b)%(1+b) == 0 && x-b > 0){
            LL a = (x-b)/(1+b);
            LL c = a*b;
            if(a+b+c == x){
                puts("Yes");return 0;
            }
        }
    }
    puts("No");
    return 0;
}
