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

const int MAXN = 3;
const int ha = 1e9+7;
#define int LL

struct Matrix{
    int a[MAXN][MAXN];

    inline void clear(){
        CLR(a,0);
    }

    Matrix operator * (const Matrix &other) const {
        Matrix res;res.clear();
        FOR(i,0,2){
            FOR(j,0,2){
                FOR(k,0,2){
                    res.a[i][j] += (this->a[i][k] * other.a[k][j]) % ha;
                    res.a[i][j] %= ha;
                }
            }
        }
        return res;
    }

    Matrix operator ^ (int k) const {
        Matrix res,a;res.clear();
        a = *this;
        FOR(i,0,2) res.a[i][i] = 1;
        while(k){
            if(k & 1) res = res*a;
            a = a*a;
            k >>= 1;
        }
        return res;
    }
}p;

inline void Solve(){
    int N;read(N);p.clear();
    p.a[0][2] = p.a[1][0] = p.a[2][1] = p.a[2][2] = 1;
    if(N <= 3) puts("1");
    else{
        Matrix ans = p^(N-3);
        printf("%lld\n",(ans.a[0][2]+ans.a[1][2]+ans.a[2][2])%ha);
    }
}

signed main(){
    int T;read(T);
    while(T--) Solve();
    system("pause");
    return 0;
}