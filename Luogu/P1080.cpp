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

const int MAXN = 1000 + 5;
const int MAXL = 20000 + 5;

struct Node{
    int a,b;
    LL ab;
    bool operator < (const Node &other) const {
        return ab < other.ab;
    }
}p[MAXN];

int N;
int sum[MAXL],ans[MAXL],add[MAXL];

void times(int x){
    CLR(add,0);
    FOR(i,1,ans[0]){
        ans[i] = ans[i] * x;
        add[i+1] += ans[i] / 10;
        ans[i] %= 10;
    }
    FOR(i,1,ans[0] + 4){
        ans[i] += add[i];
        if(ans[i] >= 10){
            ans[i+1] += ans[i]/10;
            ans[i] %= 10;
        }
        if(ans[i]){
            ans[0] = std::max(ans[0],i);
        }
    }
}

void div(int x){
    CLR(add,0);
    int q = 0;
    RFOR(i,ans[0],1){
        q = q * 10 + ans[i];
        add[i] = q/x;
        if(!add[0] && add[i]) add[0] = i;
        q %= x;
    }
}

bool cmp(){
    if(sum[0] == add[0]){
        RFOR(i,add[0],1){
            if(add[i] > sum[i]) return true;
            if(add[i] < sum[i]) return false;
        }
    }
    if(add[0] > sum[0]) return true;
    return false;
}

inline void copy(){
    CLR(sum,0);
    RFOR(i,add[0],0){
        sum[i] = add[i];
    }
}

int main(){
    read(N);
    FOR(i,0,N){
        read(p[i].a),read(p[i].b);
        p[i].ab = p[i].a * p[i].b;
    }
    std::sort(p + 1,p + N + 1);
    ans[0] = ans[1] = 1;
    FOR(i,1,N){
        times(p[i-1].a);
        div(p[i].b);
        if(cmp()) copy();
    }
    RFOR(i,sum[0],1) printf("%d",sum[i]);
    return 0;
}
