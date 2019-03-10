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

const int MAXN = 100000+5;
const int blo = 1000;
int a[MAXN],bel[MAXN],tag[MAXN],n;
std::vector<int> v[blo];

inline void reset(int x){
    v[x].clear();
    FOR(i,(x-1)*blo+1,x*blo) v[x].push_back(a[i]);
    std::sort(v[x].begin(),v[x].end());
}

inline void modify(int l,int r,int c){
    if(bel[l] == bel[r]){
        FOR(i,l,r) a[i] += c;
        reset(bel[l]);return;
    }
    FOR(i,l,bel[l]*blo) a[i] += c;
    reset(bel[l]);
    FOR(i,bel[l]+1,bel[r]-1) tag[i] += c;
    FOR(i,(bel[r]-1)*blo+1,r) a[i] += c;
    reset(bel[r]);
}

inline int query(int l,int r,int c){
    int ans = -1;
    if(bel[l] == bel[r]){
        FOR(i,l,r) 
            if(a[i] + tag[bel[i]] < c)
                ans = std::max(ans,a[i]+tag[bel[i]]);
        return ans;
    }
    FOR(i,l,bel[l]*blo){
        if(a[i] + tag[bel[i]] < c) ans = std::max(ans,a[i]+tag[bel[i]]);
    }
    FOR(i,bel[l]+1,bel[r]-1){
        int x = c-tag[i];
        int t = std::lower_bound(v[i].begin(),v[i].end(),x) - v[i].begin();
        if(t) ans = std::max(ans,v[i][t-1]+tag[i]);
    }
    FOR(i,(bel[r]-1)*blo+1,r)
        if(a[i] + tag[bel[i]] < c)
            ans = std::max(ans,a[i]+tag[bel[i]]);
    return ans;
}

int main(){
    scanf("%d",&n);
    FOR(i,1,n) scanf("%d",a+i);
    FOR(i,1,n){
        bel[i] = (i-1)/blo + 1;
        v[bel[i]].push_back(a[i]);
    }
    FOR(i,1,bel[n]) std::sort(v[i].begin(),v[i].end());
    FOR(i,1,n){
        int opt,l,r,c;
        scanf("%d%d%d%d",&opt,&l,&r,&c);//DEBUG(opt);
        if(!opt){
            modify(l,r,c);
        }
        else{
            printf("%d\n",query(l,r,c));
        }
    }
    return 0;
}