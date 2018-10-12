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

const int MAXN = 1000 + 5;
int N,M;
LL L,R;
LL a[MAXN];
LL mincost;

bool check(LL k){
	LL sum = 0,cnt = 0;
	for(int i = 1;i <= N;i++){
		sum += a[i];
		if(sum > k){
			sum = a[i];
			cnt++;
		}
	}
	if(cnt <= M - 1) return true;
	return false;
}

const int ha = 998244353;

LL ans = 0;
int sum[MAXN];
int f[MAXN][MAXN];

int main(){
	scanf("%d%d",&N,&M);
	for(int i = 1;i <= N;i++){
		scanf("%lld",&a[i]);
		R += a[i];
		L = std::max(L,a[i]);
        sum[i] = sum[i-1] + a[i];
	}
	while(L < R){
		LL mid = L + (R - L >> 1);
		if(check(mid)) R = mid;
		else L = mid + 1;
	}
	mincost = (L + R) >> 1;
    printf("%lld\n",mincost);
    FOR(i,0,N) f[0][i] = 1;
    FOR(i,2,N) a[i] += a[i-1];
    FOR(i,1,M){
        int s = 1;
        FOR(j,0,N){
            while(a[j]-a[s-1]>mincost) ++s;
            f[i][j] += f[i-1][j];
            if(s > 1) f[i][j] += f[i-1][s];
        }
    }
	return 0;
}