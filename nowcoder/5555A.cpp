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

inline bool pd(int x){
    int q = std::sqrt(1.0*x);
    return q*q==x;
}
const int MAXN = 2000+5;
const int ha = 998244353;
int f[MAXN][MAXN];
int main(){
    int n,m;scanf("%d%d",&n,&m);
    int mx = 1;
    FOR(i,2,m){
        if(m%i) continue;
        if(!pd(i)) continue;
        mx = std::max(mx,i);
    }
    FOR(i,0,n) f[0][i] = 1;
    mx = std::sqrt(1.0*mx);
    FOR(i,1,mx){
        f[i][1] = 1;
        FOR(j,2,n){
            if(i-j >= 0) (f[i][j] += f[i-j][j]) %= ha;
            (f[i][j] += f[i][j-1])%=ha;
        }
    }
//    DEBUG(f[2][2]);
    printf("%d\n",f[mx][n]);
    return 0;
}

