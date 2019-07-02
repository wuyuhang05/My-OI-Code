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

const int MAXN = 3e5 + 5;
int n,a[MAXN],mx[MAXN],tag[MAXN],tot;
LL ans;
int main(){
    scanf("%d",&n);
    FOR(i,1,n) scanf("%d",a+i);
    FOR(i,1,n){
        if(a[i] != 1) continue;
        mx[i] = 1;
        ROF(j,i-1,1){
            if(a[j] == 1) break;
            mx[j] = std::max(mx[j+1],a[j]);
        }
        FOR(j,i+1,n){
            if(a[j] == 1) break;
            mx[j] = std::max(mx[j-1],a[j]);
        }
        ++tot;
        int L = i,R = i;
        while(tag[a[L]] != tot && L >= 1) tag[a[L--]] = tot;
        for(L++;L <= i;tag[a[L++]] = tot-1){
            while(R > i && (R-L+1 > mx[L] || mx[R] >= mx[L])) tag[a[R--]] = tot-1;
            while(R < n && R-L+1 < mx[L]){
                if(tag[a[R+1]] == tot || a[R+1] >= mx[L]) break;
                tag[a[++R]] = tot;
            }
            if(R-L+1 == mx[L]) ans++;
        }
        ++tot;
        L = i,R = i;
        while(tag[a[R]] != tot && R <= n) tag[a[R++]] = tot;
        for(R--;R > i;tag[a[R--]] = tot-1){
            while(L < i && (R-L+1 > mx[R] || mx[L] >= mx[R])) tag[a[L++]] = tot-1;
            while(L > 1 && R-L+1 < mx[R]){
                if(tag[a[L-1]] == tot || a[L-1] >= mx[R]) break;
                tag[a[--L]] = tot;
            }
            if(R-L+1 == mx[R]) ans++;
        }
    }
    printf("%lld\n",ans);
    return 0;
}
