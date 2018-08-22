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
#define LL long long

const int BASE = 20 + 5;
const int MAX_SUM = 200 + 5;

LL f[BASE][MAX_SUM][MAX_SUM][2];
int sum = 9 * 18 + 1;
LL a,b;
int dight[BASE];

LL pre(LL x,int ha){
	if(!x) return 0;
	memset(f,0,sizeof(f));
	int cnt = 0;
	while(x){
		dight[++cnt] = x % 10;
		x /= 10;
	}
	f[cnt + 1][0][0][0] = 1;
	for(int i = cnt + 1;i > 1;i--){
		for(int j = 0;j <= ha;j++){
			for(int k = 0;k < ha;k++){
				if(!f[i][j][k][0] && !f[i][j][k][1]) continue;
				for(int p = 0;p <= 9;p++){
					if(p < dight[i-1] && (j + p <= ha)) 
						f[i-1][j+p][(10 * k + p)%ha][1] += f[i][j][k][0];
					else if(p == dight[i-1] && (j + p <= ha))
						f[i-1][j+p][(10 * k + p)%ha][0] += f[i][j][k][0];
					if(f[i][j][k][1] && (j + p <= ha)) 
						f[i-1][j+p][(10 * k + p)%ha][1] += f[i][j][k][1]; 
				}
			}
		}
	}
	return f[1][ha][0][0] + f[1][ha][0][1];
}

int main(){
	scanf("%lld%lld",&a,&b);
	LL ans = 0;
	for(int i = 1;i < sum;i++)
		ans += pre(b,i) - pre(a-1,i);
	printf("%lld\n",ans);
	getchar();getchar();
	return 0;
}
