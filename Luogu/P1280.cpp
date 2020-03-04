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

#define R register
#define LL long long
#define U unsigned
#define FOR(i,a,b) for(R int i = a;i <= b;++i)
#define RFOR(i,a,b) for(R int i = a;i >= b;--i)
#define CLR(i,a) memset(i,a,sizeof(i))
#define BR printf("--------------------\n")
#define DEBUG(x) std::cerr << #x << '=' << x << std::endl

const int MAXN = 10000 + 5;

int N,K;

struct People{
    int s,t;

    bool operator < (const People &other) const {
        return s > other.s;
    }
}p[MAXN];
int sum[MAXN];
int num = 1;
int f[MAXN];

int main(){
    scanf("%d%d",&N,&K);
    FOR(i,1,K){
        scanf("%d%d",&p[i].s,&p[i].t);
        sum[p[i].s]++;
    }
    std::sort(p + 1,p + K + 1);
    RFOR(i,N,1){
        if(!sum[i])
            f[i] = f[i+1]+1;
        else{
            FOR(j,1,sum[i]){
                f[i] = std::max(f[i],f[i + p[num].t]);
                num++;
            }
        }
    }
    printf("%d\n",f[1]);
    return 0;
}
