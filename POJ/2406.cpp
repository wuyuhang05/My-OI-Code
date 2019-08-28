/*
 * Author: RainAir
 * Time: 2019-08-26 10:56:38
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
#define U unsigned
#define P std::pair
#define Re register
#define LL long long
#define pb push_back
#define MP std::make_pair
#define all(x) x.begin(),x.end()
#define CLR(i,a) memset(i,a,sizeof(i))
#define FOR(i,a,b) for(Re int i = a;i <= b;++i)
#define ROF(i,a,b) for(Re int i = a;i >= b;--i)
#define DEBUG(x) std::cerr << #x << '=' << x << std::endl

const int MAXN = 1e6 + 5;
int nxt[MAXN],n;
char str[MAXN];

inline void Solve(){
    n = strlen(str+1);int j = 0;
    FOR(i,2,n){
        while(str[j+1] != str[i] && j) j = nxt[j];
        if(str[j+1] == str[i]) j++;
        nxt[i] = j;
    }
//    DEBUG(nxt[n]);
    printf("%d\n",(!(n%(n-nxt[n]))) ? n/(n-nxt[n]) : 1);
    FOR(i,0,n) nxt[i] = 0;
}

int main(){
    while(~scanf("%s",str+1) && str[1] != '.') Solve();
    return 0;
}
