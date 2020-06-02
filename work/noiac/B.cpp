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

const int MAXN = 15+1;
const int ha = 998244353;

int n,m;
int a[MAXN],b[MAXN],p[MAXN];

namespace BF{
    inline void Solve(){
        int ans = 0;
        FOR(i,1,n) p[i] = i;
        do{
            bool flag = true;int sm = 0;
            FOR(i,1,n){
                if(b[i] != -1 && p[i] != b[i]) {flag = false;break;} 
                sm += std::abs(p[i]-a[i]);
            }
            if(flag && sm <= m) ans++;
        }while(std::next_permutation(p+1,p+n+1));
        printf("%d\n",ans);
    }
}

int main(){
    scanf("%d%d",&n,&m);
    FOR(i,1,n) scanf("%d",a+i);
    FOR(i,1,n) scanf("%d",b+i);
    if(n <= 10) BF::Solve();
    return 0;
}
