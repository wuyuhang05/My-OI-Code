// TODO: uplode to Online Judge
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
// using namespace fastIO;

const int MAXN = 1000000 + 5;
int N;
char str[MAXN];
LL f[MAXN][2];

bool equ(const std::string &x,int i){
    int cnt = i,len = x.length();// DEBUG(len);
    RFOR(i,len-1,0){
        if(str[cnt] != x[i]) return false;
        cnt--;
    }
    return true;
}

const int ha = 1000000000 + 7;

int main(){
    scanf("%s",str + 1);
    N = strlen(str + 1);// DEBUG(N);
    f[0][0] = 1;
    FOR(i,1,N){
        if(i >= 1) f[i][0] = (f[i][0] + f[i-1][0] + f[i-1][1])%ha;
        if(i >= 2) f[i][0] = (f[i][0] + f[i-2][0] + f[i-2][1])%ha;
        if(i >= 3){
            if(equ("010",i))
                f[i][0] = (f[i][0] + f[i-3][0])%ha;
            else f[i][0] = (f[i][0] + f[i-3][0] + f[i-3][1])%ha;
        }
        if(i >= 4){
            if(equ("1100",i))
                f[i][1] = (f[i][1] + f[i-4][0] + f[i-4][1])%ha;
            // 1111 / 1110 / 0101 / 0011
            else if(equ("1111",i) || equ("1110",i) || equ("0101",i) || equ("0011",i));
            else f[i][0] = (f[i][0] + f[i-4][0] + f[i-4][1])%ha;
        }
    }
    printf("%lld\n",(f[N][0] + f[N][1])%ha);
    return 0;
}