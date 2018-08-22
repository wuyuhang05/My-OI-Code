#include <iostream>
#include <cstdio>
#include <cstring>

#define LL long long
const int MAXN = 100000 + 5;

LL f[MAXN],ans;

int main(){
    int a,b;
    scanf("%d%d",&a,&b);
    int k = std::min(a,b);
    for(int i = k;i;i--){
        f[i] = (LL)(a/i) * (b/i);
        for(int j = 2;j * i <= k;j++){
            f[i] -= f[i * j];
        }
        ans += f[i] * (i + i - 1);
    }
    printf("%lld",ans);
    return 0;
}
