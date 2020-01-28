/*
 * Time: 2019-11-29 17:30:13
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
#define int LL
const int MAXN = 2e5 + 5;
char str[23];
int st[MAXN],tp;
int n,D;
int la = 0,sz = 0;
int a[MAXN];

inline int calc(int t){
    int p = std::lower_bound(st+1,st+tp+1,t)-st;
    return st[p];
}

signed main(){
    scanf("%lld%lld",&n,&D);
    FOR(i,1,n){
        scanf("%s",str);
        int x;scanf("%lld",&x);
        if(str[0] == 'A') (x += la) %= D;
        if(str[0] == 'Q'){
            printf("%lld\n",la = a[calc(sz-x+1)]);
        }
        else{
            a[++sz] = x;
            while(tp && a[st[tp]] <= x) tp--;
            st[++tp] = sz;
        }
    }
    return 0;
}
