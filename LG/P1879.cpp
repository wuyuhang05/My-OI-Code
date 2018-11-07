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

const int ha = 1000000000;
const int MAXN = 13;
int map[MAXN],N,M;
int f[MAXN][(1<<MAXN)+5];
int state[(1<<MAXN)+5];

int main(){
	read(N);read(M);
	FOR(i,1,N){
		map[i] = 0;
		FOR(j,1,M){
			int x;read(x);
			map[i] = (map[i]<<1)+x;
		}
	}
	int MAX = (1<<M)-1;
	FOR(i,0,MAX) state[i] = (!(i&(i<<1)) && !(i&(i>>1)));
	f[0][0] = 1;
	FOR(i,1,N){
		FOR(now,0,MAX){
			if(state[now] && ((now&map[i]) == now)){
				FOR(last,0,MAX){
					if(!(now & last)){
						f[i][now] = (f[i][now] + f[i-1][last])%ha;
					}
				}
			}
		}
	}
	int ans = 0;
	FOR(i,0,MAX){
		ans = (ans + f[N][i])%ha;
	}
	printf("%d\n",ans);
	return 0;
}
/*
12 3
1 1 1
1 1 0
1 0 1
0 1 1
1 1 0
1 1 1
1 0 0
1 1 1
1 0 1
1 1 1
0 1 0
1 0 0

*/
