/*
 * Author: RainAir
 * Time: 2019-09-10 21:23:45
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

const int MAXN = 3e5 + 5;
int n,m;
char a[MAXN],b[MAXN];
int p[MAXN];

int main(){
    scanf("%d%d",&n,&m);
    scanf("%s%s",a+1,b+1);
    for(int i = 1,j = 1;i <= m;++i){
        while(j <= n && a[j] != b[i]) ++j;
        if(j > n){
            puts("-1");
            return 0;
        }
        p[i] = j++;
    }
//    FOR(i,1,m) printf("%d ",p[i]);
    a[0] = a[1];
    for(int i = n,j = m;i >= 1;--i){
        if(a[i] == a[i-1]) continue;
        while(j >= 1 && p[j] > i) j--;
        if(j <= 0){
            puts("-1");
            return 0;
        }
        if(p[j] >= i-1) continue;
        p[j] = a[i] == b[j] ? i : i-1;
    }
    FOR(i,1,m) printf("%d ",p[i]);
    return 0;
}
