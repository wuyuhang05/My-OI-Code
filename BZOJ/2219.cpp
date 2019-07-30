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

inline int qpow(int a,int n,int ha=-1){
    int res = 1;
    while(n){
        if(n & 1){
            if(ha == -1) res = 1ll*res*a;
            else res = 1ll*res*a%ha;
        }
        if(ha == -1) a = 1ll*a*a;
        else a = 1ll*a*a%ha;
        n >>= 1;
    }
    return res;
}
int f[1000005],tot;
inline int getg(int p){
    int ps = p-1;tot = 0;
    int q = std::sqrt(1.0*ps);
    FOR(i,2,q){
        if(!(ps%i)){
            f[++tot] = i;
            while(!(ps%i)) ps /= i;
        }
    }
    if(ps != 1) f[++tot] = ps;
    for(int i = 1;i < p;i++){
        int j = 1;bool flag = true;
        for(;j <= tot;++j){
            if(qpow(i,(p-1)/f[j],p) == 1) {flag = false;break;}
        }
        if(flag) return i;
    }
}

std::unordered_map<int,int> S;

inline int BSGS(int a,int b,int p){ // a^x == b (mod p)
    S.clear();int q = std::sqrt(1.0*p)+1;
    b %= p;int t = b;
    FOR(i,0,q-1){
        S[t] = i;
        t = 1ll*t*a%p;
    }
    a %= p;
    if(!a) return !b ? 1 : -1;
    int base = qpow(a,q,p);
    FOR(i,0,q){
        if(S.count(t)){
            int gx = i*q-S[t];
            if(gx >= 0) return gx;
        }
        t = 1ll*t*base%p;
    }
    return -1;
}

inline int exgcd(int a,int b,int &x,int &y){
    if(!b){
        x = 1,y = 0;
        return a;
    }
    int g = exgcd(b,a%b,x,y);
    int t = x;x = y;y = t-(a/b)*y;
    return g;
}

inline int work(int a,int b,int p,int e){
    int pk = qpow(p,e),g = getg(p),phi = qpow(p,e-1)*(p-1);
    int lgb = BSGS(g,b,pk);int lgx,y;
    int gc = exgcd(a,phi,lgx,y);
    if(lgb%gc) return -1;
    lga = lga*(lgb/gc)%phi;
    lga = (lga%phi+phi)%phi;
}

inline void Solve(){
    int A,B,K;scanf("%d%d%d",&A,&B,&K);
    int q = std::sqrt(1.0*K):,x = K;
    int ans = 1;
    FOR(i,2,q){
        if(!(x%i)){
            int e = 0,p = 1;
            while(!(x%i)) e++,x /= i;
            ans = 1ll*ans*work(A,B,i,e);
        }
    }
    printf("%d\n",ans);
}

int main(){
    int T;scanf("%d",&T);
    while(T--) Solve();
    return 0;
}
