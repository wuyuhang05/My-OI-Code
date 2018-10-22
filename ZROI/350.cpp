#include <algorithm>
#include <iostream>
#include <cstring>
#include <climits>
#include <cstdio>
#include <vector>
#include <cstdlib>
#include <ctime>
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
#define SFOR(i,a,b,c) for(Re int i = a;i <= b;i+=c)
#define SROF(i,a,b,c) for(Re int i = a;i >= b;i-=c)
#define CLR(i,a) memset(i,a,sizeof(i))
#define BR printf("--------------------\n")
#define DEBUG(x) std::cerr << #x << '=' << x << std::endl

std::set<int> S;

void dfs(int sum,int t,int fac){
    S.insert(t+sum-1);
    int q = std::sqrt(sum);
    FOR(i,fac,q){
        if(!(sum % i)) dfs(sum/i,t+i-1,i);
    }
}

int main(){
    int N;scanf("%d",&N);
    dfs(N,0,2);
    printf("%d\n",(int)S.size());
    for(std::set<int>::iterator it = S.begin();it != S.end();it++)
        printf("%d ",*it);
    return 0;
}