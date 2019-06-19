#include <algorithm>
#include <iostream>
#include <cstring>
#include <climits>
#include <cstdlib>
#include <cstdio>
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

const int MAXN = 100000+5;
int a[MAXN],ans[MAXN],n,ret,qx[MAXN],qy[MAXN];

int main(){
    scanf("%d",&n);
    FOR(i,1,n) scanf("%d",a+i);
    CLR(ans,0x3f);
    for(int i = 0;i <= 1050000;i = (int)((i+1)*1.05)){
        int lx = 1,ly = 1,rx = 0,ry = 0,ret = 0,p = 0;
        FOR(j,1,n){
            while(p <= n && (lx > rx || ly > ry || a[qx[lx]]-a[qy[ly]] <= i)){
                p++;
                while(lx <= rx && a[qx[rx]] <= a[p]) --rx;
                while(ly <= ry && a[qy[ry]] >= a[p]) --ry;
                qx[++rx] = qy[++ry] = p;
            }
            ret = std::max(ret,p-j);
            if(qx[lx] == j) lx++;
            if(qy[ly] == j) ly++;
        }
        ans[ret] = std::min(ans[ret],i);
    }
    ROF(i,n-1,2) ans[i] = std::min(ans[i],ans[i+1]);
    FOR(i,2,n) printf("%d\n",ans[i]);
    return 0;
}
