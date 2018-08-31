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

const int MAXN = 100000 + 5;

int N,M;

struct Days{
    int fa,c;

    bool operator < (const Days &other) const {
        if(fa == other.fa) return c < other.c;
        return fa < other.fa;
    }
}d[MAXN];

int find(int x){
    return d[x].fa == x ? x : d[x].fa = find(d[x].fa);
}

int solve(int l,int r){
    int cnt = l,ret = 0;
    FOR(i,l+1,r){
        if(d[i].c != d[i-1].c){
            ret = std::max(ret,i-cnt);
            cnt = i;
        }
    }
    ret = std::max(ret,r + 1-cnt);
    return r-l+1-ret;
}

int main(){
    scanf("%d",&N);
    FOR(i,1,N){
        scanf("%d",&d[i].c);
        d[i].fa = i;
    }
    scanf("%d",&M);
    FOR(i,1,M){
        int x,y;
        scanf("%d%d",&x,&y);
        int fx = find(x),fy = find(y);
        d[fx].fa = fy;
    }
    FOR(i,1,N) d[i].fa = find(i);
    std::sort(d + 1,d + N + 1);
    int last = 1;
    LL ans = 0;
    FOR(i,2,N){
        if(d[i].fa != d[i-1].fa){
            ans += solve(last,i-1);
            last = i;
        }
    }
    ans += solve(last,N);
    printf("%lld\n",ans);
    return 0;
}
