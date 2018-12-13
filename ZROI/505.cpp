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
#define MP std::make_pair
#define CLR(i,a) memset(i,a,sizeof(i))
#define BR printf("--------------------\n")
#define DEBUG(x) std::cerr << #x << '=' << x << std::endl

const int ha = 1000000000+7;

inline char nc(){
    #define SIZE 100000
    static char buf[SIZE],*p1=buf+SIZE,*pend=buf+SIZE;
    if(p1 == pend){
        p1 = buf;pend = buf+fread(buf,1,SIZE,stdin);
        if(p1 == pend) return -1;
    }
    return *p1++;
}

inline void read(int &x){
    x = 0;int flag = 1;
    char ch = nc();
    while(!isdigit(ch)){
        if(ch == '-') flag = -1;
        ch = nc();
    }
    while(isdigit(ch)){
        x = (x<<1) + (x<<3) + (ch^'0');
        ch = nc();
    }
    x *= flag;
}

inline void read(LL &x){
    x = 0;int flag = 1;
    char ch = nc();
    while(!isdigit(ch)){
        if(ch == '-') flag = -1;
        ch = nc();
    }
    while(isdigit(ch)){
        x = (x<<1) + (x<<3) + (ch^'0');
        ch = nc();
    }
    x *= flag;
}

const int MAXN = 20+5;
const int MAXM = 100000+5;

LL f[MAXN][MAXM],c[MAXN][MAXM];
int top;
std::pair<int,int> S[MAXM];
int N,M;

inline void pre(){
    top = 0;
    FOR(i,1,20) FOR(j,1,N) f[i][j] = (f[i][j-1]+f[i-1][j])%ha;
}

signed main(){
    read(N);read(M);
    c[0][1] = 1;
    FOR(i,1,20) FOR(j,1,N) c[i][j] = (c[i][j-1]+c[i-1][j])%ha;
    FOR(i,1,N) read(f[0][i]);
    pre();
    while(M--){
        int opt,x,y;
        read(opt);read(x);read(y);
        if(opt & 1){
            S[++top] = MP(x,(y-f[0][x]+ha+ha)%ha);
            f[0][x] = y;
            if(top > 1500) pre();
        }
        else{
            LL ans = f[x][y];
            if(x) FOR(i,1,top) if(y-S[i].first >= 0) ans = (ans + 1ll*S[i].second*c[x][y-S[i].first+1])%ha;
            printf("%lld\n",ans);
        }
    }
    return 0;
}