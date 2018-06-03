#include <iostream>
#include <cstring>
#include <cstdio>

const int ha = 1000000;
const int MAXN = 100000 + 5;
const int MAXA = 1000 + 5;

int T,A,S,B,ans;
int f[2][MAXN],ant[MAXA];

int main(){
    scanf("%d%d%d%d",&T,&A,&S,&B);
    for(int x,i = 1;i <= A;i++){
        scanf("%d",&x);
        ant[x]++;
    }
    f[0][0] = f[1][0] = 1;
    for(int i = 1;i <= T;i++){
        for(int j = 1;j <= B;j++){
            if(j - ant[i] - 1 >= 0)
                f[i%2][j] = (f[(i-1)%2][j] + f[i%2][j-1] - f[(i - 1)%2][j-ant[i]-1]+ha)%ha;
            else
                f[i%2][j] = (f[(i-1)%2][j] + f[i%2][j-1])%ha;
        }
    }
    for(int i = S;i <= B;i++)
        ans = (ans + f[T%2][i]) % ha;
    printf("%d",ans);
    //getchar();getchar();
    return 0;
}
