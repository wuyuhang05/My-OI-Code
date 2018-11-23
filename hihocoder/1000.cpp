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

#define Re register
#define LL long long
#define U unsigned
#define FOR(i,a,b) for(Re int i = a;i <= b;++i)
#define ROF(i,a,b) for(Re int i = a;i >= b;--i)
#define CLR(i,a) memset(i,a,sizeof(i))
#define BR printf("--------------------\n")
#define DEBUG(x) std::cerr << #x << '=' << x << std::endl

inline char nc(){
#define BUF_SIZE 100000
    static char buf[BUF_SIZE],*p1=buf+BUF_SIZE,*pend = buf+BUF_SIZE;
    if(p1 == pend){
        p1 = buf;pend = buf+fread(buf,1,BUF_SIZE,stdin);
        if(p1 == pend) return  -1;
    }
    return *p1++;
}

inline void read(int &x){
    char ch = nc();
    int flag = 1;
    x = 0;
    while(!isdigit(ch)){
        if(ch == '-') flag = -1;
        ch = nc();
    }
    while(isdigit(ch)){
        x = (x << 1) + (x << 3) + ch^'0';
        ch = nc();
    }
    x *= flag;
}

int main(){
    int a,b;read(a);read(b);
    printf("%d\n",a+b);
    return 0;
}
