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

const int MAXN = 5e5 + 5;
LL a[MAXN],b[MAXN];
LL pre[MAXN],suf[MAXN],f[MAXN],g[MAXN],h[MAXN];
int n,m;
std::vector<LL> ext;

inline void work(int l,int r,int L,int R){//f[[L,R]]+g[]
    if(l > r) return;
    if(L == R){
        FOR(i,l,r) h[i] = std::max(h[i],f[L]+g[i-L]);
        return;
    }
    int mid = (l + r) >> 1;int ps = 0;
    FOR(i,L,std::min(mid,R)){
        if(f[i]+g[mid-i] > h[mid]){
            h[mid] = f[i]+g[mid-i];ps = i;
        }
    }
    work(l,mid-1,L,ps);work(mid+1,r,ps,R);
}

int main(){
    scanf("%d",&n);
    FOR(i,1,n) scanf("%lld",a+i);
    std::sort(a+1,a+n+1);
    FOR(i,1,n){
        if(a[i] == a[i-1]) ext.pb(a[i]);
        else b[++m] = a[i];
    }
    std::reverse(b+1,b+m+1);std::sort(all(ext));std::reverse(all(ext));
    FOR(i,1,m) pre[i] = pre[i-1]+b[i];
    ROF(i,m,1) suf[i] = std::__gcd(suf[i+1],b[i]);
    f[1] = suf[1];f[m] = pre[m];int p = 1;
    FOR(i,2,m-1){
        if(suf[i] != suf[i+1] || (i == 2)){
            FOR(j,1,i) if(std::__gcd(suf[i+1],b[j])-b[j] > std::__gcd(suf[i+1],b[p])-b[p]) p = j;
        }
        if(std::__gcd(suf[i+1],b[i])-b[i] > std::__gcd(suf[i+1],b[p])-b[p]) p = i;
        f[i] = std::__gcd(suf[i+1],b[p])-b[p]+pre[i];
    }
    FOR(i,1,(int)ext.size()) g[i] = g[i-1]+ext[i-1];
    work(1,n,1,m);
    FOR(i,1,n) printf("%lld\n",h[i]);
    return 0;
}
