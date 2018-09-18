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
// #define read(x) std::cin >> x

const int MAXN = 100000 + 5;
int N,M;int a[MAXN],b[MAXN],cnt;
bool bowl[MAXN];

int main(){
	// freopen("A.in","r",stdin);
	// freopen("A.out","w",stdout);
	read(N);read(M);
	FOR(i,1,M){
		read(a[i]);
		bowl[a[i]] = true;
	}
	FOR(i,1,N){
		if(!bowl[i])
		b[++cnt] = i;
	}
	int i = 1,j = 1;
	while(i <= M && j <= cnt){
		if(a[i] < b[j])
			printf("%d\n",a[i++]);
		else printf("%d\n",b[j++]);
	}
	while(i <= M) printf("%d\n",a[i++]);
	while(j <= cnt) printf("%d\n",b[j++]);
	return 0;
} 

