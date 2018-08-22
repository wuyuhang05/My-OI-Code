#include <iostream>
#include <cstdio>
#include <cstring>

int f[300000 + 5];

inline int find(int x){
	if(x != f[x]) f[x] = find(f[x]);
	return f[x];
}

inline void Union(int x,int y){
	int fa = find(f[x]),fb = find(f[y]);
	f[fa] = fb;
}

inline void init(int n){
	for(int i = 1;i <= n * 3;i++)
		f[i] = i;
}

int main(){
	int N,K,d,x,y,ans = 0;
	scanf("%d%d",&N,&K);
	init(N);
	for(int i = 1;i <= K;i++){
		scanf("%d%d%d",&d,&x,&y);
		if(x > N || y > N){
			ans++;continue;
		}
		if(d == 1){
			if(find(x + N) == find(y) || find(x + 2*N) == find(y)){
				ans++;continue;
			}
			Union(x,y);Union(N + x,N + y);Union(2 * N + x,2 * N + y);
		}
		else if(d == 2){
			if(x == y){
				ans++;continue;
			}
			if(find(x) == find(y) || find(N*2 + x) == find(y)){
				ans++;continue;
			}
			Union(x,y + 2 * N);Union(x + N,y);Union(x + 2 * N,y + N);
		}
	}
	printf("%d",ans);
	return 0;
}