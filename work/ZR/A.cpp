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
#define db double
#define U unsigned
#define P std::pair<int,int>
#define LL long long
#define pb push_back
#define MP std::make_pair
#define all(x) x.begin(),x.end()
#define CLR(i,a) memset(i,a,sizeof(i))
#define FOR(i,a,b) for(int i = a;i <= b;++i)
#define ROF(i,a,b) for(int i = a;i >= b;--i)
#define DEBUG(x) std::cerr << #x << '=' << x << std::endl

const int MAXN = 5000;
int a[MAXN+5],n;
int t[MAXN*2+10];
int now = 0;

inline void add(int p,int t){
    if(!a[p]) now++;
    a[p] += t;
}

inline void upd(int x){
    add(a[x],1);
    while(a[x] > 1){
        add(a[x+1],a[x]/2);
        a[x] %= 2;if(!a[x]) now--;
        x++;
    }
}

int main(){
    scanf("%d",&n);
    FOR(i,1,n) scanf("%d",a+i);int ans = n;
    FOR(l,1,n){
        int mx = a[l],mn = a[l];
        FOR(r,l+1,n){
            mx = std::max(mx,a[r]);mn = std::min(mn,a[r]);
            if(mx-mn > n) break;
            upd(a[r]-a[l]+MAXN);
            if(now == 1) ans++;
        }
        if(l != n-1) CLR(t,0),now = 0;
    }
    printf("%d\n",ans);
    return 0;
}
