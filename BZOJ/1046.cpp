/*
 * Author: RainAir
 * Time: 2019-07-24 15:22:10
 */
#include <algorithm>
#include <iostream>
#include <cstring>
#include <climits>
#include <cstdlib>
#include <cstdio>
#include <bitset>
#include <vector>
#include <cmath>
#include <ctime>
#include <queue>
#include <stack>
#include <map>
#include <set>

#define fi first
#define se second
#define U unsigned
#define P std::pair
#define Re register
#define LL long long
#define pb push_back
#define MP std::make_pair
#define all(x) x.begin(),x.end()
#define CLR(i,a) memset(i,a,sizeof(i))
#define FOR(i,a,b) for(Re int i = a;i <= b;++i)
#define ROF(i,a,b) for(Re int i = a;i >= b;--i)
#define DEBUG(x) std::cerr << #x << '=' << x << std::endl

const int MAXN = 10000+5;
int a[MAXN];
int q[MAXN],tot,b[MAXN],t[MAXN],f[MAXN];
int n;

inline int find(int x){
    int l = 1,r = tot,ans = 0;
    while(l <= r){
        int mid = (l + r) >> 1;
        if(q[mid] > x){
            ans = std::max(ans,mid);
            l = mid+1;
        }
        else r = mid-1;
    }
    return ans;
}

inline void work(){
    tot = 0;
    FOR(i,1,n){
        int rs = find(b[i]);
        f[i] = rs+1;
        tot = std::max(tot,f[i]);
        if(q[rs+1] < b[i]) q[rs+1] = b[i];
    }
}

int main(){
    scanf("%d",&n);
    FOR(i,1,n) scanf("%d",a+i),b[i] = a[i];
    std::reverse(b+1,b+n+1);
    work(); // Under
    std::reverse(f+1,f+n+1);
    int m;scanf("%d",&m);
    while(m--){
        int l;scanf("%d",&l);
        if(l > tot){
            puts("Impossible");
            continue;
        }int v = 0;
        FOR(i,1,n){
            if(f[i] >= l && a[i] > v){
                printf("%d ",a[i]);
                v = a[i];l--;
                if(!l) break;
            }
        }
        puts("");
    }
    return 0;
}
