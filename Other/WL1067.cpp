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

struct BIT{
	#define lowbit(x) (x&-x)
	static const int SIZE = MAXN<<1;
	int tree[SIZE+20];
	inline void add(int pos,int x){
		while(pos <= SIZE){
			tree[pos] ^= x;
			pos += lowbit(pos);
		}
	}
	inline int calc(int pos){
		int ret = 0;
		while(pos){
			ret ^= tree[pos];
			pos -= lowbit(pos);
		}
		return ret;
	}
	#undef lowbit
}bit;
#define MP std::make_pair
int N,M;
std::vector<std::pair<int,int> > q[MAXN];
int a[MAXN];
std::map<int,int> last;
int pre[MAXN],ans[MAXN];
int sum[MAXN];

int main(){
	read(N);read(M);
	FOR(i,1,N){
		read(a[i]);
		pre[i] = last[a[i]];
		last[a[i]] = i;
		sum[i] = sum[i-1]^a[i];
	}
	FOR(i,1,M){
		int l,r;read(l);read(r);
		q[r].push_back(MP(l,i));
	}
	FOR(i,1,N){
		if(pre[i]) bit.add(pre[i],a[i]);
		bit.add(i,a[i]);
		FOR(j,0,(int)q[i].size()-1){
			int x = bit.calc(i)^bit.calc(q[i][j].first-1);
			ans[q[i][j].second] = x^sum[i]^sum[q[i][j].first-1];
		}
	}
	FOR(i,1,M) printf("%d\n",ans[i]);
	return 0;
}

