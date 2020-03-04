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

const int MAXN = 1e5 + 5;
int x[MAXN],y[MAXN];
char str[233];

int main(){
    int T;scanf("%d",&T);
    while(T--){
        int n,m;scanf("%d%d",&n,&m);CLR(x,0);CLR(y,0);
        FOR(i,1,m){
            int a,b;scanf("%d%s%d",&a,str+1,&b);
            str[1] == '<' ? ++x[b] : ++y[b];
        }
        if(std::count(y+1,y+n+1,n)){
            puts("Alice");continue;
        }
        if(std::count(x+1,x+n+1,0)){
            puts("Draw");continue;
        }
        puts("Bob");
    }
    return 0;
}