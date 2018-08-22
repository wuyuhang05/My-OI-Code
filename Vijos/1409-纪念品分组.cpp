#include <iostream>
#include <cstdio>
#include <cstring>
#include <algorithm>

const int MAXN = 30000 + 5;

int a[MAXN],ans;

int main(){
	int W,N;
	scanf("%d%d",&W,&N);
	for(int i = 1;i <= N;i++)	
		scanf("%d",&a[i]);
	std::sort(a + 1,a + N +1);
	int i = 1,j = N;
	while(i <= j){
		if(a[i] + a[j] > W){
			j--;
			ans++;
		}
		else{
			i++;j--;ans++;
		}
	}
	printf("%d",ans);
	return 0;
} 
