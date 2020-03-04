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

const int MAXN = 1000+5;
const int ha = 1e9 + 7;
int n,m;
std::vector<int> a;
inline LL dp(std::vector<int> S){
    if(S.size() <= 1) return 1;
    // DEBUG(S.size());
    int p = std::min_element(all(S))-S.begin(),q = std::max_element(all(S))-S.begin();
    if(S[p]+S[q] > m){
        std::vector<int> A,B;
        FOR(i,0,q-1) A.pb(S[i]);
        FOR(i,q+1,(int)S.size()-1) B.pb(S[i]);
        return 1ll*dp(A)*dp(B)%ha;
    }
    S.erase(S.begin()+p);
    return 1ll*dp(S)*(int)(S.size()+1)%ha;
}

int main(){
    scanf("%d%d",&n,&m);
    FOR(i,1,n){
        int x;scanf("%d",&x);a.pb(x);
    }
    printf("%lld\n",dp(a));
    return 0;
}