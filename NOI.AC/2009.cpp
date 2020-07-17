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

const int MAXN = 20000+5;

int f[2][MAXN],now;
int n,m;
int a[MAXN],b[MAXN];

inline void up(int &x,int y){
    if(x < y) x = y;
}

int main(){
    scanf("%d%d",&n,&m);
    FOR(i,1,n-1) scanf("%d%d",a+i,b+i);
    now = 0;CLR(f[now],-0x3f);
    FOR(i,0,m-1) f[now][i] = i;
    FOR(i,1,n-1){
        CLR(f[now^1],-0x3f);
        FOR(j,0,MAXN-1){
            if(f[now][j] == -0x3f3f3f3f) continue;
            if(j >= a[i]+b[i]) up(f[now^1][j],f[now][j]);
            if(a[i] <= j && j < a[i]+b[i]) up(f[now^1][j-a[i]],f[now][j]);
            if(j < a[i]) if(j+b[i] < MAXN) up(f[now^1][j+b[i]],f[now][j]+b[i]); 
        }
        int mx = -0x3f3f3f3f;
        FOR(j,0,a[i]-1){
            if(f[now][j] == -0x3f3f3f3f) continue;
            mx = std::max(mx,f[now][j]);
        }
        FOR(j,0,b[i]-1) up(f[now^1][j],mx+j);
        now ^= 1;
    }
    int ans = -0x3f3f3f3f;
    FOR(i,0,MAXN-1) up(ans,f[now][i]);
    printf("%d\n",ans);
    return 0;
}
