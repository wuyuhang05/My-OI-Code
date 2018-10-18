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

const int MAXN = 50000 + 5;
#define int long long
std::vector<LL> v[MAXN];
LL tag[MAXN],value[MAXN];
int block[MAXN];
int N,BLOCK;

void reset(int x){
	v[x].clear();
	int k = std::min(BLOCK*x,N);
	FOR(i,BLOCK*(x-1)+1,k) v[x].push_back(value[i]);
	std::sort(v[x].begin(),v[x].end());
}

void add(int l,int r,int delta){
	int k = std::min(block[l]*BLOCK,r);
	FOR(i,l,k) value[i] += delta;
	reset(block[l]);
	if(block[l] != block[r]){
		FOR(i,(block[r]-1)*BLOCK+1,r) value[i] += delta;
		reset(block[r]);
	}
	FOR(i,block[l]+1,block[r]-1) tag[i] += delta;
}

int query(int l,int r,int x){
	int ans = 0;
	int k = std::min(block[l]*BLOCK,r);
	FOR(i,l,k) ans = (value[i] + tag[block[l]] < x) ? ans + 1 : ans;
	if(block[l] != block[r]){
		FOR(i,(block[r]-1)*BLOCK+1,r)
			ans = (value[i] + tag[block[r]] < x) ? ans + 1 : ans;
	}
	FOR(i,block[l]+1,block[r]-1) ans += std::lower_bound(v[i].begin(),v[i].end(),x-tag[i])-v[i].begin();
	return ans;
}

signed main(){
	read(N);BLOCK = std::sqrt(N);
	FOR(i,1,N){
		block[i] = (i-1)/BLOCK + 1;
		read(value[i]);
		v[block[i]].push_back(value[i]);
	}
	FOR(i,1,block[N]) std::sort(v[i].begin(),v[i].end());
	FOR(i,1,N){
		int opt,l,r,x;
		read(opt);read(l);read(r);read(x);
		if(!opt){
			add(l,r,x);
		}
		else{
			printf("%lld\n",query(l,r,x*x));
		}
	}
	return 0;
}

