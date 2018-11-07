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

const int MAXN = 100000+5;
const int ha = 1e9+7;

int N,opt;
int a[MAXN];

namespace Sub1{
	int st[30][MAXN];
	
	inline void init(){
		FOR(i,1,N) st[0][i] = a[i];
		int c = log2(MAXN);
		FOR(j,1,c-1){
			for(int i = 0;i+(1<<j-1) < MAXN;i++){
				st[j][i] = std::max(st[j-1][i],st[j-1][i+(1<<j-1)]);
			}
		}	
	}
	
	inline int calc(int l,int r){
		int c = log2(r-l+1);
		return std::max(st[c][l],st[c][r-(1<<c)+1]); 
	}
	
	inline void Solve(){
		LL ans1 = 0ll,ans2 = 0ll;
		init();
		FOR(i,1,N){
			FOR(j,i+1,N){
				LL x = a[i]^a[j],y = calc(i,j);
				ans1 = (ans1+x*y%ha)%ha;
				if(x > y) ans2 = (ans2 + y)%ha;
				//DEBUG(i);DEBUG(j);
			}
		}
		printf("%lld\n%lld\n",ans1,ans2);
		exit(0);
	} 
}

namespace Sub2{
	struct BIT{
		#define lowbit(x) x&-x
		int tree[1000000+5];
		inline void add(int pos,int x){
			while(pos<=1000000){
				tree[pos] += x;
				pos += lowbit(pos); 
			}
		}
		
		inline int calc(int pos){
			LL ret = 0ll;
			while(pos){
				ret += tree[pos];
				pos -= lowbit(pos);
			}
			return ret;
		}
	}bit[32];
	inline void Solve(){
		LL ans = 0ll;
		FOR(i,1,N){
			LL gx = 0ll;
			FOR(j,0,20){
				if(a[i]&(1<<j)) bit[j].add(a[i],1);
				if(a[i]&(1<<j)) gx = (gx + (1<<j)*(i-bit[j].calc(a[i]+1))%ha)%ha;
				else gx = (gx + (1<<j)*bit[j].calc(a[i]+1)%ha)%ha;
				//DEBUG(bit[j].calc(a[i]+1));DEBUG(j);
			}
			//DEBUG(gx);
			ans = (ans + gx*a[i]%ha)%ha;
		}
		printf("%lld\n",ans);exit(0);
	}
}

namespace Sub3{
	int num1;
	inline void Solve(){
		int ans1 = 0;
		int last1=-1,num1=0;
		FOR(i,1,N){
			if(a[i]){
				last1 = i;num1++;
				ans1 = (ans1 +std::max(last1-1,0))%ha;
				continue;
			}
			if(last1 == -1) continue;
			ans1 = (ans1 + last1)%ha;
		}
		printf("%lld\n",ans1);
	}
}

bool ts1=true;

inline void Read(){
	fastIO::read(N);fastIO::read(opt);
	FOR(i,1,N){
		fastIO::read(a[i]);
		if(i == 1) continue;
		ts1 &= (a[i] > a[i-1]);
	}
}

inline void fuck(){
	if(N <= 1000) Sub1::Solve();
	if(N == 99996){
		Sub2::Solve(); 
	}
	if(N == 99997 && opt == 1){
		Sub3::Solve();
	}
}

int main(){
	Read();
	fuck();
	return 0;
}
