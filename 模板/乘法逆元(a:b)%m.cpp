#include <iostream>
#include <cstdio>
#include <cstring>

typedef long long LL;
const int ha = 9973;

LL n,a,b,x,y,d;

LL ex_gcd(LL a,LL b,LL &x,LL &y){
    if(b == 0){
        x = 1;y = 0;
        return a;
    }
    LL d = ex_gcd(b,a % b,y,x);
    y -= a/b*x;
    return d;
}

int main(){
    int T;
    scanf("%d",&T);
    while(T--){
        scanf("%lld%lld",&n,&b);
        int d = ex_gcd(b,ha,x,y);
        x *= n;
        x = (x % ha + ha) % ha;
        printf("%lld\n",x);
    }
    return 0;
}
