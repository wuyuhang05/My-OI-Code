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

const int MAXN = 1000000+5;

int prime[MAXN],tot,d[MAXN];
bool p[MAXN],vis[MAXN];
int pos[MAXN];
inline void pre(){
	FOR(i,0,20) pos[1<<i] = i;
	p[1] = true;
	FOR(i,2,MAXN-1){
		if(!p[i]){
			prime[++tot] = i;d[i] = i;
		}
		for(int j = 1;j <= tot && i*prime[j] < MAXN;j++){
			p[i*prime[j]] = 1;d[i*prime[j]] = prime[j];
			if(!(i%prime[j])) break;
		}
	}
}

int c[MAXN],z[MAXN],size; 
int cnt[MAXN][21];
int msk[MAXN]; 
int opt,x,ans;
#define lowbit(x) (x&-x)
void dfs(int step,int gcd,int res){
	if(step > size){
		if(opt == 1) if(++cnt[gcd][res] == 1) msk[gcd] ^= 1<<res;
		if(opt == 2) if(!--cnt[gcd][res]) msk[gcd] ^= 1<<res;
		if(opt == 3) if(msk[gcd]) ans = std::min(ans,res+pos[lowbit(msk[gcd])]);
//		if(opt == 3){
//			DEBUG(res);
//			DEBUG(msk[gcd]);DEBUG(res+pos[lowbit(msk[gcd])]);
//			DEBUG(pos[lowbit(msk[gcd])]);DEBUG(lowbit(msk[gcd]));
//		}
		return;
	}
	FOR(i,0,c[step]){
		dfs(step+1,gcd,res+c[step]-i);
		gcd *= z[step];
	}
} 

void fjprime(int x){
	size = 0;
	while(x > 1){
		z[++size] = d[x];c[size] = 0;
		while(!(x%z[size])) x /= z[size],++c[size];
	}
}
//#define read(x) std::cin >> x
int main(){
	pre();
	int Q;
	read(Q);
	while(Q--){
		//int opt,x;
		read(opt);read(x);
		if((opt == 1 && vis[x]) || (opt == 2 && !vis[x])) continue;
		fjprime(x);//DEBUG(size);
		ans = INT_MAX;
		dfs(1,1,0);
		if(opt == 3) printf("%d\n",ans == INT_MAX ?-1 :ans);
		else vis[x] = opt == 1 ?1 :0;
	}
	return 0;
}
/*
12
1 20
1 15
3 30
1 30
3 30
2 10
3 27
1 15
2 15
2 20
2 30
3 5
*/

