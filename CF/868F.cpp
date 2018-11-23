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
const int MAXM = 20 + 5;

int f[MAXN][MAXM];
int N,K,L=1,R;
int a[MAXN];
int cnt[MAXN],ans,t[MAXN];

inline int calc(int l,int r){
	while(L > l) ans += cnt[a[--L]]++;
	while(R < r) ans += cnt[a[++R]]++;
	while(L < l) ans -= --cnt[a[L++]];
	while(R > r) ans -= --cnt[a[R--]];
	return ans;
}

void work(int k,int l,int r,int pl,int pr){
	if(l > r) return;
	if(l == r){
		FOR(i,pl,pr) f[l][k] = std::min(f[l][k],f[i-1][k-1]+calc(i,l));
		return;
	}
	int mid = (l + r) >> 1;
	FOR(i,pl,pr) t[i] = f[i-1][k-1] + calc(i,mid);
	int next = 0;
	FOR(i,pl,pr){
		if(!next || t[i] < t[next]) next = i;
	}
	f[mid][k] = t[next];
	work(k,l,mid-1,pl,next);
	work(k,mid+1,r,next,pr);
}

signed main(){
	scanf("%I64d%I64d",&N,&K);
	FOR(i,1,N) scanf("%I64d",a+i);
	CLR(f,0x7f);
	f[0][0] = 0;
	FOR(i,1,K) work(i,1,N,1,N);
	printf("%I64d\n",f[N][K]);
	return 0;
}
/*
 f[i][j] 前 i 个分成 j 段的最小代价
 f[i][j] = min{f[k][j-1] + w(k+1,i)}
*/
 
