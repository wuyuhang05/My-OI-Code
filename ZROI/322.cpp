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

const int MAXN = 10100000 + 5;
const int ha = 998244353;

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

inline LL qpow(LL a,int n){
    LL ret = 1;
    while(n){
        // DEBUG(a);DEBUG(n);DEBUG(ret);
        if(n & 1) ret = (ret * a)%ha;
        a = (a * a)%ha;
        n >>= 1;
    }
    return ret;
}

LL powa[MAXN],powb[MAXN],inv[MAXN],inva[MAXN];
int M,N,P,Q;
LL f[MAXN];

LL query1(int x,int y){
    LL ans = 0,c = 1;
    int k = std::min(x-P,y-1);
    FOR(i,0,k){
        ans = (ans + f[y-i]%ha*powa[x-P-i]%ha*powb[i]%ha*c%ha)%ha;
        c = (x-P-i)*inv[i+1]%ha*c%ha;
    }
    return ans;
}

LL query2(int x,int y){
    LL ans = 0,c = 1;
    RFOR(i,y,1){
        LL k = ((y-i)&1) ? ha-1 : 1;
        // DEBUG(P-x+y-i);DEBUG(inva[P-x+y-i]);
        ans = (ans + k*powb[y-i]%ha*inva[P-x+y-i]%ha * f[i]%ha*c%ha)%ha;
        c = (y-i+P-x)*inv[y-i+1]%ha*c%ha;
    }
    return ans;
}

int main(){
    read(M);read(N);read(powa[1]);read(powb[1]);
    powa[0] = powb[0] = inv[0] = inv[1] = inva[0] = 1;
    inva[1] = qpow(powa[1],ha-2);
    // DEBUG(powa[1]);DEBUG(ha-2);DEBUG(qpow(powa[1],ha-2));
    FOR(i,2,N + M){
        inv[i] = (LL)(ha-ha/i) * inv[ha%i]%ha;
        powa[i] = (powa[i-1] * powa[1])%ha;
        powb[i] = (powb[i-1] * powb[1])%ha;
        inva[i] = (LL)(inva[i-1]*inva[1])%ha;
        // printf("%lld %lld %lld %lld\n",inv[i],powa[i],powb[i],inva[i]);
    }
    read(P);read(Q);
    FOR(i,1,N) read(f[i]);
    while(Q--){
        int x,y;read(x);read(y);
        if(x >= P) printf("%lld\n",query1(x,y));
        else printf("%lld\n",query2(x,y));
    }
    return 0;
}
