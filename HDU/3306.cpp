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
#define int LL
const int MAXN = 4;
const int ha = 10007;

struct Matrix{
    int a[MAXN][MAXN];

    inline void clear(){
        CLR(a,0);
    }

    Matrix operator * (const Matrix &other) const {
        Matrix res;res.clear();
        FOR(i,0,3){
            FOR(j,0,3){
                FOR(k,0,3){
                    res.a[i][j] += (this->a[i][k]*other.a[k][j])%ha;
                    res.a[i][j] %= ha;
                }
            }
        }
        return res;
    }

    Matrix operator ^ (int k) const {
        Matrix res,a;res.clear();
        a = *this;
        FOR(i,0,3) res.a[i][i] = 1;
        while(k){
            if(k & 1) res = res*a;
            a = a*a;
            k >>= 1;
        }
        return res;
    }
}A;

signed main(){
    int N,X,Y;
    A.a[0][0] = A.a[1][0] = A.a[2][0] = A.a[3][0] = 1;
    while(~scanf("%lld%lld%lld",&N,&X,&Y)){
        Matrix x;x.clear();X %= ha;Y %= ha;
        x.a[0][0] = x.a[0][1] = x.a[2][1] = 1;
        x.a[1][1] = (X*X)%ha;
        x.a[1][2] = (Y*Y)%ha;
        x.a[1][3] = (2*X*Y)%ha;
        x.a[3][1] = X;
        x.a[3][3] = Y;
        Matrix ans = x^N;
        ans = ans*A;
        printf("%lld\n",ans.a[0][0]%ha);
    }
    return 0;
}