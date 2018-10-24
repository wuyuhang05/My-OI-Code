#include <algorithm>
#include <iostream>
#include <cstring>
#include <climits>
#include <cstdio>
#include <vector>
#include <cstdlib>
#include <ctime>
#include <cmath>
#include <queue>
#include <stack>
#include <map>
#include <set>

#define Re register
#define LL long long
#define U unsigned
#define FOR(i,a,b) for(Re int i = a;i <= b;++i)
#define ROF(i,a,b) for(Re int i = a;i >= b;--i)
#define SFOR(i,a,b,c) for(Re int i = a;i <= b;i+=c)
#define SROF(i,a,b,c) for(Re int i = a;i >= b;i-=c)
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

const int ha = 1000000000 + 7;
const int MAXN = 200000 + 5;

inline LL qpow(LL a,LL n=ha-2){
    LL ret = 1ll;
    while(n){
        if(n & 1) ret = (ret * a) % ha;
        a = (a * a) % ha;
        n >>= 1;
    }
    return ret;
}

LL inv[MAXN<<1];

inline void pre(){
    inv[0] = inv[1] = 1;
    FOR(i,2,MAXN) inv[i] = (inv[i-1]*i)%ha;
}

inline LL C(LL up,LL down){
    //if(up < down) return 0;
    return inv[up]*qpow(inv[down])%ha*qpow(inv[up-down])%ha;
}

inline LL calc(int x,int y){
    return C(x+y-2,x-1);
}

LL ans = 0;
LL H,W,A,B;

int main(){
    read(H);read(W);read(A);read(B);
    pre();
    FOR(i,0,H-A-1){
        ans = (ans + (C(i+B-1,i)*C(H-i-1+W-B-1,H-i-1))%ha)%ha;
    }
    printf("%lld\n",ans);
    return 0;
}