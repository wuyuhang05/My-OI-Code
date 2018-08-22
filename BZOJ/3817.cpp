#include <iostream>
#include <cstdio>
#include <cstring>
#include <cmath>
#include <map>
#include <algorithm>
#define LL long long
const int MAXN = 5e6 + 10;
const int POIN = 5e6;
LL T,cnt,mu[MAXN],phi[MAXN];
int prime[MAXN];
bool p[MAXN];
void pre(){
    mu[1] = phi[1] = 1;
    for(int i = 2;i <= POIN;i++){
        if(!p[i]){
            prime[++cnt] = i;
            mu[i] = -1;
            phi[i] = i-1;
        }
        for(int j = 1;j <= cnt && i * prime[j] <= POIN;j++){
            p[i*prime[j]] = 1;
            if(!(i % prime[j])){
                phi[i*prime[j]] = phi[i] * prime[j];
                // mu[i*prime[j]] = 0;
                break;
            }
            mu[i*prime[j]] = -mu[i];
            phi[i*prime[j]] = phi[i] * phi[prime[j]];
        }
    }
    for(int i = 1;i <= POIN;i++){
        mu[i] += mu[i-1];
        phi[i] += phi[i-1];
    }
}
std::map<int,LL> mmu,mphi;
LL query1(LL x)
{
    if(x<=5e6)return phi[x];
    if(mphi.find(x) != mphi.end())return mphi[x];
    LL tmp=x*(x+1)/2;LL i,j;
    for(i=2;i<=x;i=j+1)
    {
        j=x/(x/i);
        tmp-=(j-i+1)*query1(x/i);
    }
    return mphi[x]=tmp;
}
LL query2(LL n){
    if(n <= POIN)
        return mu[n];
    if(mmu.find(n) != mmu.end()) return mmu[n];
    LL t = 1;
    LL i,last;
    for(i = 2;i <= n;i = last + 1){
        last = n/(n/i);
        t -= (last-i+1)*query2(n/i);
    }
    return mmu[n] = t;
}
int main(){
    LL n;int T;
    scanf("%d",&T);
    pre();
    while(T--){
        scanf("%lld",&n);
        printf("%lld %lld\n",query1(n),query2(n));
    }
    return 0;
}

