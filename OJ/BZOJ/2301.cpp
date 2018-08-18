#include <algorithm>
#include <iostream>
#include <cstring>
#include <climits>
#include <cstdio>
#include <vector>
#include <cmath>
#include <queue>
#include <stack>
#include <map>
#include <set>

#define LL long long
#define U unsigned
#define DEBUG(x) std::cerr << #x << '=' << x << std::endl
#define R register

const int MAXN = 50000 + 5;

LL a,b,c,d,k;
int mu[MAXN] = {0}; // 莫比乌斯函数
bool p[MAXN] = {0};
int prime[MAXN] = {0};
int cnt = 0;

void pre(){
    mu[1] = 1;
    for(int i = 2;i < MAXN;i++){
        if(!p[i]){
            prime[++cnt] = i;
            mu[i] = -1;
        }
        for(int j = 1;j <= cnt && i * prime[j] < MAXN;j++){
            p[i*prime[j]] = 1;
            if(!(i % prime[j])){
                mu[i*prime[j]] = 0;
                break;
            }
            mu[i*prime[j]] = -mu[i];
        }
        mu[i] += mu[i-1];
    }
    return;
}

LL query(LL N,LL M){
    if(N > M) std::swap(N,M);
    LL ret = 0;
    LL last = 0;
    for(LL d = 1ll;d <= N;d = last + 1){
        LL T1 = N/d,T2 = M/d;
        last = std::min(N/T1,M/T2);
        ret += (mu[last] - mu[d-1])*T1*T2;
    }
    return ret;
}

int main(){
    int T;
    scanf("%d",&T);
    pre();
    // for(int i = 1;i < MAXN;i++) printf("%d ",mu[i]);
    while(T--){
        scanf("%lld%lld%lld%lld%lld",&a,&b,&c,&d,&k);
        LL ans = query(b/k,d/k) - query((a-1)/k,d/k) - query(b/k,(c-1)/k) + query((a-1)/k,(c-1)/k);
        printf("%lld\n",ans);
    }
    return 0;
}

