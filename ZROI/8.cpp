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

const int MAXN = 300000 + 5;

struct Node{
    int a,p,pos;

    bool operator < (const Node &other) const {
        if(a == other.a) return pos < other.pos;
        return a > other.a;
    }
}p[MAXN*2];

int N,M;

inline bool cmp(int a,int b){
    if(p[a].a == p[b].a) return p[a].pos < p[b].pos;
    return p[a].a > p[b].a;
}

int main(){
    scanf("%d",&N);
    FOR(i,1,N*2) p[i].pos = i;
    FOR(i,1,N*2) scanf("%d",&p[i].a);
    FOR(i,1,N*2) scanf("%d",&p[i].p);
    scanf("%d",&M);
    std::sort(p + 1,p + N*2 + 1);
    FOR(i,1,M){
        FOR(j,1,N){
            if(p[j*2-1].p > p[j*2].p) p[j*2-1].a++;
            else p[j*2].a++;
        }
        FOR(j,1,N){
            if(!cmp(j*2-1,j*2)) std::swap(p[j*2-1],p[j*2]);
        }
        FOR(j,1,N-1)
            if(!cmp(j*2,j*2+1)) std::swap(p[j*2+1],p[j*2]);
    }
    FOR(i,1,N*2)
        if(p[i].pos == 1){
            printf("%d %d\n",i,p[i].a);
        }
    return 0;
}
