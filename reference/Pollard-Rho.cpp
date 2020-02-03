#pragma GCC optimize("Ofast")
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
#define int LL

const int prime[] = {0,2,3,5,7,11,13,17,19,23};

inline LL qmul(int x,int y,int p){
    x %= p;y %= p;
    int k = (LL)((1.0L*x*y)/(1.0L*p)),t = x*y-k*p;
    t -= p;while(t < 0) t += p;return t;
}


inline int qpow(int a,int n,int ha){
    int res = 1ll;a %= ha;
    while(n){
        if(n & 1) res = qmul(res,a,ha);
        a = qmul(a,a,ha);
        n >>= 1;
    }
    return res;
}


inline bool chk(int x,int p){
    if(!(x%p)) return false;
    if(qpow(p%x,x-1,x) != 1) return false;
    int k = x-1;
    while(!(k&1)){
        k >>= 1;
        int t = qpow(p%x,k,x);
        if(t != 1 && t != x-1) return false;
        if(t == x-1) return true;
    }
    return true;
}


inline bool isprime(int x){
    if(x < 2) return false;
    FOR(i,1,9){
        if(x == prime[i]) return true;
        if(!chk(x,prime[i])) return false;
    }
    return true;
}

inline int gcd(int a,int b){
    if(a < b) std::swap(a,b);
    if(!b) return a;
    if(!(a&1) && !(b&1)) return gcd(a>>1,b>>1)<<1;
    if(!(a&1)) return gcd(a>>1,b);
    if(!(b&1)) return gcd(a,b>>1);
    return gcd(a-b,b);
}

inline LL rnd(int x){
    LL ans = 1ll*rand()*rand()*rand()*rand();
    ans %= x;ans++;
    return ans;
}

inline LL calc(int x,int t){
    LL v0 = rnd(x-1),v=v0,s = 1,cnt = 0,k = 1;
    while(true){
        v = (qmul(v,v,x)+t)%x;s = qmul(s,std::abs(v-v0),x);
        if(v == v0 || !s) return x;
        if(++cnt == k){
            int g = gcd(s,x);
            if(g != 1) return g;
            v0 = v;k <<= 1;
        }
    }
    return x;
}

std::vector<int> ans;

inline void work(int x,int t){
    if(x == 1) return;
    if(isprime(x)){
        ans.pb(x);
        return;
    }
    int y = x;while((y = calc(x,t--)) == x);
    while(!(x%y)) x /= y;
    work(x,t);work(y,t);
}

int p;
std::vector<int> Div;

inline void Solve(){int val;
    scanf("%lld",&val);
    ans.clear();work(val,19260817);
    Div.clear();Div.pb(1);int tt = val;
    FOR(i,0,(int)ans.size()-1){
        int e = 0;while(!(tt%ans[i])) tt /= ans[i],e++;
        int sz = (int)Div.size()-1;
        FOR(k,0,sz){
            int base = ans[i];
            FOR(j,1,e) Div.pb(Div[k]*base),base *= ans[i];
        }
    }
}