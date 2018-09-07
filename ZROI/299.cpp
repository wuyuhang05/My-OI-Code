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

#define LL long long
#define U unsigned
#define FOR(i,a,b) for(int i = a;i <= b;++i)
#define RFOR(i,a,b) for(int i = a;i >= b;--i)
#define CLR(i,a) memset(i,a,sizeof(i))
#define BR printf("--------------------\n")
#define DEBUG(x) std::cerr << #x << '=' << x << std::endl


const int MAXN = 100000 + 5;
const int MAXK = 20 + 5;

int N,K;
int a[MAXN];
int f[MAXN][MAXK],cnt[MAXN],t[MAXN];
int L,R,ans;
// f[i][k] = std::min(f[i][k],f[j-1][k-1] + w[j][i]);

inline int query(int l,int r){
    while(L > l) ans += cnt[a[--L]]++;
    while(R < r) ans += cnt[a[++R]]++;
    while(L < l) ans -= --cnt[a[L++]];
    while(R > r) ans -= --cnt[a[R--]];
    return ans;
}

void work(int k,int l,int r,int pl,int pr){
    if(l > r) return;
    if(l == r){
        FOR(i,pl,pr) f[l][k] = std::min(f[l][k],f[i-1][k-1] + query(i,l));
        return;
    }
    int mid = (l + r) >> 1;
    FOR(i,pl,pr)
        t[i] = f[i-1][k-1] + query(i,mid);
    int next = 0;
    FOR(i,pl,pr)
        if(!next || t[i] < t[next])
            next = i;
    f[mid][k] = t[next];
    work(k,l,mid-1,pl,next);
    work(k,mid + 1,r,next,pr);
}

int main(){
    scanf("%d%d",&N,&K);
    FOR(i,1,N)
        scanf("%d",a+i);
    L = 1;R = 0;
    memset(f,0x7f,sizeof(f));
    f[0][0] = 0;
    FOR(i,1,K) work(i,1,N,1,N);
    printf("%d\n",f[N][K]);
    return 0;
}
