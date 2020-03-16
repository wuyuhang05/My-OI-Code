#include<bits/stdc++.h>

#define fi first
#define se second
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
#define int LL
const int MAXN = 1e6 + 5;

int n,k;
int a[MAXN],wa,wb;

inline void work(int f[],int k){
    std::priority_queue<int> q;int sm = 0,tag = 0;
    FOR(i,1,k) q.push(-a[i]+(k-i)*wa),sm += -a[i]+(k-i)*wa;f[k] = sm;
    FOR(i,1,k-1) f[i] = 1e18;
    FOR(i,k+1,n){
        tag += wa;q.push(-a[i]-tag);sm += -a[i]-tag;
        sm -= q.top();q.pop();
        f[i] = sm+tag*k; 
    }
    FOR(i,1,n) if(f[i] != 1e18) f[i] -= wa*k*(k-1)/2;
}
int pre[MAXN],suf[MAXN];
signed main(){
    scanf("%lld%lld",&n,&k);
    FOR(i,1,n) scanf("%lld",a+i);
    scanf("%lld%lld",&wa,&wb);
    int ans = 0;FOR(i,1,n) ans += a[i];int sm = ans;
    work(pre,k/2);std::reverse(a+1,a+n+1);work(suf,k-k/2);std::reverse(suf+1,suf+n+1);
    FOR(i,0,n) ans = std::min(ans,pre[i]+suf[i+1]+sm+wb);
    printf("%lld\n",ans);
    return 0;
}
