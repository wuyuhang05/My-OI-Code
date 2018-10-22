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

const int MAXN = 1000 + 5;
const int MAXM = 100000 + 5;

int N,M;
int a[MAXN],b[MAXN];
int f[MAXM<<2];
int max,sum;

int gcd(int a,int b){
	return (!b) ? a : gcd(b,a%b);
}

struct Node{
	int a,b;
	
	Node(int a,int b) : a(a),b(b) {};
	
	bool operator < (const Node &other) const{
		//return a*other.b < b*other.a;
		return (double)a/(double)b < (double)other.a/(double)other.b;
	}
	// a/b < c/d
	// ad < bc
	
	inline int print(){
		int k = gcd(a,b);
		if(k == 0) return -1;
		printf("%d/%d\n",a/k,b/k);
	}
};
#define read(x) std::cin >> x
inline int randint(){
	return 1 + rand() % 10000;
}
int main(){
//	srand(time(NULL));
//	int aa = rand(),bb = rand()*rand();
//	DEBUG((bool)(gcd(aa,bb)==std::__gcd(aa,bb)));
	read(N);read(M);
	FOR(i,1,N){
		read(a[i]),read(b[i]);
		sum += a[i];
		max = std::max(max,a[i]);
	}
	if(sum < M){
		puts("-1");
		return 0;
	}
	CLR(f,-1);f[0] = 0;
	FOR(i,1,N){
		ROF(j,max+M-a[i],0){
			if(f[j] == -1) continue;
			f[j + a[i]] = std::max(f[j + a[i]],f[j] + b[i]);
		}
	}
	Node ans(0,1);
	FOR(i,M,M + max){
		if(f[i] == -1) continue;
		Node now(f[i],i);
		ans = std::max(ans,now);
	}
	ans.print();
	return 0;
}



