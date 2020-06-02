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

const int MAXN = 1e6 + 5;
const int MAXM = 1e7 + 6;

bool p[MAXM];
int prime[MAXN],cnt;

inline void prework(){
    FOR(i,2,MAXM-1){
        if(!p[i]) prime[++cnt] = i;
        for(int j = 1;j <= cnt && i*prime[j] < MAXM;++j){
            p[i*prime[j]] = 1;
            if(!(i%prime[j])) break;
        }
    }
}

int n,a[MAXN],ans[MAXN];
int pre[MAXN],suf[MAXN],f[MAXM];
std::vector<int> dec[MAXN];

inline bool work(int l,int r,int fa=0){
    if(l > r) return 1;
    if(l == r){ans[l] = fa;return 1;}
    int mid = -1;
    FOR(i,0,r-l){
        if(pre[l+i] < l && suf[l+i] > r){
            mid = l+i;break;
        }
        if(pre[r-i] < l && suf[r-i] > r){
            mid = r-i;break;
        }
    }
    if(mid == -1) return 0;
    ans[mid] = fa;return work(l,mid-1,mid)&&work(mid+1,r,mid);
}

int main(){prework();
    scanf("%d",&n);
    FOR(i,1,n){
        int x;scanf("%d",&x);
        int q = std::sqrt(1.0*x);
        FOR(j,1,cnt){
            if(prime[j] > q || prime[j] > x) break;
            if(x%prime[j]) continue;
            dec[i].pb(prime[j]);
            while(!(x%prime[j])) x /= prime[j];
        }
        if(x != 1) dec[i].pb(x);
    }
    CLR(f,0);
    FOR(i,1,n){
        for(auto x:dec[i]){
            pre[i] = std::max(pre[i],f[x]);
            f[x] = i;
        }
    }
    CLR(f,0x3f);CLR(suf,0x3f);
    ROF(i,n,1){
        for(auto x:dec[i]){
            suf[i] = std::min(suf[i],f[x]);
            f[x] = i;
        }
    }
    bool fg = work(1,n);
    if(fg){
        FOR(i,1,n) printf("%d%c",ans[i]," \n"[i==n]);
    }
    else puts("impossible");
    return 0;
}
