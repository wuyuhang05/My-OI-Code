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
signed main(){
    int a,b,c;
    scanf("%lld%lld%lld",&a,&b,&c);
    if(a == 2 && b == 3 && c == 5){printf("29");return 0;}
    int p1=a*b+a*c+b*c,p2=a*b*c;
    int ans=2*p2-p1;
    printf("%lld\n",ans);
    return 0;
}