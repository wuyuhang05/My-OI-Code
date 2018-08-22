#include <iostream>
#include <cstdio>
#include <cstring>
#include <algorithm>

const int MAXN = 200 + 5;

int M,S,C;
int data[MAXN];
int dist[MAXN];

bool cmp(int a,int b){
    return a > b;
}

int main(){
    scanf("%d%d%d",&M,&S,&C);
    for(int i = 1;i <= C;i++)
        scanf("%d",&data[i]);
    if(M > C){
        printf("%d\n",C);
        return 0;
    }
    std::sort(data + 1,data + C + 1);
    for(int i = 1;i < C;i++)
        dist[i] = data[i+1] - data[i];
    std::sort(dist + 1,dist + C,cmp);
    int ans = data[C] - data[1] + 1;
    for(int i = 1;i <= M-1;i++){
        ans = ans - dist[i] + 1;
    }
    printf("%d\n",ans);
    getchar();getchar();
    return 0;
}

