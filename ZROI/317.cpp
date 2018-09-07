#include <algorithm>
#include <iostream>
#include <cstring>
#include <climits>
#include <cstdio>
#include <vector>
#include <cmath>
#include <queue>
#include <stack>
#include <map>
#include <set>

#define R register
#define LL long long
#define U unsigned
#define FOR(i,a,b) for(R int i = a;i <= b;++i)
#define RFOR(i,a,b) for(R int i = a;i >= b;--i)
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

const int MAXN = 500000 + 5;
int size1,size2;

struct Values{
    int a,b;

    bool operator < (const Values &other) const {
        if(a == other.a) return b < other.b;
        return a < other.a;
    }
}v1[MAXN],v2[MAXN],s1[MAXN],s2[MAXN];

int N,Q;
// y=ax+b;

inline void pre(Values v[],Values s[],int &size){
    std::sort(v + 1,v + N + 1);
    FOR(i,1,N){
        while((size >= 1 && s[size].a == v[i].a) || (size >= 2 && (1ll * (s[size-1].b - s[size].b) * (v[i].a - s[size-1].a)) >= (1ll * (s[size-1].b - v[i].b) * (s[size].a - s[size-1].a))))
            size--;
        s[++size] = v[i];
    }
}

LL val(const Values &u,int x){
    return (LL)u.a * x + u.b;
}

inline LL find_max(Values s[],int size,int x){
    int l = 1,r = size;
    while(l < r){
        int mid = (l + r) >> 1;
        if(val(s[mid],x) > val(s[mid + 1],x))
            r = mid;
        else l = mid + 1;
    }
    return (LL)val(s[l],x)*x;
}

int main(){
    read(N);read(Q);
    FOR(i,1,N){
        read(v1[i].a);read(v1[i].b);
        v2[i].a = -v1[i].a;v2[i].b = -v1[i].b;
    }
    pre(v1,s1,size1);
    pre(v2,s2,size2);
    while(Q--){
        int x;read(x);
        if(!x){
            puts("0");
            continue;
        }
        if(x < 0) printf("%lld\n",-find_max(s2,size2,x));
        else printf("%lld\n",find_max(s1,size1,x));
    }
    return 0;
}
