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

const int BASE = 35 + 5;
const int MAXN = 100000 + 5;
const int ha = 998244353;

int p[BASE];
int mul[MAXN],max;
int N,K;

inline void pre(){
    mul[0] = mul[1] = 1;
    FOR(i,2,MAXN-1){
        mul[i] = (1ll*mul[i-1]*i)%ha;
    }
}

LL ans = 0;

inline LL qpow(LL a,LL n=ha-2){
    LL ret = 1ll;
    while(n){
        if(n & 1) ret = (ret * a) % ha;
        a = (a * a) % ha;
        n >>= 1;
    }
    return ret%ha;
}

inline LL C(int up,int down){
    if(up < down) return 0;
    return 1ll * mul[up] % ha * qpow(mul[down])%ha * qpow(mul[up-down])%ha;
}

int main(){
    freopen("card.in","r",stdin);
    freopen("card.out","w",stdout);
    read(N);read(K);
    FOR(i,1,N){
        LL x;read(x);
        int cnt = 0;
        while(x){
            p[++cnt] += (x&1);
            x >>= 1;
        }
        max = std::max(max,cnt);
    }
    pre();
    FOR(i,1,max){
        int num1 = p[i],num2 = N-p[i]; // num1 : 1,num2 : 0;
        LL sum = 0ll;
        FOR(j,1,std::min(num1,K)){ // 枚举每位的贡献
            sum = (sum + (C(num1,j) * C(num2,K-j))%ha)%ha;
            j++; // C
        }
        // DEBUG(sum);
        ans = (ans + sum * qpow(2,i-1))%ha;
    }
    printf("%lld\n",ans);
    return 0;
}