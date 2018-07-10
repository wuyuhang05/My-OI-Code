#include <algorithm>
#include <iostream>
#include <cstring>
#include <climits>
#include <cstdlib>
#include <cstdio>
#include <queue>
#include <stack>
#include <map>
#include <set>

#define DEBUG(x) std::cerr << #x << '=' << x << std::endl
using std::max;
#define LL long long

const int MAXN = 100000 + 5;
int N,M;
LL L,R;
LL a[MAXN];

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

int main(){
	scanf("%d%d",&N,&M);
	//DEBUG(N);DEBUG(M);
	for(int i = 1;i <= N;i++){
		scanf("%lld",&a[i]);
		R += a[i];
		L = max(L,a[i]);
	}
	while(L < R){
		//DEBUG(L);DEBUG(R);
		LL mid = L + (R - L >> 1);
		if(check(mid)) R = mid;
		else L = mid + 1;
	}
	printf("%lld",(L + R)/2);
	getchar();getchar();
	return 0;
}