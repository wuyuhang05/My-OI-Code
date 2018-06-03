#include <algorithm>
#include <iostream>
#include <cstring>
#include <cstdio>

int N,K;

int f[200 + 5][6 + 5];

int main(){
    scanf("%d%d",&N,&K);
    f[0][0] = 1;
    for(int i = 1;i <= N;i++)
        f[i][1] = 1;
    for(int i = 1;i <= N;i++)
        for(int j = 1;j <= K;j++)
            if(i >= j)
                 f[i][j] = f[i-j][j] + f[i-1][j-1];
    printf("%d\n",f[N][K]);
    return 0;
}
