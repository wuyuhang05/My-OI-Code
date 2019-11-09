/*
 * Author: RainAir
 * Time: 2019-11-06 15:13:36
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
const int MAXN = 1e6 + 5;
int n,x,a,b,m;
int ans[MAXN];

signed main(){
    scanf("%lld%lld%lld%lld%lld",&n,&x,&a,&b,&m);
    int sm = n*x;
    FOR(i,1,n-1) sm += a*(n-i);
    sm -= m;
    //assert(!(sm%(a+b)));
    sm /= (a+b);
    //DEBUG(sm);
    ROF(i,n-1,1){
        if(sm >= i){
            sm -= i;
            ans[n-i] = true;// to B
        }
        else if(sm > 0){
            ans[n-sm] = true;
            break;
        }
        else break;
    }
    int now = x;
    FOR(i,1,n) printf("%lld ",now),now += ans[i] ? -b : a;
    return 0;
}
