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
const int MAXN = 30000+5;
int f[2][MAXN];
int n,m,sm[MAXN],now;

inline int w(int l,int r){
    return (sm[r]-sm[l])*(sm[r]-sm[l]);
}

inline void work(int l,int r,int L,int R){
    if(l > r) return;
    int mid = (l + r) >> 1,ps = -1;
    FOR(i,L,std::min(R,mid-1)){
        if(f[now][mid] > f[now^1][i]+w(i,mid)){
            f[now][mid] = f[now^1][i]+w(i,mid);
            ps = i;
        }
    }
    assert(ps != -1);
    work(l,mid-1,L,ps);work(mid+1,r,ps,R);
}

signed main(){
    scanf("%lld%lld",&n,&m);
    FOR(i,1,n) scanf("%lld",sm+i),sm[i] += sm[i-1];
    CLR(f[now],0x3f);f[now][0] = 0;
    FOR(i,1,m){
        now ^= 1;CLR(f[now],0x3f);
        work(i,n,0,n);
    }
    int ans = f[now][n];
    ans*=m;
    ans -= sm[n]*sm[n];
    printf("%lld\n",ans);
    return 0;
}
