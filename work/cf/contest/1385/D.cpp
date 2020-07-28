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

const int MAXN = 2e5 + 5;

int n;char str[MAXN];
int sm[MAXN][26];
int ans = 1e9;

inline void dfs(int l,int r,int c,int now=0){
    if(l == r){
        now += (r-l+1)-(sm[r][c]-sm[l-1][c]);
        ans = std::min(ans,now);
        return;
    }
    int mid = (l + r) >> 1;
    int t = now;
    now += r-mid-(sm[r][c]-sm[mid][c]);
    dfs(l,mid,c+1,now);
    now = t;
    now += mid-l+1-(sm[mid][c]-sm[l-1][c]);
    dfs(mid+1,r,c+1,now);
}

inline void Solve(){
    scanf("%d",&n);
    scanf("%s",str+1);
    FOR(i,1,n){
        FOR(j,0,25) sm[i][j] = sm[i-1][j];
        sm[i][str[i]-'a']++;
    }
    ans = 1e9;
    dfs(1,n,0);
    printf("%d\n",ans);
}

int main(){
    int T;scanf("%d",&T);
    while(T--) Solve();
    return 0;
}
