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
#define U unsigned
#define P std::pair
#define LL long long
#define pb push_back
#define MP std::make_pair
#define all(x) x.begin(),x.end()
#define CLR(i,a) memset(i,a,sizeof(i))
#define FOR(i,a,b) for(int i = a;i <= b;++i)
#define ROF(i,a,b) for(int i = a;i >= b;--i)
#define DEBUG(x) std::cerr << #x << '=' << x << std::endl

int main(){
    freopen("a.in","w",stdout);
    int n = 100000,m = 10000,q = 100000;
    printf("%d %d\n",n,m);
    FOR(i,1,m){
        printf("%d %d %d\n",1+rand()%n,1+rand()%n,1+rand()%m);
    }
    printf("%d\n",q);
    FOR(i,1,q){
        printf("%d %d\n",1+rand()%n,1+rand()%n);
    }
    return 0;
}

