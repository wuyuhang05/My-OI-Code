#include <algorithm>
#include <iostream>
#include <cstring>
#include <climits>
#include <cstdlib>
#include <cstdio>
#include <cmath>
#include <queue>
#include <stack>
#include <map>
#include <set>
#define lowbit(x) x&(-x)

const int MAXN = 40000 + 5;

int a[MAXN],origin[MAXN];

int N,ans;
int c[MAXN * 2];

std::map<int,int> S;

void add(int x,int k){
	for(int i = x;i <= N;i += lowbit(i))
		c[i] += k;
}

int query(int x){
	int sum = 0;
	for(int i = x;i > 0;i -= lowbit(i))
		sum += c[i];
	return sum;
}

int main(){
	scanf("%d",&N);
	for(int i = 1;i <= N;i++){
		scanf("%d",&a[i]);a[i] = -a[i];
		S.insert(std::make_pair(a[i],0));
	}
	int tN = 0;
	for(std::map<int,int>::iterator it = S.begin();it != S.end();it++){
		it->second = ++tN;
		origin[tN] = it->first;
	}
	for(int i = 1;i <= tN;i++)
		a[i] = S[a[i]];
	for(int i = 1;i <= N;i++){
		add(a[i],1);
		ans += query(a[i] - 1);
	}
	printf("%d\n",ans);
	getchar();getchar();
	return 0;
}