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

const int MAXN = 100000 + 5;
int N,K,Q;
int a[MAXN<<1],sum[MAXN<<1],s[MAXN<<1];
int L,R;
int f[MAXN][30];

inline void pre(){
    FOR(i,1,N) f[i][0] = s[i];
    for(int j = 1;(1 << j) <= N;j++){
        for(int i = 1;i + (1 << j) - 1 <= N;i++){
            f[i][j] = std::max(f[i][j-1],f[i+(1<<(j-1))][j-1]);
        }
    }
}

inline int query(int l,int r){
    int c = log2(r-l+1);
    return std::max(f[l][c],f[r-(1<<c)+1][c]);
}

int main(){
    read(N);read(K);read(Q);
    FOR(i,1,N) read(a[i]),sum[i] = sum[i-1]+a[i];
    FOR(i,1,N-K+1) s[i] = sum[i+K-1]-sum[i-1];
    FOR(i,N-K+2,N) s[i] = sum[N] - sum[i-1] + sum[i-1+K-N];
    pre();
    L = 1;R = N-K+1;
    while(Q--){
        char ch = nc();
        if(ch == '?'){
            if(L < R) printf("%d\n",query(L,R));
            else printf("%d\n",std::max(query(L,N),query(1,R)));
        }
        else{
            if(--L == 0) L = N;
            if(--R == 0) R = N;
        }
    }
    return 0;
}
/*
5 3 4
1 0 0 1 1
?!!?
*/