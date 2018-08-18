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

const int MAXN = 500000 + 5;
const U LL ha = 1ll << 32;

U LL g[MAXN],s[MAXN];

void pre(){
    memset(g,0,sizeof(g));
    g[0] = s[1] = 0;
    for(int i = 1;i < MAXN;i++){
        for(int j = 1;j * i < MAXN;j++)
            g[j*i] = (g[j*i] + (1ll+j)*j/2)%ha;
        g[i] = g[i] * i % ha;
    }
    for(U LL i = 1;i < MAXN;i++)
        s[i] = (s[i-1] + g[i]) % ha;
}

int main(){
    pre();
    int T;scanf("%d",&T);
    for(int x,i = 1;i <= T;i++){
        scanf("%d",&x);
        printf("Case #%d: %lld\n",i,s[x]);
    }
    return 0;
}

