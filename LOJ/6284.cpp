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
int a[MAXN],flag[MAXN],bel[MAXN],blo,n;

inline void reset(int x){
    if(flag[x] == -1) return;
    FOR(i,(x-1)*blo+1,x*blo) a[i] = flag[x];
    flag[x] = -1;
}

inline int query(int l,int r,int c){
    int ans = 0;
    if(bel[l] == bel[r]){
        reset(bel[l]);
        FOR(i,l,r){
            if(a[i] != c) a[i] = c;
            else ans++;
        }
        return ans;
    }
    reset(bel[l]);
    FOR(i,l,bel[l]*blo){
        if(a[i] != c) a[i] = c;
        else ans++;
    }
    FOR(i,bel[l]+1,bel[r]-1){
        if(flag[i] != -1){
            if(flag[i] != c) flag[i] = c;
            else ans += blo;
        }
        else{
            FOR(j,(i-1)*blo+1,i*blo){
                if(a[j] != c) a[j] = c;
                else ans++;
            }
            flag[i] = c;
        }
    }
    reset(bel[r]);
    FOR(i,(bel[r]-1)*blo+1,r){
        if(a[i] != c) a[i] = c;
        else ans++;
    }
    return ans;
}

int main(){
    scanf("%d",&n);blo = std::sqrt(n);
    FOR(i,1,n){
        scanf("%d",a+i);
        bel[i] = (i-1)/blo + 1;
    }CLR(flag,-1);
    FOR(i,1,n){
        int l,r,c;
        scanf("%d%d%d",&l,&r,&c);
        printf("%d\n",query(l,r,c));
    }
    return 0;
}