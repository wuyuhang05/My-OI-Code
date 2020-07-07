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

const int MAXN = 4e5 + 5;
int n,m;
int smx[MAXN],smy[MAXN];
int sm[2][MAXN];

int main(){
 //   freopen("A.in","r",stdin);
    scanf("%d%d",&n,&m);
    FOR(i,1,m){
        int x,y;scanf("%d%d",&x,&y);
        smx[x+y] = 1;smy[x-y+n] = 1;
        sm[(x+y)%2][x+y] = 1;
    }
    LL ans = 1ll*n*n;
    int t = 0;
    FOR(i,2,2*n){
        if(i <= n+1) t++;
        else t--;
        if(smx[i]){
            ans -= t;
        }
    }
    FOR(i,1,MAXN-1) sm[0][i] += sm[0][i-1],sm[1][i] += sm[1][i-1];
    t = 0;
    FOR(i,1-n,n-1){
        if(i <= 0) t++;
        else t--;
        if(!smy[i+n]) continue;
        ans -= t;
        if(i <= 0){
            int l = 2-i,r = i+2*n;
            if(l > r) std::swap(l,r);
            ans += (sm[(2-i)%2][r]-sm[(2-i)%2][std::max(0,l-1)]);
        }
        else{
            int l = i+2,r = 2*n-i;
            if(l > r) std::swap(l,r);
            ans += (sm[(i+2)%2][r]-sm[(i+2)%2][std::max(0,l-1)]);
        }
    }
    printf("%lld\n",ans);
    return 0;
}
