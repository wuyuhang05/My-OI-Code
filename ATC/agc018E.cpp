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

const int MAXN = 5e6 + 5;
const int ha = 1e9 + 7;

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

inline void prework(){
    fac[0] = 1;FOR(i,1,MAXN-1) fac[i] = 1ll*fac[i-1]*i%ha;
    inv[MAXN-1] = qpow(fac[MAXN-1]);
    ROF(i,MAXN-2,0) inv[i] = 1ll*inv[i+1]*(i+1)%ha;
}

inline int C(int n,int m){
    if(n < m) return 0;
    if(!m) return 1;
    return 1ll*fac[n]*inv[m]%ha*inv[n-m]%ha;
}

inline int calc1(int x,int y){// (0,0) 到 (x,y)
    if(x < 0 || y < 0) return 0;
    return C(x+y,x);
}

inline int calc2(int x,int y){ // (0,0) 到 ([0,x],[0,y])
    return (calc1(x+1,y+1)+ha-1)%ha;
}

inline int calc3(int x1,int x2,int y1,int y2){// (0,0) 到 ([x1,x2],[y1,y2])
    int res = calc1(x2+1,y2+1);
    (res += ha-calc1(x2+1,y1)) %= ha;
    (res += ha-calc1(x1,y2+1)) %= ha;
    (res += calc1(x1,y1)) %= ha;
    return res;
}

inline int calc4(int x,int y,int x1,int x2,int y1,int y2){// (x,y) 到 ([x1,x2],[y1,y2])
    return std::min(x1,x2) >= x && std::min(y1,y2) >= y ? calc3(x1-x,x2-x,y1-y,y2-y) : calc3(x-x2,x-x1,y-y2,y-y1);
    // 实际应用是要判包含的 但是这个题不会
}
int x[233],y[233];
int main(){
    prework();
    FOR(i,1,6) scanf("%d",x+i);
    FOR(i,1,6) scanf("%d",y+i);
    int ans = 0;
    FOR(i,x[3],x[4]){
        (ans += 1ll*(ha-(i+y[3])%ha)*calc4(i,y[3]-1,x[1],x[2],y[1],y[2])%ha*calc4(i,y[3],x[5],x[6],y[5],y[6])%ha) %= ha;
        (ans += 1ll*(i+y[4]+1)%ha*calc4(i,y[4],x[1],x[2],y[1],y[2])%ha*calc4(i,y[4]+1,x[5],x[6],y[5],y[6])%ha) %= ha;
    }
    FOR(i,y[3],y[4]){
        (ans += 1ll*(ha-(i+x[3])%ha)*calc4(x[3]-1,i,x[1],x[2],y[1],y[2])%ha*calc4(x[3],i,x[5],x[6],y[5],y[6])%ha) %= ha;
        (ans += 1ll*(x[4]+i+1)%ha*calc4(x[4],i,x[1],x[2],y[1],y[2])%ha*calc4(x[4]+1,i,x[5],x[6],y[5],y[6])%ha) %= ha;
    }
    printf("%d\n",ans);
    return 0;
}
