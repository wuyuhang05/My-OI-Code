#include <iostream>
#include <climits>
#include <cstdio>

const int MAXN = 200000 + 5;

int fa[MAXN],dist[MAXN],Min = INT_MAX;

int find(int x){
    if(x != fa[x]){
        int last = fa[x];
        fa[x] = find(fa[x]);
        dist[x] += dist[last];
    }
    return fa[x];
}

void check(int a,int b){
    int fx = find(a),fy = find(b);
    if(fx != fy){
        fa[fx] = fy;
        dist[a] = dist[b] + 1;
    }
    else Min = std::min(Min,dist[a] + dist[b] + 1);
}

int main(){
    int N;
    scanf("%d",&N);
    for(int i = 1;i <= N;i++) fa[i] = i;
    for(int x,i = 1;i <= N;i++){
        scanf("%d",&x);
        check(i,x);
    }
    printf("%d",Min);
    return 0;
}
