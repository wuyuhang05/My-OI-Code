/*
 * Author: RainAir
 * Time: 2020-05-29 15:31:29
 */
#include <algorithm>
#include <iostream>
#include <cstring>
#include <climits>
#include <cstdlib>
#include <cstdio>
#include <bitset>
#include <vector>
#include <cmath>
#include <ctime>
#include <queue>
#include <stack>
#include <map>
#include <set>

#define fi first
#define se second
#define db double
#define U unsigned
#define P std::pair<int,int>
#define LL long long
#define pb push_back
#define MP std::make_pair
#define all(x) x.begin(),x.end()
#define CLR(i,a) memset(i,a,sizeof(i))
#define FOR(i,a,b) for(int i = a;i <= b;++i)
#define ROF(i,a,b) for(int i = a;i >= b;--i)
#define DEBUG(x) std::cerr << #x << '=' << x << std::endl

int main(){
    int n,m,sx,sy;scanf("%d%d%d%d",&n,&m,&sx,&sy);
    printf("%d %d\n",sx,sy);
    ROF(i,m,1){
        if(i == sy) continue;
        printf("%d %d\n",sx,i);
    }
    printf("%d %d\n",1,1);
    int t = 1;
    FOR(i,1,n){
        if(i == sx) continue;
        t ^= 1;
        if(!t) FOR(j,2,m) printf("%d %d\n",i,j);
        else ROF(j,m-1,1) printf("%d %d\n",i,j);
        if(i+1 == sx) printf("%d %d\n",i+2,t?1:m);
        else if(i+1 != n+1) printf("%d %d\n",i+1,t?1:m);
    }
    return 0;
}
