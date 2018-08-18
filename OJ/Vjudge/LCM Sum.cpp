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

const int MAXN = 1000000 + 5;
const U LL ha = 1ll << 32;

int phi[MAXN],p[MAXN/10],cnt;
LL ans[MAXN];
bool b[MAXN];

void pre(){
    phi[1] = 1;
    for(int i = 2;i < MAXN;i++){
        if(!b[i]){
            p[++cnt] = i;
            phi[i] = i-1;
        }
        for(int j = 1;j <= cnt && i * p[j] <= MAXN;j++){
            b[i*p[j]] = true;
            if(!(i % p[j])){
                phi[i*p[j]] = phi[i] * p[j];
                break;
            }
            phi[i*p[j]] = phi[i] * (p[j]-1);
        }
    }
    for(int i = 1;i < MAXN;i++)
        for(int j = 1;j*i < MAXN;j++)
            ans[i*j] += (LL)j*phi[j]/2;
    for(int i = 1;i < MAXN;i++) ans[i] = (LL)i*ans[i] + i;
}

int main(){
    pre();
    int T;scanf("%d",&T);
    for(int x,i = 1;i <= T;i++){
        scanf("%d",&x);
        printf("%lld\n",ans[x]);
    }
    return 0;
}

