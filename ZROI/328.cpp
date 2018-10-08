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

const int MAXN = 3000000 + 5;
int N;
int f[29][MAXN],g[20][MAXN];
int a[MAXN];
float log2N;

inline int gcd(int a,int b){
    if(!b) return a;
    return gcd(b,a%b);
}

inline void init(){
    log2N = log2(N)+1;
    FOR(i,1,log2N)
        for(int j = 1;j+(1<<i)-1 <= N;j++)
            f[i][j] = std::min(f[i-1][j],f[i-1][j+(1<<(i-1))]);
    FOR(i,1,log2N)
        for(int j = 1;j+(1<<i)-1 <= N;j++)
            g[i][j] = gcd(g[i-1][j],g[i-1][j+(1<<(i-1))]);
}

inline int qmin(int l,int r){
    int k = log2(r-l+1);
    return std::min(f[k][l],f[k][r-(1<<k)+1]);
}

inline int qgcd(int l,int r){
    int k = log2(r-l+1);
    return gcd(g[k][l],g[k][r-(1<<k)+1]);
}

inline bool check(int x){
    FOR(i,1,N){
        int j = i+x-1;
        if(j > N) return false;
        if(qmin(i,j) == qgcd(i,j)) return true;
    }
    return false;
}

int ans[MAXN],cnt;

int main(){
    read(N);
    FOR(i,1,N){
        read(a[i]);
        f[0][i] = g[0][i] = a[i];
    }
    init();
    int l=1,r=N;
    while(l < r){
        int mid = (l + r) >> 1;++mid;
        if(check(mid)) l = mid;
        else r = mid - 1;
    }
    FOR(i,1,N){
        int j = i + l - 1;
        if(j > N) break;
        if(qgcd(i,j) == qmin(i,j)){
            ans[++cnt] = i;
        }
    }
    printf("%d %d\n",cnt,l-1);
    FOR(i,1,cnt){
        printf("%d%c",ans[i],(i == cnt) ? '\n' : ' ');
    }
    return 0;
}