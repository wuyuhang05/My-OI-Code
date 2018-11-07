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

const int MAXN = 9+1;
#define lowbit(x) (x&-x)
int status[(1<<MAXN)+1],cnt[(1<<MAXN)+1],size;
/// status 合法的情况，cnt 情况有多少个二进制1 
LL f[MAXN][MAXN*MAXN][(1<<MAXN)+1];
int N,K;

int main(){
	read(N);read(K);
	int MAX = (1<<N)-1;
	FOR(i,0,MAX){
		if(i & (i>>1)) continue;
		status[++size] = i;
		int x = i;
		while(x){
			x -= lowbit(x);
			cnt[size]++;
		}
	}
	FOR(i,1,size) f[1][cnt[i]][i] = 1;
	FOR(i,2,N){
		FOR(j,1,size){
			FOR(k,1,size){
				if((status[j]&status[k]) || (status[j]&status[k] << 1) || (status[j]&status[k] >> 1)) continue;
				FOR(l,cnt[k],K){
					f[i][l][k] += f[i-1][l-cnt[k]][j];
				}
			}
		}
	}
	LL ans=0;
	FOR(i,1,size) ans += f[N][K][i];
	printf("%lld\n",ans);
	return 0;
}

