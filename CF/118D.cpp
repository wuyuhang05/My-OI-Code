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
#define Re register
#define LL long long
#define pb push_back
#define MP std::make_pair
#define all(x) x.begin(),x.end()
#define CLR(i,a) memset(i,a,sizeof(i))
#define FOR(i,a,b) for(Re int i = a;i <= b;++i)
#define ROF(i,a,b) for(Re int i = a;i >= b;--i)
#define DEBUG(x) std::cerr << #x << '=' << x << std::endl

const int MAXN = 100+5;
const int ha = 1e8;
int n1,n2,k1,k2;
int f[MAXN][MAXN][2];

inline int dfs(int i,int j,int k){
    if(!i && !j) return 1;
    if(f[i][j][k] != -1) return f[i][j][k];
    int &res = f[i][j][k];res = 0;
    if(k){
        FOR(l,1,std::min(k2,j)) (res += dfs(i,j-l,0)) %= ha;
    }
    else{
        FOR(l,1,std::min(k1,i)) (res += dfs(i-l,j,1)) %= ha;
    }
    return res;
}

int main(){
    scanf("%d%d%d%d",&n1,&n2,&k1,&k2);
    int ans = 0;CLR(f,-1);
    ans = (dfs(n1,n2,0)+dfs(n1,n2,1))%ha;
    printf("%d\n",ans);
    return 0;
}

