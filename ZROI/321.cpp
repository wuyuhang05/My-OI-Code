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

#define LL long long
#define U unsigned
#define FOR(i,a,b) for(int i = a;i <= b;++i)
#define RFOR(i,a,b) for(int i = a;i >= b;--i)
#define CLR(i,a) memset(i,a,sizeof(i))
#define BR printf("--------------------\n")
#define DEBUG(x) std::cerr << #x << '=' << x << std::endl

int p[20000005];
int seed, N ,k, S;

int getrand(){
	seed = ((seed * 12321) ^ 9999) % 32768;
	return seed;
}

void generateData(){
	scanf("%d%d%d",&k,&seed,&S);
	int t = 0;
	N = k * 2 + 1;
    CLR(p,0);
	for(int i = 1; i <= N; i++){
		p[i] = (getrand() / 128) % 2;
		t += p[i];
	}
	int i = 1;
	while(t > k){
		while (p[i] == 0)
			i++;
		p[i] = 0;
		t--;
	}
	while(t < k){
		while (p[i] == 1)
			i++;
		p[i] = 1;
		t++;
	}
}
const int MAXN = 20000000 + 5;
int sum[MAXN],w[MAXN],pool[MAXN*2],*cnt = pool + 10000000 + 5;

int main(){
    generateData();
    FOR(i,1,N){
        if(p[i]){
            w[i] = w[i-1]-cnt[sum[i-1]+2];
            sum[i] = sum[i-1]+1;
            ++cnt[sum[i]];
        }   
        else{
            sum[i] = sum[i-1]-1;
            w[i] = w[i-1] + cnt[sum[i]+2];
        }
    }
    // FOR(i,1,N)printf("%d ",w[i]);
    CLR(pool,0);
    int tot = 0;
    RFOR(i,N,1){
        if(p[i])
            tot += ++cnt[sum[i]];
        else{
            if(w[i] + tot == S){
                printf("%d\n",i);
                break;
            }
            tot -= cnt[sum[i]+1];
        }
    }
    return 0;
}
