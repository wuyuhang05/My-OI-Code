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
const int MAXN = 100+5;
const int MAXM = 10+2;
const int MAXX = (1<<10)+2;

int map[MAXN],N,M;
char str[MAXN];
int state[(1<<MAXM)+3],size;
int f[MAXN][MAXX][MAXX];
// ����ǰ i �У�i-1��״̬Ϊj��i��״̬Ϊk�����ڷŷ���
int status[MAXX],cnt[MAXX]; 

inline int get(int x){
	#define lowbit(x) (x&-x)
	int res = 0;
	while(x){
		res++;
		x -= lowbit(x);
	}
	return res;
	#undef lowbit
}

int main(){
	scanf("%d%d",&N,&M);
	FOR(i,1,N){
		scanf("%s",str+1);
		FOR(j,1,M) map[i] = (map[i] << 1) + (str[j] == 'H' ? 1 : 0);
	}
	int MAX = (1<<M)-1;
	FOR(i,0,MAX){
		if((!((i<<1) & i)) && (!((i<<2) & i)) && (!((i>>1) & i)) && (!((i>>2) & i))){
			state[++size] = i;
			cnt[size] = get(i);
			if(!(i&map[1])) f[1][0][size] = cnt[size];
		}
	}
	FOR(i,1,size) FOR(j,1,size) if(!(state[i]&state[j]) && !(state[j]&map[2])) f[2][i][j] = std::max(f[2][i][j],f[1][0][i]+cnt[j]);
	FOR(i,3,N){
		FOR(j,1,size){ // now
			if(map[i]&state[j]) continue;
			FOR(k,1,size){ // i-1
				if(state[j]&state[k]) continue;
				FOR(l,1,size){// i-2
					if(!(state[k]&state[l]) && !(state[l]&state[j])) f[i][k][j] = std::max(f[i][k][j],f[i-1][l][k]+cnt[j]);
				}
			}
		}
	}
	int ans = 0;
	FOR(i,1,size) FOR(j,1,size) ans = std::max(ans,f[N][i][j]);
	printf("%d\n",ans);
	return 0;
}
