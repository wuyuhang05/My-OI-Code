/*
 * Time: 2019-11-10 19:55:28
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

const int MAXN = 1e5 + 5;
int p;

inline int calc(int l,int r){
    return r/p-(l-1)/p;
}

int n;
double f[MAXN][2],pro[MAXN];

int main(){
    scanf("%d%d",&n,&p);double t = 0;
    FOR(i,1,n){
        int l,r;scanf("%d%d",&l,&r);
        pro[i] = 1.0*calc(l,r)/(r-l+1);
    }
    double ans = 0.0;
    FOR(i,2,n){
        ans += 2000.0*(1-(1-pro[i-1])*(1-pro[i]));
    }
    ans += 2000.0*(1-(1-pro[n])*(1-pro[1]));
    printf("%.10f\n",ans);
    return 0;
}
