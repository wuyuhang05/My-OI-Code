#include <unordered_map>
#include <algorithm>
#include <iostream>
#include <cstring>
#include <climits>
#include <cstdlib>
#include <cstdio>
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

const int MAXN = 20 + 5;
const int BASE = 12;

int n,m,a[MAXN][MAXN],b[MAXN][MAXN],f[MAXN];

std::unordered_map<LL,int> S;

LL hash(){
    LL res = 0;
    FOR(i,1,n) res = res*BASE+f[i];
    return res;
}

inline void gen(LL x){
    ROF(i,n,1) f[i] = x%BASE,x /= BASE;
}

inline int dfs(LL x){
    if(S.count(x)) return S[x];
    gen(x);
    int flag = 0;
    FOR(i,1,n) flag += f[i];flag %= 2;
    int res = flag ? INT_MAX : INT_MIN;
    FOR(i,1,n){
        if(f[i] < f[i-1]){
            f[i]++;LL hs = hash();
            if(flag) res = std::min(res,dfs(hs)-b[i][f[i]]);
            else res = std::max(res,dfs(hs)+a[i][f[i]]);
            f[i]--;
        }
    }
    return S[x] = res;
}

int main(){
    scanf("%d%d",&n,&m);
    FOR(i,1,n) FOR(j,1,m) scanf("%d",&a[i][j]);
    FOR(i,1,n) FOR(j,1,m) scanf("%d",&b[i][j]);
    FOR(i,0,n) f[i] = m;
    S[hash()] = 0;
    printf("%d\n",dfs(0));
    return 0;
}
