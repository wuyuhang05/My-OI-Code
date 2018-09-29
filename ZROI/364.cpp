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

const int MAXN = 100000 + 5;

LL N,M,S,T,sum;
LL a[MAXN],p[MAXN],top;
LL f[51][MAXN][2];
LL tot[51][MAXN];
LL limit;

LL dfs(LL x,LL y,LL z){ // f[x][y][z] 答案的后 i 位，其中 j 个回到了环的开始（进位）
    if(x == M) return z == 0;
    if(f[x][y][z] != -1) return f[x][y][z];
    LL &ans = f[x][y][z];
    LL a = tot[x][y],b = y-a; // a: 找进位过的 y 个数中 x 位多少个是 ‘1’，b: 进位的 y 个数多少个是 ‘0’ 
    LL c = tot[x][N] - a,d = N - y - c; // c: 找没有进位的数中 x 位多少个是 ‘1’，d: 找没有进位的数中 x 位多少个是 ‘0’
    LL t = (S >> x) & 1;
    // printf("%lld %lld %lld %lld %lld\n",a,b,c,d,t);
    ans = 0;
    if(((b + c) & 1) == t) ans += dfs(x + 1,a,(limit >> x) & 1 ? 0 : z); // 不进位情况二进制位答案与期望答案相同
    if(((a + d) & 1) == t) ans += dfs(x + 1,a + b + c,(limit >> x) & 1 ? z : 1);
    return ans;
}

LL calc(LL x){
    limit = x - 1;
    CLR(f,-1);
    return dfs(0,0,0);
}

int main(){
    read(N);read(M);read(S);read(T);
    FOR(i,1,N) read(a[i]),sum ^= a[i];
    FOR(i,0,M-1){ // 二进制拆分
        FOR(j,1,N) // tot[i][j]: 处理进位
            tot[i][j] = tot[i][j-1] + ((a[j] >> i) & 1);
        top = 0;
        FOR(j,1,N){ // 按照这一位有没有 ‘1’ 来排序
            if((a[j] >> i) & 1)
                p[++top] = a[j];
        }
        FOR(j,1,N){
            if((a[j] >> i) & 1);
            else p[++top] = a[j];
        }
        std::swap(p,a);
        // FOR(j,1,N) std::swap(a[i],p[i]);
    }
    LL times = T >> M;
    printf("%lld\n",calc(1ll << M) * times + calc(T - (times << M) + 1) - (sum == S));
    return 0;
}