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
#define RFOR(i,a,b) for(Re int i = a;i >= b;--i)
#define SFOR(i,a,b,c) for(Re int i = a;i <= b;i+=c)
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

const int MAXN = 50 + 5;
const int MAXM = 500 + 5;
const LL INF = 0x3f3f3f;

LL N,M;
LL v[MAXN],a[MAXN];
LL f[MAXN][MAXM]; // 2...i 号政党获得的席位为 j,留给 i+1 号政党的最大票数

inline bool check(int mid){
    CLR(f,0x3f);
    f[1][0] = 0;
    FOR(i,2,N-1){
        FOR(j,0,M){ // 枚举 2...i 个政党总共获得的席位
            FOR(k,0,j){ // 枚举第 i 个政党获得的席位
                LL gx = ((k+1)*v[1])/mid-v[i]-f[i-1][j-k];
                if(gx >= 0) f[i][j] = std::min(f[i][j],std::max(a[i]-gx,0ll));
            }
        }
    }
    LL xN = INF; // 最后一个政党获得的席位
    FOR(i,0,M){ // 枚举 2...N-1 个政党总共获得的席位并确认方案是否可行
        if(f[N-1][i] >= INF) continue;
        LL t = (v[N]+f[N-1][i])*mid-1;
        // DEBUG(t);
        xN = std::min(xN,std::max(0ll,t/v[1])+i);
    }
    return M-mid >= xN;
}

int main(){
    read(N);read(M);
    FOR(i,1,N) read(v[i]);
    FOR(i,1,N) read(a[i]);
    v[1] += a[1] + a[N]; // 断环为链
    LL L = 0,R = M + 1,ans;
    while(L <= R){
        LL mid = (L + R) >> 1;
        if(check(mid)) ans = mid,L = mid + 1;
        else R = mid - 1;
    }
    printf("%lld\n",ans);
    return 0;
}