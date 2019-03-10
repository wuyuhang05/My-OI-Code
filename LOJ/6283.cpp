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

const int ha = 10000 + 7;
const int MAXN = 100000 + 5;

int a[MAXN],add[MAXN],mul[MAXN],bel[MAXN],blo,n;

inline void push(int x){
    FOR(i,(x-1)*blo+1,std::min(x*blo,n)) a[i] = (a[i]*mul[bel[i]]+add[bel[i]])%ha;
    mul[x] = 1;add[x] = 0;
}

inline void modify1(int l,int r,int c){
    if(bel[l] == bel[r]){
        push(bel[l]);
        FOR(i,l,r) (a[i] += c) %= ha;
        return;
    }
    push(bel[l]);
    FOR(i,l,bel[l]*blo) (a[i] += c) %= ha;
    FOR(i,bel[l]+1,bel[r]-1) (add[i] += c) %= ha;
    push(bel[r]);
    FOR(i,(bel[r]-1)*blo+1,r) (a[i] += c) %= ha;
}

inline void modify2(int l,int r,int c){
    if(bel[l] == bel[r]){
        push(bel[l]);
        FOR(i,l,r) (a[i] *= c) %= ha;
        return;
    }
    push(bel[l]);
    FOR(i,l,bel[l]*blo) (a[i] *= c) %= ha;
    FOR(i,bel[l]+1,bel[r]-1){
        (add[i] *= c) %= ha;
        (mul[i] *= c) %= ha;
    }
    push(bel[r]);
    FOR(i,(bel[r]-1)*blo+1,r) (a[i] *= c) %= ha;
}

int main(){
    scanf("%d",&n);blo = std::sqrt(n);
    FOR(i,1,n){
        scanf("%d",a+i);
        bel[i] = (i-1)/blo + 1;
    }
    FOR(i,1,bel[n]) mul[i] = 1;
    FOR(i,1,n){
        int opt,l,r,c;
        scanf("%d%d%d%d",&opt,&l,&r,&c);
        if(opt == 0) modify1(l,r,c);
        if(opt == 1) modify2(l,r,c);
        if(opt == 2) push(bel[r]),printf("%d\n",a[r]%ha);
    }
    return 0;
}