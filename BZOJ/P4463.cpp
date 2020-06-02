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

const int MAXN = 1500+5;

int k,n,ha;
int f[505][MAXN];// 考虑 前 i 位 <=j
int y[MAXN],now;

inline int qpow(int a,int n=ha-2){
	int res = 1;
	while(n){
		if(n & 1) res = 1ll*res*a%ha;
		a = 1ll*a*a%ha;
		n >>= 1;
	}
	return res;
}

inline int cha(int n,int x){
    int res = 0;
    if(x <= n) return y[x];
    FOR(i,1,n){
        int up = y[i],down = 1;
        FOR(j,1,n){
            if(i == j) continue;
            up = 1ll*up*(x-j)%ha;
            down = 1ll*down*(i+ha-j)%ha;
        }
        up = 1ll*up*qpow(down)%ha;
        (res += up) %= ha;
    }
    return res;
}

int main(){
    scanf("%d%d%d",&k,&n,&ha);
    FOR(i,0,2*n+2) f[0][i] = 1;
    FOR(i,1,n){
        FOR(j,1,2*n+2){
            f[i][j] = (1ll*f[i-1][j-1]*j%ha+f[i][j-1]) % ha;
        }
    }
    FOR(i,1,2*n+2) y[i] = f[n][i];
    int ans = cha(2*n+2,k);
    FOR(i,1,n) ans = 1ll*ans*i%ha;
    printf("%d\n",ans);
    return 0;
}
