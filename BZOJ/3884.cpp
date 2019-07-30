/*
 * Author: RainAir
 * Time: 2019-07-18 17:23:41
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

const int MAXN = 1e7 + 5;

bool p[MAXN];
int prime[MAXN],cnt,phi[MAXN];

inline void prework(){
    FOR(i,2,10000000){
        if(!p[i]) prime[++cnt] = i,phi[i] = i-1;
        for(int j = 1;j <= cnt && i*prime[j] <= 10000000;++j){
            p[i*prime[j]] = true;
            phi[i*prime[j]] = phi[i]*(prime[j]-1);
            if(!(i%prime[j])){
                phi[i*prime[j]] = phi[i]*prime[j];
                break;
            }
        }
    }
}

inline int qpow(int a,int n,int ha){
    int res = 1;
    while(n){
        if(n & 1) res = 1ll*res*a%ha;
        a = 1ll*a*a%ha;
        n >>= 1;
    }
    return res;
}

std::map<int,int> S;

inline int f(int x){
    if(S.count(x)) return S[x];
    int p = phi[x];
    return S[x] = qpow(2,f(p)+p,x);
}

inline void Solve(){
    int n;scanf("%d",&n);
    printf("%d\n",f(n));
}

int main(){
    prework();S[1] = 0;
    int T;scanf("%d",&T);
    while(T--) Solve();
    return 0;
}
