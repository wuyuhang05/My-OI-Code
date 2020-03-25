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
const int MAXN = 2e6 + 5;
const int ha = 998244353;
int a[MAXN],n,x;

inline int qpow(int a,int n=ha-2){
    int res = 1;
    while(n){
        if(n & 1) res = 1ll*res*a%ha;
        a = 1ll*a*a%ha;
        n >>= 1;
    }
    return res;
}
int fac[MAXN],inv[MAXN];
inline int C(int n,int m){
    return 1ll*fac[n]*inv[m]%ha*inv[n-m]%ha;
}

int main(){
    scanf("%d%d",&n,&x);
    fac[0] = 1;
    FOR(i,1,MAXN-1) fac[i] = 1ll*fac[i-1]*i%ha;
    inv[MAXN-1] = qpow(fac[MAXN-1]);
    ROF(i,MAXN-2,0) inv[i] = 1ll*inv[i+1]*(i+1)%ha;
    FOR(i,1,n) scanf("%d",a+i);
    int ext = 0;
    FOR(i,1,n) (ext += 1ll*a[i]*(a[i]-1)%ha) %= ha;
    int ans = 1ll*x*x%ha;
    (ans += ha-1ll*(2*x-1)*(n-1)%ha*C(n-2,x-2)%ha*qpow(C(n,x))%ha)%=ha;
    (ans += 1ll*ext*C(n-3,x-3)%ha*qpow(C(n,x))%ha) %= ha;
    (ans += (1ll*(n-1)*(n-2)%ha+ha-ext)%ha*C(n-4,x-4)%ha*qpow(C(n,x))%ha) %= ha;
    printf("%d\n",ans);
    return 0;
}
//E[x^2] = E[(|V|-|E|)^2] = E[|V|^2]+E[|E|^2]-E[2|V||E|]
//E[|V|^2] = |V|^2
//E[2|V||E|] = 2(n-1)C(n-2,x-2)/C(n,x)
//E[|E|^2]: 选择一个边的有序对
//ext表示有公共点的边对
//讨论有几个公共点(0,1,2)
//E[|E|^2] = ((n-1)*(n-2)-ext)*(C(n-4,x-4))/(C(n,x)) + ext*C(n-3,x-3)/C(n,x) + (n-1)*C(n-2,x-2)/C(n,x)
