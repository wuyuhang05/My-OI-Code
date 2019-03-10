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

const int MAXN = 1000000+5;
const int MAXM = 1000+5;

std::vector<int> v[MAXN];
int a[MAXN],bel[MAXN],tag[MAXN],blo,n,q;

inline void reset(int x){
    v[x].clear();
    FOR(i,(x-1)*blo+1,x*blo) v[x].push_back(a[i]);
    std::sort(v[x].begin(),v[x].end());
}

inline void modify(int l,int r,int x){
    if(bel[l] == bel[r]){
        FOR(i,l,r) a[i] += x;reset(bel[l]);
        return;
    }
    FOR(i,l,bel[l]*blo) a[i] += x;reset(bel[l]);
    FOR(i,bel[l]+1,bel[r]-1) tag[i] += x;
    FOR(i,(bel[r]-1)*blo+1,r) a[i] += x;
    reset(bel[r]);
}

inline int query(int l,int r,int c){
    int ans = 0;
    if(bel[l] == bel[r]){
        FOR(i,l,r) if(a[i]+tag[bel[i]] >= c) ans++;
        return ans;
    }
    FOR(i,l,bel[l]*blo) if(a[i]+tag[bel[i]] >= c) ans++;
    FOR(i,bel[l]+1,bel[r]-1){
        int t = c-tag[i];
        if(v[i][blo-1] < t) continue;
        int p = std::lower_bound(v[i].begin(),v[i].end(),t)-v[i].begin()+1;
        ans += (blo-p+1);
    }
    FOR(i,(bel[r]-1)*blo+1,r) if(a[i]+tag[bel[i]] >= c) ans++;
    return ans;
}

int main(){
    scanf("%d%d",&n,&q);blo = std::sqrt(n*1.0);
    FOR(i,1,n){
        scanf("%d",a+i);
        v[(bel[i] = (i-1)/blo + 1)].push_back(a[i]);
    }
    FOR(i,1,bel[n]) std::sort(v[i].begin(),v[i].end());
    while(q--){
        char str[12];int l,r,c;
        scanf("%s%d%d%d",str+1,&l,&r,&c);
        if(str[1] == 'M'){
            modify(l,r,c);
        }
        else{
            printf("%d\n",query(l,r,c));
        }
    }
    return 0;
}