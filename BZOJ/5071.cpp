#include <algorithm>
#include <iostream>
#include <cstring>
#include <climits>
#include <cstdio>
#include <vector>
#include <cstdlib>
#include <ctime>
#include <cmath>
#include <queue>
#include <stack>
#include <map>
#include <set>

#define fi first
#define lc (x<<1)
#define se second
#define U unsigned
#define rc (x<<1|1)
#define Re register
#define LL long long
#define MP std::make_pair
#define CLR(i,a) memset(i,a,sizeof(i))
#define FOR(i,a,b) for(Re int i = a;i <= b;++i)
#define ROF(i,a,b) for(Re int i = a;i >= b;--i)
#define SFOR(i,a,b,c) for(Re int i = a;i <= b;i+=c)
#define SROF(i,a,b,c) for(Re int i = a;i >= b;i-=c)
#define DEBUG(x) std::cerr << #x << '=' << x << std::endl

using namespace std;

const int MAXN = 1000000+5;
int a[MAXN],N,t[MAXN];
int c1[MAXN],c2[MAXN];

inline void Solve(){
    scanf("%d",&N);
    for(int i = 1;i <= N;i++) scanf("%d",a+i),a[i] += a[i-1];
    for(int i = 1;i <= N;i++) scanf("%d",t+i),t[i] += t[i-1];
    sort(a+1,a+N+1);sort(t+1,t+N+1);
    for(int i = 1;i <= N;i++) if(a[i] != t[i]){printf("NO\n");return;}
    printf("YES\n");
//    }
}

int main(){
    int T;scanf("%d",&T);
    while(T--) Solve();
    return 0;
}