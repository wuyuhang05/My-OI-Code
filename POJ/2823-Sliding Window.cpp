#include <algorithm>
#include <iostream>
#include <cstring>
#include <climits>
#include <cstdlib>
#include <cstdio>
#include <cmath>
#include <queue>
#include <stack>
#include <deque>
#include <map>
#include <set>
//debug begin
using std::cout;
using std::endl;
//debug end.

const int MAXN = 1000000 + 5;

int N,K;
int num[MAXN],maxq[MAXN],minq[MAXN],maxans[MAXN],minans[MAXN];

int main(){
	while(scanf("%d%d",&N,&K) != EOF){
		int maxhead=0,minhead=0,maxtail=0,mintail=0;
		for(int i = 0;i < N;i++){
			if(maxhead < maxtail && maxq[maxhead] <= i - K) maxhead++; 
			if(minhead < mintail && minq[minhead] <= i - K) minhead++;
			scanf("%d",&num[i]);
            while (maxhead<maxtail && num[maxq[maxtail-1]]<=num[i]) maxtail--;maxtail++;
            maxq[maxtail-1]=i;
            while (minhead<mintail && num[minq[mintail-1]]>=num[i]) mintail--;mintail++;
            minq[mintail-1]=i;
            maxans[i]=num[maxq[maxhead]];
            minans[i]=num[minq[minhead]];  
		}
		//for(int i = K-1;i < N;i++) printf("%d",minans[i],(i == N - 1) ? '\n' : ' ');
		//for(int i = K-1;i < N;i++) printf("%d%c",maxans[i],(i == N - 1) ? '\n' : ' ');
		for (int i=K-1;i<N;i++) cout<<minans[i]<<' ';cout<<endl;
        for (int i=K-1;i<N;i++) cout<<maxans[i]<<' ';cout<<endl;
	}
	//getchar();getchar();
	return 0;
}