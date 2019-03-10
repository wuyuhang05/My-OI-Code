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
int a[MAXN],bel[MAXN],cnt[MAXN],origin[MAXN],blo,lastans;
std::vector<int> p[MAXN];
std::vector<int> v;
int f[2010][2010];
int n,m;

inline void init(int x){
    CLR(cnt,0);
    int max=0,pos=0;
    FOR(i,(x-1)*blo+1,n){
        cnt[a[i]]++;
        if(cnt[a[i]] > max){
            max = cnt[a[i]];
            pos = a[i];
        }
        else if(cnt[a[i]] == max && a[i] < pos) pos = a[i];
        f[x][bel[i]] = pos;
    }
}

inline int calc(int l,int r,int x){
    return std::upper_bound(p[x].begin(),p[x].end(),r) - std::lower_bound(p[x].begin(),p[x].end(),l);
}

inline int query(int l,int r){
    int ans = 0,max = 0;
    if(bel[l] == bel[r]){
        FOR(i,l,r){
            int t = calc(l,r,a[i]);
            if(t > max){
                max = t;
                ans = a[i];
            }
            else if(t == max && a[i] < ans) ans = a[i];
        }
        return ans;
    }
    ans = f[bel[l]+1][bel[r]-1];
    max = calc(l,r,ans);
    FOR(i,l,bel[l]*blo){
        int t = calc(l,r,a[i]);
        if(t > max){
            max = t;ans = a[i];
        }
        else if(t == max && a[i] < ans) ans = a[i];
    }
    FOR(i,(bel[r]-1)*blo+1,r){
        int t = calc(l,r,a[i]);
        if(t > max){
            max = t;ans = a[i];
        }
        else if(t == max && a[i] < ans) ans = a[i];
    }
    return ans;
}

int main(){
    scanf("%d%d",&n,&m);
    blo = std::sqrt(n/log(n));
    FOR(i,1,n){
        scanf("%d",a+i);
        v.push_back(a[i]);
        bel[i] = (i-1)/blo+1;
    }
    std::sort(v.begin(),v.end());
    v.erase(std::unique(v.begin(),v.end()),v.end());
    FOR(i,1,n){
        int t = std::lower_bound(v.begin(),v.end(),a[i])-v.begin()+1;
        origin[t] = a[i];a[i] = t;
        p[a[i]].push_back(i);
    }
    FOR(i,1,bel[n]) init(i);
    FOR(i,1,m){
        int l,r;scanf("%d%d",&l,&r);
        l = (l+lastans-1)%n+1;r = (r+lastans-1)%n+1;
        if(l > r) std::swap(l,r);
        printf("%d\n",lastans = origin[query(l,r)]);
    }
    return 0;
}