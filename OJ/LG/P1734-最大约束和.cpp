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

const int MAXN = 1000;

int S;
int f[MAXN * 2],w[MAXN];

int main(){
	scanf("%d",&S);
	for(int i = 1;i <= S;i++){
		for(int j = i * 2;j <= S;j+=i)
			w[j] += i;
	}
	for(int i = 1;i <= S;i++)
		for(int j = S;j >= i;j--)
			f[j] = std::max(f[j],f[j-i] + w[i]);
	printf("%d",f[S]);
	return 0;
}