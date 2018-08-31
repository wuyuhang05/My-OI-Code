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

struct Node{
    int a,l,r;
}node[MAXN];

int N;
LL f[MAXN];

int main(){
    scanf("%d",&N);
    FOR(i,1,N){
        scanf("%d",&node[i].a);
        node[i].l = 1;node[i].r = N;
    }
    int head = 1,tail = 0;
    FOR(i,1,N){
        while(head <= tail && node[i].a >= node[f[tail]].a){
            node[f[tail]].r = i-1;
            tail--;
        }
        node[i].l = f[tail]+1;f[++tail] = i;
    }
    LL ans = 0;
    
    return 0;
}
