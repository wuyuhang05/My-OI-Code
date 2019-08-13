/*
 * Author: RainAir
 * Time: 2019-08-09 08:34:38
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

const int MAXN = 2e6 + 5;
const int BASE = 31;
U LL a[MAXN],hash[MAXN];
char str[MAXN];
int n;
char stk[MAXN];int top;

int main(){
    scanf("%s",str+1);n = strlen(str+1);
    FOR(i,1,n){
        if(top && stk[top] == str[i]) top--;
        else stk[++top] = str[i],hash[top] = hash[top-1]*BASE+str[i];
        a[i] = hash[top];
    }
    std::sort(a+1,a+n+1);
    LL ans = 0,cnt = 0;
    FOR(i,0,n){
        if(!i || a[i] != a[i-1]) cnt = 1;
        else ans += cnt++;
    }
    printf("%lld\n",ans);
    return 0;
}

