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

const int MAXN = 100 + 5;

struct Trash{
    int t,f,h;
    bool operator < (const Trash &other) const {
        return t < other.t;
    }
}t[MAXN];

int D,G;
int f[MAXN];

int main(){
    scanf("%d%d",&D,&G);
    FOR(i,1,G)
        scanf("%d%d%d",&t[i].t,&t[i].f,&t[i].h);
    std::sort(t + 1,t + G + 1);
    f[0] = 10;
    FOR(i,1,G){
        RFOR(j,D,0){
            if(f[j] >= t[i].t){
                if(j + t[i].h >= D){
                    printf("%d\n",t[i].t);
                    return 0;
                }
                f[j + t[i].h] = std::max(f[j + t[i].h],f[j]);
                f[j] += t[i].f;
            }
        }
    }
    printf("%d\n",f[0]);
    return 0;
}
