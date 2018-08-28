/*
ID: wuyuhan5
PROB: sprime
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

#define R register
#define LL long long
#define U unsigned
#define FOR(i,a,b) for(R int i = a;i <= b;++i)
#define RFOR(i,a,b) for(R int i = a;i >= b;--i)
#define CLR(i,a) memset(i,a,sizeof(i))
#define BR printf("--------------------\n")
#define DEBUG(x) std::cerr << #x << '=' << x << std::endl

int N;
int num[10];

bool is_prime(int l){
    int x = 0;
    FOR(i,1,l)
        x += num[i]*pow(10,l-i);
    if(x == 1) return false;
    int q = std::sqrt(x);
    FOR(i,2,q)
        if(!(x % i)) return false;
    return true;
}

inline void print_num(){
    FOR(i,1,N)
        printf("%d",num[i]);
    puts("");
}

inline void dfs(int step){
    if(step != 1){
        if(!is_prime(step-1)) return; 
    }
    if(step == N + 1){
        print_num();
        return;
    }
    FOR(i,0,9){
        if(step == 1 && !i) continue;
        num[step] = i;
        dfs(step+1);
    }
}

int main(){
    freopen("sprime.in","r",stdin);
    freopen("sprime.out","w",stdout);
    scanf("%d",&N);
    dfs(1);
    return 0;
}
