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

const int MAXN = 500000+5;
int a[MAXN],s[MAXN],f[MAXN],n,m;
#define X(i) (s[i])
#define Y(i) (f[i]+s[i]*s[i])

int q[MAXN],head,tail;

inline bool chkhead(int a,int b,int c){ // c转移中 b 比 a 优
    return Y(b)-Y(a) <= 2*s[c]*(X(b)-X(a));
}

inline bool chktail(int a,int b,int c){ // 维护凸壳
    return (Y(b)-Y(a))*(X(c)-X(b)) >= (Y(c)-Y(b))*(X(b)-X(a));
}

inline int calc(int i,int j){
    return f[j]+(s[i]-s[j])*(s[i]-s[j])+m;
}

inline void Solve(){
    CLR(a,0);CLR(s,0);CLR(f,0);
    s[0] = f[0] = 0;
    FOR(i,1,n) scanf("%d",a+i),s[i] = s[i-1] + a[i];
    q[head = tail = 0] = 0;
    FOR(i,1,n){
        while(head < tail && chkhead(q[head],q[head+1],i)) head++;
        f[i] = calc(i,q[head]);
        while(head < tail && chktail(q[tail-1],q[tail],i)) tail--;
        q[++tail] = i;
    }
    printf("%d\n",f[n]);
}

int main(){
    while(~scanf("%d%d",&n,&m)) Solve();
    return 0;
}
