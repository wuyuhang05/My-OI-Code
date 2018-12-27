#include <unordered_map>
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
#define int LL
#define Re register
#define LL long long
#define U unsigned
#define FOR(i,a,b) for(Re int i = a;i <= b;++i)
#define ROF(i,a,b) for(Re int i = a;i >= b;--i)
#define SFOR(i,a,b,c) for(Re int i = a;i <= b;i+=c)
#define SROF(i,a,b,c) for(Re int i = a;i >= b;i-=c)
#define CLR(i,a) memset(i,a,sizeof(i))
#define BR printf("--------------------\n")
#define DEBUG(x) std::cerr << #x << '=' << x << std::endl

const int MAXN = 1000000+5;

int N,size,ans;
int bl[MAXN],a[MAXN],b[MAXN];
int lst[MAXN],pre[MAXN],origin[MAXN],tag[MAXN];
std::unordered_map<LL,int> S[1022];

void modify(int x,LL val,int mn){
    int l = std::max(mn+1,(bl[x]-1)*size+1),r = std::min(bl[x]*size,N);
    if(l == x){
        for(int i = bl[x];(i-1)*size < N;++i) tag[i] ^= val;
        return;
    }
    S[bl[x]].erase(S[bl[x]].begin(),S[bl[x]].end());
    FOR(i,l,r) a[i] ^= tag[bl[x]];
    tag[bl[x]] = 0;
    FOR(i,x,r) a[i] ^= val;
    FOR(i,l,r) ++S[bl[x]][a[i]];
    for(int i = bl[x]+1;(i-1)*size < N;++i) tag[i] ^= val;
}

int calc(){
    int num=0;
    for(int i = 1;(i-1)*size < N;++i){
        if(S[i].find(tag[i]) != S[i].end()) num += S[i][tag[i]];
    }
    return num;
}


LL seed = 20050117;
LL gen(){
    seed = (1ll*seed*19260817%1000000007+323232323^998244353);
    return seed;
}


signed main(){
    scanf("%lld",&N);size = std::sqrt(N);
    FOR(i,1,N) bl[i] = (i-1)/size + 1;
    FOR(i,1,N) scanf("%lld",a+i),b[i] = a[i];
    ROF(i,N,1) lst[i] = pre[a[i]],pre[a[i]] = i;
    std::sort(b+1,b+N+1);
    FOR(i,1,N) origin[b[i]] = (b[i] == b[i-1]) ? origin[b[i-1]] : 1ll*gen()*gen();
    FOR(i,1,N) a[i] = origin[a[i]];
    ROF(i,N,1){
        if(lst[i]) modify(lst[i],a[i],i);
        ++S[bl[i]][a[i] = tag[bl[i]]];
        ans += calc();
    }
    printf("%lld\n",ans);
    return 0;
}
/*
4
2 2 2 3
*/