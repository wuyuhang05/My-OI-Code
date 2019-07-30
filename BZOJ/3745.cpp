/*
 * Author: RainAir
 * Time: 2019-07-26 19:23:04
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

const int MAXN = 5e5 + 5;
cosnt int ha = 1e9;
int a[MAXN],n;
int mn[MAXN],mx[MAXN],s[MAXN];
int s1[MAXN],s2[MAXN];
// s1 = max*min*(i+1)
// s2 = max*min

inline void work(int l,int r){
    if(l > r) return;
    int mid = (l + r) >> 1;
    ROF(i,mid-1,l) mx[i] = std::max(mx[i+1],a[i]),mn[i] = std::min(mn[i+1],a[i]);
    FOR(i,mid+2,r) mx[i] = std::max(mx[i-1],a[i]),mn[i] = std::min(mn[i-1],a[i]);
    FOR(i,l,r) s[i] = mx[i]*mn[i];
    s1[mid+1] = s[mid+1]*(mid+2);s2[mid+1] = s[mid+1];
    FOR(i,mid+2,r) 
    int R1 = mid+1,R2 = mid+1; // R1:max,R2:min
    ROF(L,mid,l){
        while(R1 < r && mx[L] >= mx[R1+1]) R1++;
        while(R2 < r && mn[L] >= mn[R2+1]) R2++;
        int R3 = std::min(R1,R2),R4 = std::max(R1,R2);

        // R <= R3
        int S = mx[L]*mn[L],t = mid-L+1;
        ans += S*t*(R3-mid)*(R3-mid+1)/2;
        // R4 < R

    }
}

int main(){
    scanf("%d",&n);
    FOR(i,1,n) scanf("%d",a+i);
    work(1,n);
    return 0;
}
