#include <iostream>
#include <cstdio>
#include <cstring>
#include <cmath>

typedef long long LL;
LL euler(LL x){
    LL ans = x,tq = sqrt(x);
    for(LL i = 2;i <= tq;i++){
        if(!(x % i)){
            ans = ans - ans / i;
            while(!(x % i)) x /= i;
        }
    }
    if(x > 1) ans = ans - ans / x;
    return ans;
}

int main(){
    LL x,ans = 0;
    scanf("%lld",&x);
    int q = sqrt(x);
    for(int i = 1;i <= q;i++){
        if(!(x % i)) ans += i * euler(x / i) + x / i * euler(i);
    }
    if(q * q == x){
        ans -= q * euler(q);
    }
    printf("%lld",ans);
    return 0;
}
