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

#define Re register
#define LL long long
#define U unsigned
#define FOR(i,a,b) for(Re int i = a;i <= b;++i)
#define ROF(i,a,b) for(Re int i = a;i >= b;--i)
#define CLR(i,a) memset(i,a,sizeof(i))
#define BR printf("--------------------\n")
#define DEBUG(x) std::cerr << #x << '=' << x << std::endl

const int MAXN = 100000 + 5;

struct Member{
#define MAXL 20
    char str[MAXL];
    int opt;
#undef MAXL
}p[MAXN];

int N,M,pos=0;

int main(){
    scanf("%d%d",&N,&M);
    FOR(i,0,N-1) scanf("%d%s",&p[i].opt,p[i].str+1);
    FOR(i,1,M){
        int opt,x;scanf("%d%d",&opt,&x);
        opt ^= p[pos].opt; // 0:- 1:+
        pos = opt ? (pos+x)%N : (pos-x%N+N)%N;
        // DEBUG(pos);
    }
    printf("%s\n",p[pos].str+1);
    return 0;
}
