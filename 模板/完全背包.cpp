#include <iostream>
#include <cstring>
#include <cstdio>

const int MAXM = 10000 + 5;

int f[MAXM * 10];
int t[MAXM],v[MAXM];

int main(){
    int T,M;
    scanf("%d%d",&T,&M);
    for(int i = 1;i <= M;i++)
        scanf("%d%d",&t[i],&v[i]);
    for(int i = 1;i <= M;i++){
        for(int j = t[i];j <= T;j++){
            f[j] = std::max(f[j],f[j-t[i]] + v[i]);
        }
    }
    printf("%d\n",f[T]);
    //getchar();getchar();
    return 0;
}
