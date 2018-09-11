#include <algorithm>
#include <iostream>
#include <cstring>
#include <climits>
#include <cstdlib>
#include <cstdio>
#include <cmath>
#include <queue>
#include <set>
#include <map>
#define U unsigned
#define LL long long
#define FOR(i,a,b) for(int i = a;i <= b;i++)
#define RFOR(i,a,b) for(int i = a;i >= b;i--)
#define CLR(i,x) memset(i,x,sizeof(i))
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

inline LL qpow(LL a,LL n){
	LL ret = 1ll;
	while(n){
		if(n & 1) ret = (ret * a);
		a = (a * a);
		n >>= 1;
	}
	return ret;
}

int N,M,v,sum;
const int MAXN = 50 + 5;
double f[MAXN][MAXN*MAXN*MAXN][2]; 

int main(){
	read(N);read(M);read(v);read(sum);
	double ans = 0;
	f[0][0][0] = 1;
	FOR(i,1,N){ // ci shu
		FOR(j,0,N*M){
			FOR(k,1,M){
				f[i][j+k][1] += (double)f[i-1][j][1];
				if(k == v) f[i][j+k][1] += (double)f[i-1][j][0];
				else f[i][j+k][0] += (double)f[i-1][j][0];
			}
		}
	}
	FOR(i,0,N*M) ans += (double)f[N][i][1]; // DEBUG(ans);
	printf("%.10f\n",(double)f[N][sum][1]/(double)ans);
	return 0;
}

