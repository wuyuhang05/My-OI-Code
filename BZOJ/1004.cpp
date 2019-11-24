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
#define P std::pair<int,int>
#define LL long long
#define pb push_back
#define MP std::make_pair
#define all(x) x.begin(),x.end()
#define CLR(i,a) memset(i,a,sizeof(i))
#define FOR(i,a,b) for(int i = a;i <= b;++i)
#define ROF(i,a,b) for(int i = a;i >= b;--i)
#define DEBUG(x) std::cerr << #x << '=' << x << std::endl
 
const int MAXN = 20+5;
int f[MAXN*3][MAXN][MAXN][MAXN];
int a,b,c,n,m,ha;
int p[MAXN*3];
bool vis[MAXN*3];
int cnt;
 
inline int qpow(int a,int n=ha-2){
    int res = 1;
    while(n){
        if(n & 1) res = 1ll*res*a%ha;
        a = 1ll*a*a%ha;
        n >>= 1;
    }
    return res;
}
 
inline void dfs(int v){
    ++cnt;vis[v] = 1;
    if(!vis[p[v]]) dfs(p[v]);
}
std::vector<int> v;
inline int dp(int i,int a,int b,int c){
    if(a < 0 || b < 0 || c < 0) return 0;
    if(f[i][a][b][c] != -1) return f[i][a][b][c];
    int &ans = f[i][a][b][c];ans = 0;
    if(i && (!a && !b && !c)) return ans;
    if(!i && (!a && !b && !c)) return ans=1;
    int t = v[i];
//  int t = v.at(i);
//  DEBUG(t);
    (ans += dp(i-1,a-t,b,c)) %= ha;
    (ans += dp(i-1,a,b-t,c)) %= ha;
    (ans += dp(i-1,a,b,c-t)) %= ha;
//  printf("%d %d %d %d\n",a,b,c,ans);
    return ans;
}
 
inline int exgcd(int a,int b,int &x,int &y){
    if(!b){
        x = 1;y = 0;
        return a;
    }
    int g = exgcd(b,a%b,x,y);
    int t = x;x = y;y = t-(a/b)*y;
    return g;
}
 
inline int inv(int a){
    int x=0,y=0;
    int g = exgcd(a,ha,x,y);
    while(x<0) x += ha;
    x %= ha;
    return x;
}
 
int main(){
    scanf("%d%d%d%d%d",&a,&b,&c,&m,&ha);
    n = a+b+c;
    int res = 0;
    FOR(ii,1,m+1){
        if(ii == m+1) FOR(i,1,n) p[i] = i;
        else FOR(i,1,n) scanf("%d",p+i);
        CLR(vis,0);v.clear();v.pb(233);
        FOR(i,1,n){
            if(!vis[i]){
                cnt = 0;
                dfs(i);
                v.pb(cnt);
            }
        }
        int sz = (int)v.size()-1;
        CLR(f,-1);
        (res += dp(sz,a,b,c)) %= ha;
    }
    res = std::abs(res);
    res = 1ll*res*inv(m+1)%ha;
    printf("%d\n",res);
    return 0;
}
