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
#define LD long double
#define FOR(i,a,b) for(R int i = a;i <= b;++i)
#define RFOR(i,a,b) for(R int i = a;i >= b;--i)
#define CLR(i,a) memset(i,a,sizeof(i))
#define BR printf("--------------------\n")
#define DEBUG(x) std::cerr << #x << '=' << x << std::endl

// f[i] = std::min(f[j] + (sum[i]-sum[j]L-1)^P)

const int MAXN = 100000 + 5;
const int MAXL = 30 + 5;

int N,L,P;
char str[MAXN][MAXL];
int sum[MAXN],k[MAXN],pr[MAXN];
LD f[MAXN];

int q[MAXN],head,tail;

inline LD qpow(LD a,int n){
    LD ret = 1;
    while(n){
        if(n & 1) ret = ret * a;
        a = a * a;
        n >>= 1;
    }
    return ret;
}

inline LD query(int i,int j){
    return f[j] + qpow(std::abs(sum[i]-sum[j]-L),P);
}

inline int bound(int x,int y){
    int l = x,r = N + 1;
    while(l < r){
        int mid = (l + r) >> 1;
        if(query(mid,x) >= query(mid,y)) r = mid;
        else l = mid + 1;
    }
    return l;
}

inline void Solve(){
    scanf("%d%d%d",&N,&L,&P);L++;
    FOR(i,1,N){
        scanf("%s",str[i]);
        sum[i] = sum[i-1] + strlen(str[i]) + 1;
    }
    head = tail = 1;
    q[head] = 0;
    FOR(i,1,N){
        while(head < tail && k[head] <= i) head++;
        f[i] = query(i,q[head]);
        pr[i] = q[head];
        while(head < tail && k[tail-1] >= bound(q[tail],i)) --tail;
        k[tail] = bound(q[tail],i);q[++tail] = i;
    }
    if(f[N] > 1e18) puts("Too hard to arrange");
    else{
        printf("%.0Lf\n",f[N]);
        tail = 0;
        q[tail] = N;
        int i = N;
        while(i){
            q[++tail] = i = pr[i];
        }
        while(tail){
            for(i=q[tail]+1;i < q[tail-1];i++)
                printf("%s ",str[i]);
            puts(str[i]);
            tail--;
        }
    }
    puts("--------------------");
}

int main(){
    int T;
    scanf("%d",&T);
    while(T--){
        Solve();
    }
    return 0;
}
