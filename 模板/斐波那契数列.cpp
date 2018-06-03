#include <iostream>
#include <cstdio>
#include <cstring>

const int MAXN = 5 + 5;
#define LL long long
const int ha = 1000000007;

struct Matrix{
    LL a[MAXN][MAXN];
    LL N,M;

    void clear(LL n=0,LL m=0){
        N = n;M = m;
        memset(a,0,sizeof(a));
    }

    Matrix operator * (const Matrix &b) const{
        Matrix ret;
        ret.clear();
        for(int i = 0;i < 2;i++){
            for(int j = 0;j < 2;j++){
                for(int k = 0;k < 2;k++){
                    ret.a[i][j] = (ret.a[i][j] + ((a[i][k] * b.a[k][j]) % ha)) % ha;
                }
            }
        }
        return ret;
    }
}fib,ans;

int main(){
    LL N;
    scanf("%lld",&N);
    ans.a[0][0] = ans.a[1][1] = 1;
    fib.a[0][1] = fib.a[1][0] = fib.a[1][1] = 1;
    N--;
    while(N){
        if(N & 1)
            ans = ans * fib;
        fib = fib * fib;
        N >>= 1;
    }
    printf("%lld",ans.a[1][1]);
    getchar();getchar();
    return 0;
}
