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

const int MAXN = 1000 + 5;

int a[MAXN][MAXN],b[MAXN][MAXN];
int N,M;
#define P std::pair<int,int>
#define MP std::make_pair
int p[MAXN],top,ans;

int main(){
    read(N);read(M);
    FOR(i,1,N) FOR(j,1,M) read(a[i][j]),b[i][j] = 1;
    FOR(j,2,M){
        FOR(i,2,N){
            if(a[i][j]+a[i-1][j-1] <= a[i-1][j] + a[i][j-1])
                b[i][j] = b[i-1][j]+1;
        }
    }
    FOR(i,1,N) FOR(j,1,M) if(b[i][j] == 1) --b[i][j];
    p[0] = 1;
    FOR(i,2,N){
        int h = 0;
        FOR(j,2,M){
            while(h&&b[i][j] <= b[i][p[h]]){
                ans = std::max(ans,b[i][p[h]]*(j-p[h-1]));
                h--;
            }
            p[++h] = j;
            // DEBUG(h);
        }
        while(h){
            ans = std::max(ans,b[i][p[h]]*(M+1-p[h-1]));
            h--;
        }
    }
    printf("%d\n",ans);
    return 0;
}