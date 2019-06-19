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

const int MAXN = 50+5;
const int MAXL = 20+5;
const int ha = 990804011;

int dp[MAXN][MAXN][MAXL][MAXL+4];
char s[MAXN][MAXN];
int a[MAXN][MAXN];
int n,m;

inline int dfs(int l,int r,int p,int c){
    int &f = dp[l][r][p][c];
    if(f != -1) return f;
    if(l > r) return f = 1;
    if(c > 26) return f = 0;
    if(p > m) return f = (l == r);
    f = dfs(l,r,p,c+1);
    FOR(i,l,r){
        if(!(a[i][p] == c || (a[i][p] == 27 && c))) break;
        f = (f + 1ll*dfs(l,i,p+1,0)*dfs(i+1,r,p,c+1)%ha)%ha;
    }
    return f;
}

int main(){
    scanf("%d",&n);
    CLR(dp,-1);
    FOR(i,1,n){
        int len;scanf("%s",s[i]+1);
        len = strlen(s[i]+1);m = std::max(m,len);
        FOR(j,1,len){
            if(s[i][j] == '?') a[i][j] = 27;
            else a[i][j] = s[i][j]-'a'+1;
        }
    }
    printf("%d\n",dfs(1,n,1,0));
    return 0;
}
