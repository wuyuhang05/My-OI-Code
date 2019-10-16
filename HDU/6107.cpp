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
#define Re register
#define LL long long
#define pb push_back
#define MP std::make_pair
#define all(x) x.begin(),x.end()
#define CLR(i,a) memset(i,a,sizeof(i))
#define FOR(i,a,b) for(Re int i = a;i <= b;++i)
#define ROF(i,a,b) for(Re int i = a;i >= b;--i)
#define DEBUG(x) std::cerr << #x << '=' << x << std::endl

const int MAXN = 1e5 + 5;
int a[MAXN],n,w,pw,dw,maxh,q;
int Log[MAXN+233],f[2][20][MAXN*2]; // 第 i 个单词（是否有图片）往下 2^j 行可以放多少个单词
P qu[MAXN];

inline void prework(){
 //   int sum = a[1],j = 2;
    FOR(i,1,n){
        int sum = a[i],j = i+1;
        while(j <= n && sum+a[j]+1 <= w) sum += a[j++]+1;
        f[0][0][i] = j-i;sum -= a[i]+(i!=-1);
    }
    FOR(i,1,Log[n])
        FOR(j,1,n)
            f[0][i][j] = f[0][i-1][j]+f[0][i-1][j+f[0][i-1][j]];
    FOR(i,1,n){
        int sum = 0,sp = 0,j = i;
        while(j <= n && sum+a[j]+sp <= dw) sum += a[j++]+sp,sp = 1;
        sum = sp = 0;
        while(j <= n && sum+a[j]+sp <= w-dw-pw) sum += a[j++]+sp,sp = 1;
        f[1][0][i] = j-i;
    }
    FOR(i,1,Log[maxh])
        FOR(j,1,n)
            f[1][i][j] = f[1][i-1][j]+f[1][i-1][j+f[1][i-1][j]];
}

inline int calc1(int s){ //  s~n单词放多少行（无 pic）
    int ans = 0;
    while(s <= n){
        int j = 0;
        while((1<<(j+1)) <= n && s+f[0][j+1][s] <= n) j++;
        ans += (1<<j);s += f[0][j][s];
    }
    return ans;
}

inline int calc2(int type,int s,int h){ // 从单词 s 开始向下 h 行到哪个单词（0/1 pic）
    if(!h) return s;
    while(h && s <= n){
        int j = 0;
        while((1<<(j+1)) <= h) j++;
        h -= (1<<j);s += f[type][j][s];
    }
    return s;
}

inline void Solve(){
    scanf("%d%d%d%d",&n,&w,&pw,&dw);
    FOR(i,1,n) scanf("%d",a+i);CLR(f,0);
    maxh = 0;scanf("%d",&q);
    FOR(i,1,q) scanf("%d%d",&qu[i].fi,&qu[i].se),maxh = std::max(maxh,qu[i].se);
    prework();
    FOR(i,1,q){
        int x = qu[i].fi,h = qu[i].se;
        int ans = calc1(1);
        if(ans < x){
            printf("%d\n",ans+h);
            continue;
        }
        ans = x+h-1;
        int b = calc2(0,1,x-1),c = calc2(1,b,h);
        if(c <= n) ans += calc1(c);
        printf("%d\n",ans);
    }
}

int main(){
    int T;scanf("%d",&T);
    Log[0] = -1;FOR(i,1,MAXN-111) Log[i] = Log[i>>1]+1;
    while(T--) Solve();
    return 0;
}
