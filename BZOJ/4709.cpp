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
const int MAXN = 100000+5; 
int N;
int f[MAXN];
int num[MAXN],a[MAXN],s[MAXN];
std::vector<int> g[MAXN];

inline LL calc(int pos,int x){
	return f[pos-1]+a[pos]*x*x;
}

int get(int x,int y){
	int l=1,r=N,ans = N+1;
	while(l <= r){
		int mid = (l + r) >> 1;
		if(calc(x,mid-s[x]+1) >= calc(y,mid-s[y]+1)) ans = mid,r = mid-1;
		else l = mid+1;
	}
	return ans;
}

signed main(){
	scanf("%lld",&N);
	FOR(i,1,N){
		scanf("%lld",a+i);s[i] = ++num[a[i]];
		int len = g[a[i]].size();
		while(len >= 2 && get(g[a[i]][len-2],g[a[i]][len-1]) <= get(g[a[i]][len-1],i))
			len--,g[a[i]].pop_back();
		g[a[i]].push_back(i);++len;
		while(len >= 2 && get(g[a[i]][len-2],g[a[i]][len-1]) <= s[i])
			--len,g[a[i]].pop_back();
		f[i] = calc(g[a[i]][len-1],s[i]-s[g[a[i]][len-1]]+1);
	}
	printf("%lld\n",f[N]);
	return 0;
}
/*
f[i]: Ç°i¸ö 
f[i] = std::max(f[j-1] + a[i]*(s[i]-s[j]+1)^2)
*/
