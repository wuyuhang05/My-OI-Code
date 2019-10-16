/*
 * Author: RainAir
 * Time: 2019-10-12 06:44:00
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
#define LL long long
#define pb push_back
#define MP std::make_pair
#define all(x) x.begin(),x.end()
#define CLR(i,a) memset(i,a,sizeof(i))
#define FOR(i,a,b) for(int i = a;i <= b;++i)
#define ROF(i,a,b) for(int i = a;i >= b;--i)
#define DEBUG(x) std::cerr << #x << '=' << x << std::endl

const int MAXN = 110000+5;
int a[MAXN],n,b;

inline void dfs(int step,int t){
    if(step == n+1){
        ROF(i,n,1){
            if(a[i] >= 10) putchar(a[i]-10+'A');
            else printf("%d",a[i]);
        }
        puts("");
        return;
    }
    if(t == 1){
        ROF(i,b-1,0) a[step] = i,dfs(step+1,!(i&1));
    }
    else{
        FOR(i,0,b-1) a[step] = i,dfs(step+1,i&1);
    }
}

int main(){
    scanf("%d%d",&n,&b);
    dfs(1,0);
    return 0;
}
