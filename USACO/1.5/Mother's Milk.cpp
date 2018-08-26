/*
ID: wuyuhan5
PROB: milk3
LANG: C++
*/
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
#define FOR(i,a,b) for(int i = a;i <= b;++i)
#define RFOR(i,a,b) for(int i = a;i >= b;--i)
#define CLR(i,a) memset(i,a,sizeof(i))
#define BR printf("--------------------\n")
#define DEBUG(x) std::cerr << #x << '=' << x << std::endl

const int MAXN = 20 + 5;
bool f[MAXN][MAXN][MAXN];
bool milk[MAXN];
int p[4];

void dfs(int a[4]){
    if(f[a[1]][a[2]][a[3]]) return;
    f[a[1]][a[2]][a[3]] = true;
    if(!a[1]) milk[a[3]] = true;
    FOR(i,1,3){
        FOR(j,1,3){
            if(i == j) continue;
            if(a[j] < p[j] && a[i] > 0){
                int ret = std::min(p[j]-a[j],a[i]);
                int b[4];
                memcpy(b,a,sizeof(int)*4);
                b[i] -= ret;b[j] += ret;
                dfs(b);
            }
        }
    }
}

int main(){
    freopen("milk3.in","r",stdin);
    freopen("milk3.out","w",stdout);
    int &A = p[1],&B = p[2],&C = p[3];
    scanf("%d%d%d",&A,&B,&C);
    int a[4] = {0,0,0,C};
    dfs(a);
    FOR(i,0,C-1){
        if(milk[i]) printf("%d ",i);
    }
    printf("%d\n",C);
    return 0;
}
