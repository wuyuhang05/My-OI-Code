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
const int MAXN = 100000+5;
int a[MAXN],N;
int ans,pre=1,sum;
// ceil(a[i]/2) ~ a[i]

signed main(){
    read(N);
    FOR(i,1,N) read(a[i]),sum += a[i];
    std::sort(a+1,a+N+1);
    FOR(i,1,N){
        int t = ceil((1.0*a[i])/2.0);
        //DEBUG(t);DEBUG(pre);
        if(t > pre) ans += t-pre;
        pre += a[i];
    }
    printf("%lld\n",sum-ans);
    system("pause");
    return 0;
}
/*
95
97 88 93 95 87 99 88 96 90 96 89 90 11 1 89 94 95 99 96 94 93 94 89 89 100 99 87 89 95 89 87 94 93 93 92 100 98 91 93 91 88 98 87 92 94 98 10 87 87 12 90 100 97 93 87 91 88 87 88 91 87 96 94 96 96 93 1 100 94 96 89 1 100 100 97 89 98 90 97 89 1 92 1 89 98 87 88 90 95 95 96 94 98 88 93
ans: 8111
*/