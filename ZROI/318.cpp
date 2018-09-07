#include <algorithm>
#include <iostream>
#include <cstring>
#include <climits>
#include <cstdio>
#include <vector>
#include <cmath>
#include <queue>
#include <stack>
#include <map>
#include <set>

#define R register
#define LL long long
#define U unsigned
#define FOR(i,a,b) for(R int i = a;i <= b;++i)
#define RFOR(i,a,b) for(R int i = a;i >= b;--i)
#define CLR(i,a) memset(i,a,sizeof(i))
#define BR printf("--------------------\n")
#define DEBUG(x) std::cerr << #x << '=' << x << std::endl

namespace fastIO{
    #define BUF_SIZE 100000
    #define OUT_SIZE 100000
    #define ll long long
    bool IOerror=0;
    inline char nc(){
        static char buf[BUF_SIZE],*p1=buf+BUF_SIZE,*pend=buf+BUF_SIZE;
        if (p1==pend){
            p1=buf; pend=buf+fread(buf,1,BUF_SIZE,stdin);
            if (pend==p1){IOerror=1;return -1;}
        }
        return *p1++;
    }
    inline bool blank(char ch){return ch==' '||ch=='\n'||ch=='\r'||ch=='\t';}
    inline void read(int &x){
        bool sign=0; char ch=nc(); x=0;
        for (;blank(ch);ch=nc());
        if (IOerror)return;
        if (ch=='-')sign=1,ch=nc();
        for (;ch>='0'&&ch<='9';ch=nc())x=x*10+ch-'0';
        if (sign)x=-x;
    }
    inline void read(ll &x){
        bool sign=0; char ch=nc(); x=0;
        for (;blank(ch);ch=nc());
        if (IOerror)return;
        if (ch=='-')sign=1,ch=nc();
        for (;ch>='0'&&ch<='9';ch=nc())x=x*10+ch-'0';
        if (sign)x=-x;
    }
    #undef ll
    #undef OUT_SIZE
    #undef BUF_SIZE
};
using namespace fastIO;

const int ha = 323232323;

const int ____ = 1000000 + 5;
const int MAXN = 500000;
LL N,a[____];
LL mul[____],inv[____];
LL f[____],g[____];

inline LL qpow(LL a,LL n){
    LL ret = 1;
    while(n){
        if(n & 1) ret = (ret * a)%ha;
        a = (a * a) % ha;
        n >>= 1;
    }
    return ret;
}

inline LL C(LL a,LL b){
    return mul[a] * inv[b] % ha * inv[a-b] % ha;
}

inline void pre(){
    mul[0] = 1;
    FOR(i,1,MAXN*2){
        mul[i] = (mul[i-1] * i) % ha;
    }
    inv[MAXN * 2] = qpow(mul[MAXN*2],ha-2);
    RFOR(i,MAXN*2-1,0){
        inv[i] = inv[i+1]*(i+1)%ha;
    }
}

int main(){
    read(N);
    FOR(i,1,N) read(a[i]);
    pre();
    FOR(i,0,MAXN){
        f[i] = qpow(inv[2],a[1] + i) * C(a[1]-1+i,i) % ha;
        g[i] = f[i] * i % ha;
        if(i){
            f[i] = (f[i] + f[i-1]) % ha;
            g[i] = (g[i] + g[i-1]) % ha;
        }
    }
    LL ret = a[1];
    FOR(i,2,N){
        ret = (ret + (g[a[i]] + (ha + 1 - f[a[i]]) * a[i] % ha))%ha;
    }
    printf("%lld\n",ret);
    return 0;
}

