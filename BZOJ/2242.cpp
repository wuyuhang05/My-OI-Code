//#include <tr1/unordered_map>
#include <unordered_map>
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
#define int LL
int a,b,c;

inline int qpow(int a,int n,int ha){
    int res = 1ll;
    while(n){
        if(n & 1) res = 1ll*res*a%ha;
        a = 1ll*a*a%ha;
        n >>= 1;
    }
    return res;
}

inline void Solve1(){
    printf("%lld\n",qpow(a,b,c));
}

inline int exgcd(int a,int b,int &x,int &y){
    if(!b){
        x = 1;y = 0;
        return a;
    }
    int g = exgcd(b,a%b,x,y);
    int t = x;x = y;y = t-(a/b)*y;
    return g;
}

inline void Solve2(){
    std::swap(b,c);int x=0,y=0;
    int g = exgcd(a,b,x,y);
    if(c%g){
        puts("Orz, I cannot find x!");
        return;
    }
    x = x*c/g;
    x = (x%b+b)%b;
    printf("%lld\n",x);
}

std::unordered_map<int,int> S;

inline void Solve3(){
    S.clear();int p = c,phi = p-1;
    int q = std::sqrt(1.0*p)+1;b %= c;
    FOR(i,0,q-1){
        int t = 1ll*b*qpow(a,i,p)%p;
        if(!S.count(t)) S[t] = i;
    }
    //a = qpow(a,1,p);
    a %= p;
    if(!a){
        puts(!b ? "1" : "Orz, I cannot find x!");
        return ;
    }
    FOR(i,0,q){
        int t = qpow(a,i*q,p);
        if(S.count(t)){
            int ans = i*q-S[t];
            if(ans < 0) continue;
            printf("%lld\n",ans);
            return;
        }
        //t = 1ll*t*tt%p;
    }
    puts("Orz, I cannot find x!");
}

signed main(){
    int T,k;scanf("%lld%lld",&T,&k);
    while(T--){
        scanf("%lld%lld%lld",&a,&b,&c);
        if(k == 1) Solve1();
        if(k == 2) Solve2();
        if(k == 3) Solve3();
    }
    return 0;
}
