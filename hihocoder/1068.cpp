#include <algorithm>
#include <iostream>
#include <cstring>
#include <climits>
#include <cstdlib>
#include <cstdio>
#include <vector>
#include <queue>
#include <stack>
#include <map>
#include <set>

#define Re register
#define LL long long
#define CLR(a,b) memset(a,b,sizeof(a))
#define FOR(i,a,b) for(Re int i = a;i <= b;++i)
#define ROF(i,a,b) for(Re int i = a;i >= b;--i)
#define DEBUG(x) std::cerr << #x << '=' << x << std::endl

inline char nc(){
    #define SIZE 100000
    static char buf[SIZE],*p1 = buf+SIZE,*pend = buf+SIZE;
    if(p1 == pend){
        p1 = buf;pend = buf+fread(buf,1,SIZE,stdin);
        if(p1 == pend) return -1;
    }
    return *p1++;
    #undef SIZE
}

inline void read(int &x){
    x = 0;char ch = nc();
    int flag = 1;
    while(!isdigit(ch)){
        if(ch == '-') flag = -1;
        ch = nc();
    }
    while(isdigit(ch)){
        x = (x<<3)+(x<<1)+(ch-'0');
        ch = nc();
    }
    x*=flag;
}

const int MAXN = 1000000+5;
int N,Q;
int f[50][MAXN];

inline void pre(){
    int c = log2(N);
    FOR(j,1,c){
        for(int i = 0;i+(1<<j-1) < MAXN;i++){
            f[j][i] = std::min(f[j-1][i],f[j-1][i+(1<<j-1)]);
        }
    }
}

inline int calc(int l,int r){
    int c = log2(r-l+1);
    return std::min(f[c][l],f[c][r-(1<<c)+1]);
}

int main(){
    read(N);
    FOR(i,1,N) read(f[0][i]);
    //FOR(i,1,N) DEBUG(f[0][i]);
    pre();
    read(Q);
    while(Q--){
        int l,r;read(l);read(r);
        printf("%d\n",calc(l,r));
    }
    system("pause");
    return 0;
}