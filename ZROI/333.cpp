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

const int MAXN = 300000 + 5;
int N,M;
LL a[MAXN],b[MAXN],f[5005][5005];

int main(){
    read(N);read(M);
    FOR(i,1,N) read(a[i]);
    std::sort(a + 1,a + N + 1);
    LL n1 = N%M,n2=M-N%M,l1=N/M+1,l2=N/M;
    FOR(i,0,n1)
        FOR(j,0,n2)
        f[i][j] = LLONG_MAX;
    f[0][0] = 0;
    FOR(i,0,n1){
        FOR(j,0,n2){
            if(i < n1) f[i+1][j] = std::min(f[i+1][j],f[i][j]+a[(i+1)*l1+j*l2]-a[i*l1+j*l2+1]);
            if(j < n2) f[i][j+1] = std::min(f[i][j+1],f[i][j]+a[i*l1+(j+1)*l2]-a[i*l1+j*l2+1]);
        }
    }
    printf("%lld\n",f[n1][n2]);
    return 0;
}
