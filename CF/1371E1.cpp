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

const int MAXN = 1e5+5;
int a[MAXN];
int p,n;
std::vector<int> S;
int f[MAXN];

int main(){
    scanf("%d%d",&n,&p);
    FOR(i,1,n) scanf("%d",a+i);
    std::sort(a+1,a+n+1);std::reverse(a+1,a+n+1);
    int mn = 1e9;
    FOR(i,1,n) a[i] = n-a[i]-j+1,mn = std::min(mn,a[i]);
    mn = -mn;
    printf("%d\n",(int)S.size());
    for(auto x:S) printf("%d ",x);puts("");
    return 0;
}
