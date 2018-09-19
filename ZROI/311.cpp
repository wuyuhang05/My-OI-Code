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
const int ha = 1000000000 + 7;
int N,p[MAXN];
int f[MAXN][MAXN],C[MAXN][MAXN];

int dfs(int n,int low){
    if(f[n][low] != -1) return f[n][low];
    if(n == 1) return f[n][low] = 1;
    int &ret = f[n][low];ret=0;
    int t[MAXN],cnt=0,j=1,k;
    FOR(i,1,N)
        if(p[i] >= low && p[i] < low + n)
            t[++cnt] = p[i];
    FOR(i,1,cnt-1){
        std::swap(t[i],t[i+1]);
        while(j <= i){
            if(t[j] >= low + i) break;j++;}
        k = i+1;
        while(k <= cnt){
            if(t[k] < low + i) break;k++;}
        DEBUG(i);DEBUG(j);
        if(j > i && k > cnt){
            LL t = (LL)dfs(i,low) * (LL)dfs(cnt-i,low+i) % ha;
            t = (t*C[cnt-2][i-1]) % ha;
            ret = (ret + t) % ha;
        }
        std::swap(t[i],t[i+1]);
    }
    return ret;
}

inline void init(){
    FOR(i,0,N){
        C[i][0] = 1;
        FOR(j,1,i){
            C[i][j] = (C[i-1][j] + C[i-1][j-1]) % ha;
        }
    }
    CLR(f,-1);
}

int main(){
    read(N);
    FOR(i,1,N) read(p[i]);
    init();
    dfs(N,0);
    if(f[N][0] != -1) printf("%d\n",f[N][0]);
    else puts("0");
   // system("Sleep 5");
    return 0;
}