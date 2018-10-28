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
#define int long long
const int MAXN = 2000 + 5;
const int ha = 258280327;
int f[MAXN][MAXN];

LL qpow(LL a,LL n=ha-2){
    LL ret = 1ll;
    while(n){
        if(n & 1) ret = (ret * a) % ha;
        a = (a * a) % ha;
        n >>= 1;
    }
    return ret;
}
int inv[MAXN];
inline void solve(){
    int N,x,y;read(N);
    read(x);read(y);
    LL p = x*qpow(y)%ha;
    inv[0] = 1;
    FOR(i,1,N) inv[i] = (inv[i-1])*(1-p+ha)%ha;
    CLR(f,0);f[0][0] = 1;
    FOR(i,1,N){
        FOR(j,1,i){
            f[i][j] = (f[i][j]+f[i-1][j-1]*inv[j-1]%ha)%ha;
            f[i][j] = (f[i][j]+f[i-1][j]*(1-inv[j]+ha)%ha)%ha;
        }
    }
    /*
    FOR(i,1,N){
        FOR(j,1,i){
            printf("%lld ",f[i][j]);
        }
        puts("");
    }*/
    FOR(i,0,N-1){
        int ans = 0ll;
        FOR(pos,1,N) ans = (ans + f[pos-1][i])%ha;
        printf("%lld%c",ans*inv[i]%ha*qpow(N)%ha,(i == N-1) ? '\n' : ' ');
    }
}

signed main(){
    int T;read(T);
    while(T--)solve();
    return 0;  
}

// f[i][j] 第i个人受到j次攻击的概率
// f[i][j] = f[i-1][j-1]*((N-i+1)) + f[i-1][j]
//          