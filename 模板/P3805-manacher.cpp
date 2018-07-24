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

const int MAXL = 11000000 + 5;

char str[MAXL << 1],a[MAXL];
int p[MAXL << 1];
int len;

void manacher(){
	int maxright = 0,mid;
	for(int i = 1;i < len;i++){
		if(i < maxright)
			p[i] = std::min(p[(mid << 1) - i],p[mid] + mid - i);
		else p[i] = 1;
		for(;str[i+p[i]] == str[i-p[i]];p[i]++);
		if(p[i] + i > maxright){
			maxright = p[i] + i;
			mid = i;
		}
	}
}

void change(){
	str[0] = str[1]= '#';
	for(int i = 0;i < len;i++){
		str[(i << 1) + 2] = a[i];
		str[(i << 1) + 3] = '#';
	}
	len = (len << 1) + 2;
	str[len] = 0;
}

int main(){
	int ans = 1;
	scanf("%s",a);
	len = strlen(a);
	change();
	manacher();
	for(int i = 0;i < len;i++)
		ans = std::max(ans,p[i]);
	printf("%d\n",ans-1);
	getchar();getchar();
	return 0;
}