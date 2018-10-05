#include <algorithm>
#include <iostream>
#include <cstring>
#include <climits>
#include <cstdio>
#include <vector>
#include <cmath>
#include <queue>
#include <stack>
#include <map>
#include <set>

#define R register
#define LL long long
#define U unsigned
#define FOR(i,a,b) for(R int i = a;i <= b;++i)
#define RFOR(i,a,b) for(R int i = a;i >= b;--i)
#define CLR(i,a) memset(i,a,sizeof(i))
#define BR printf("--------------------\n")
#define DEBUG(x) std::cerr << #x << '=' << x << std::endl

const int MAXN = 500000 + 5;
int N,M;
int a[MAXN],f[MAXN],sum[MAXN];
int q[MAXN],head,tail;

// f[i] = min{f[j] + (sum[i]-sum[j-1])^2 + M}
//
#define Y(i) (f[i] + sum[i] * sum[i])
#define X(i) (sum[i])

inline bool headpop(int a,int b,int x){
    return Y(b) - Y(a) <= 2 * sum[x] * (X(b) - X(a));
}

inline bool tailpop(int a,int b,int c){
    return (Y(b) - Y(a)) * (X(c) - X(b)) >= (Y(c) - Y(b)) * (X(b) - X(a));
}

inline int calc(int i,int j){
    return f[j] + (sum[i]-sum[j])*(sum[i]-sum[j]) + M;
}

int main(){
    while(~scanf("%d%d",&N,&M)){
        FOR(i,1,N) scanf("%d",a + i);
        f[0] = sum[0] = 0;
        FOR(i,1,N) sum[i] = sum[i-1] + a[i];
        q[head = tail = 0] = 0;
        FOR(i,1,N){
            while(head < tail && headpop(q[head],q[head+1],i)) head++;
            f[i] = calc(i,q[head]);
            while(head < tail && tailpop(q[tail-1],q[tail],i)) tail--;
            q[++tail] = i;
        }
        printf("%d\n",f[N]);
    }
    return 0;
}
