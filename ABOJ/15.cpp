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

const int MAXN = 1000 + 5;

struct Node{
    std::string str;
    int pre;
}node[MAXN];

int N,M;

int main(){
    // std::ios::sync_with_stdio(false);
    scanf("%d",&N);
    FOR(i,1,N) std::cin >> node[i].str;
    scanf("%d",&M);
    FOR(i,1,M){
        int x,y;scanf("%d%d",&x,&y);
        node[x].str = node[y].str;
        node[x].pre = node[y].pre + 1;
    }
    while(node[1].pre--) printf("I_love_");
    std::cout << node[1].str;
    return 0;
}
