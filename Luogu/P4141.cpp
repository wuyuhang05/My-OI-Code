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

const int MAXN = 2000 + 5;
const int ha = 10;

int a[MAXN],f[MAXN],c[MAXN][MAXN];
int N,M;

int main(){
	scanf("%d%d",&N,&M);
	for(int i = 1;i <= N;i++)
		scanf("%d",a + i);
	f[0] = 1;
	for(int i = 1;i <= N;i++)
		for(int j = M;j >= a[i];j--)
			f[j] = (f[j] + f[j-a[i]])%ha;
	for(int i = 1;i <= N;i++){
		c[i][0] = 1;
		for(int j = 1;j <= M;j++){
			if(j >= a[i]) c[i][j] = (f[j] - c[i][j-a[i]] + ha) % ha;
			else c[i][j] = f[j];
			printf("%d",c[i][j]);
		}
		puts("");
	}	
	getchar();getchar();
	return 0;
}