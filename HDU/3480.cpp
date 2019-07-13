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
#define int LL
const int MAXN = 10000+5;
int f[2][MAXN],n,m,aa[MAXN],now;

#define X(i) (aa[i+1])
#define Y(i) (f[now^1][i]+aa[i+1]*aa[i+1])

inline bool chkhead(int a,int b,int c){
    return (Y(b)-Y(a)) <= 2*(X(b)-X(a))*aa[c];
}

inline bool chktail(int a,int b,int c){
    return (Y(b)-Y(a))*(X(c)-X(b)) >= (Y(c)-Y(b))*(X(b)-X(a));
}

int q[MAXN],head,tail;

inline int calc(int i,int j){
    return f[now^1][j] + (aa[j+1]-aa[i])*(aa[j+1]-aa[i]);
}

inline void init(){
    CLR(q,0);head = tail = 0;CLR(f,0);CLR(aa,0);now = 0;
}

inline void Solve(int times){
    scanf("%lld%lld",&n,&m);
    FOR(i,1,n) scanf("%lld",aa+i);
    std::sort(aa+1,aa+n+1);
    now = 0;FOR(i,1,n) f[now][i] = (aa[i]-aa[1])*(aa[i]-aa[1]);
    FOR(i,2,m){
        now ^= 1;q[head = tail = 0] = 0;
        CLR(f[now],0);
        FOR(j,1,n){
            while(head < tail && chkhead(q[head],q[head+1],j)) head++;
            f[now][j] = calc(j,q[head]);
            while(head < tail && chktail(q[tail-1],q[tail],j)) tail--;
            q[++tail] = j;
        }
    }
    printf("Case %lld: %lld\n",times,f[now][n]);
}

signed main(){
    int T;scanf("%lld",&T);
    FOR(i,1,T) Solve(i);
    return 0;
}
