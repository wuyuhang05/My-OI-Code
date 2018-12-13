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

inline char nc(){
	#define SIZE 100000
	static char buf[SIZE],*p1 = buf+SIZE,*pend = buf+SIZE;
	if(p1 == pend){
		p1 = buf;pend = buf + fread(buf,1,SIZE,stdin);
		if(p1 == pend) return -1;
	}
	return *p1++;
}

inline void read(int &x){
	char ch = nc();
	x = 0;int flag = 1;
	while(!isdigit(ch)){
		if(ch == '-') flag = -1;
		ch = nc();
	}
	while(isdigit(ch)){
		x = (x << 1) + (x << 3) + (ch ^ '0');
		ch = nc();
	}
	x *= flag;
}

const int MAXN = 80000+5;

int N,opt,mod,min,max;
int final;
LL c[MAXN];
int sum[MAXN];

inline void Read(){
	scanf("%d%d%d%d%d",&N,&opt,&mod,&min,&max);
}

char str[20];

inline void Pretest(){
	while(opt--){
		scanf("%s",str);
		if(str[0] == 'A'){
			int L,R,x;scanf("%d%d%d",&L,&R,&x);
			c[L] += x;c[R+1] -= x;
		}
		else{
			int L,R,ans = 0;scanf("%d%d",&L,&R);
			LL now = 0ll;
			FOR(i,1,R){
				now += c[i];
				if(L <= i && (now*i)%mod >= min && (now*i)%mod <= max) ans++;
			}
			printf("%d\n",ans);
		}
	}
}

inline void Finaltest(){
	FOR(i,1,N) c[i] += c[i-1];
	FOR(i,1,N){
		sum[i] = sum[i-1];
		if((1ll*c[i]*i)%mod >= min && (1ll*c[i]*i)%mod <= max) sum[i]++;
	}
	scanf("%d",&final);
	while(final--){
		int l,r;scanf("%d%d",&l,&r);
		printf("%d\n",sum[r]-sum[l-1]);
	}
}

int main(){
	Read();
	Pretest();
	Finaltest();
	return 0;
} 
