#include <iostream>
#include <cstdio>
#include <cstring>
#include <algorithm>
#include <queue>

#define LL long long

struct Tree{
	LL v,h;
	
	bool operator < (const Tree &a) const {
		if(v != a.v) return v > a.v;
		return h > a.h;
	}
};

std::priority_queue<Tree> q;
int N,K;

int main(){
	scanf("%d %d",&N,&K);
	for(int i = 1;i <= N;++i){
		Tree a;
		scanf("%lld",&a.v);
		a.h = 1;
		q.push(a);
	}
	LL top = 0;
	if((N-1) % (K-1) != 0) top += K-1-(N-1)%(K-1);
	for(int i = 1;i <= top;i++){
		Tree need;
		need.v = 0;need.h = 1;
		q.push(need);
	}
	top += N;
	LL ans = 0;
	while(top != 1){
		Tree a;
		LL t = 0,max = 0;
		for(int i = 1;i <= K;i++){
			a = q.top();
			t += a.v;
			max = std::max(max,a.h);
			q.pop();
		}
		ans += t;
		a.v = t;
		a.h = max + 1;
		q.push(a);
		top -= K-1;
	}
	printf("%lld\n%lld\n",ans,q.top().h-1);
	return 0;
}
