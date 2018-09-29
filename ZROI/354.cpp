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
#define FOR(i,a,b) for(Re LL i = a;i <= b;++i)
#define RFOR(i,a,b) for(Re LL i = a;i >= b;--i)
#define SFOR(i,a,b,c) for(Re LL i = a;i <= b;i+=c)
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
// using namespace fastIO;

const int MAXN = 200000 + 5;

LL T,N;
int a[MAXN],b[MAXN];
char str[MAXN];
char ch;

inline void solve(){
    #define BFOR(i,a,b) for(LL i = a;i <= b;i <<= 1)
    LL len = 2*N+2;
    BFOR(S,1,T){
        if(T&S){
            FOR(i,1,N){
                LL l = i-S%len,r = i+S%len;
                if(l < 0) l = -l;
                if(l > N+1) l = len-l;
                if(r > N+1) r = len-r;
                if(r < 0) r = -r;
                b[i] = a[l] ^ a[r];
            }
            // std::swap(a,b);
            FOR(i,1,N) a[i] = b[i];
        }
    }
    #undef BFOR
}

int main(){
    scanf("%lld%lld",&T,&N);
    scanf("%s",str + 1);
    FOR(i,1,N){
        a[i] = str[i] - '0';
    }   
    solve();
    FOR(i,1,N) putchar(a[i]+'0');
    puts("");
    return 0;
}
