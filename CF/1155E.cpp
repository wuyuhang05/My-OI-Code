#include <algorithm>
#include <iostream>
#include <cstring>
#include <climits>
#include <cstdlib>
#include <cstdio>
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

int x[100],y[100],n = 11;
const int ha = 1e6 + 3;

inline int qpow(int a,int n){
    int res = 1;
    while(n){
        if(n & 1) res = 1ll*res*a%ha;
        a = 1ll*a*a%ha;
        n >>= 1;
    }
    return res;
}

inline int calc(int k){
    int ans = 0;
    FOR(i,1,n){
        int s1 = 1,s2 = 1;
        FOR(j,1,n){
            if(i == j) continue;
            s1 = 1ll*s1*(k-x[j]+ha)%ha;
            s2 = 1ll*s2*(x[i]-x[j]+ha)%ha;
        }
        s2 = qpow(s2,ha-2);
        s1 = 1ll*s1*s2%ha*y[i]%ha;
        (ans += s1) %= ha;
    }
    return ans;
}

int main(){
    FOR(i,1,n){
        std::cout << "? " << i << std::endl;
        std::cout.flush();
        std::cin >> y[i];
        x[i] = i;
    }
    int ans = -1;
    FOR(i,1,n){
        if(y[i] == 0){
            std::cout << "! " << x[i] << std::endl;
            std::cout.flush();
        }
    }
    FOR(i,0,ha-1){
        if(!calc(i)){
            ans = i;
            break;
        }
    }
    std::cout << "! " << ans << std::endl;
    std::cout.flush();
    return 0;
}
