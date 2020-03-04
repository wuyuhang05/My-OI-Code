#include <algorithm>
#include <iostream>
#include <cstring>
#include <climits>
#include <cstdio>
#include <vector>
#include <cstdlib>
#include <ctime>
//#include <cmath>
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
const int MAXN = 12 + 5;
const int MAXX = (1<<12)+5;
int map[MAXN][MAXN];
int N,M;
int v[MAXX],pos[MAXX];
int log[MAXX],g[MAXX],state[MAXX];
int f[MAXN][MAXX];
#define lowbit(x) (x&-x)
signed main(){
	read(N);read(M);
	FOR(i,1,N) FOR(j,1,N) map[i][j] = INT_MAX;
	FOR(i,1,M){
		int u,v,w;read(u);read(v);read(w);
		map[u][v] = map[v][u] = std::min(map[u][v],w);
	}
	int MAX = (1<<N)-1;
	CLR(f,0x3f);
	FOR(i,0,N) f[1][1<<i] = 0;
	FOR(i,0,N) log[1<<i]=i;
	FOR(i,1,N){
		FOR(j,0,MAX){
			int cnt = 0;
			FOR(k,1,N){
				if(!(j&(1<<(k-1)))){
					cnt++;
					v[cnt] = INT_MAX;
					pos[cnt] = (1<<(k-1));
					int t = j;
					while(t){
						int e = log[lowbit(t)]+1;//DEBUG(e);
						if(map[k][e] < INT_MAX) v[cnt] = std::min(v[cnt],map[k][e]*i);
						t -= lowbit(t);
					}
				}
			}
			int size = (1<<cnt)-1;
			FOR(k,1,size){
				g[k] = g[k-lowbit(k)]+v[log[lowbit(k)]+1];
				state[k] = state[k-lowbit(k)] | pos[log[lowbit(k)]+1];
				f[i+1][j|state[k]] = std::min(f[i+1][j|state[k]],f[i][j]+g[k]);
			}
		}
	}
	int ans = INT_MAX;
	FOR(i,1,N) ans = std::min(ans,f[i][MAX]);
	printf("%lld\n",ans);
	return 0;
}

