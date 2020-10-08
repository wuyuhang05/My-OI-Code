#include <bits/stdc++.h>

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

const int MAXN = 15 + 1;

int n,m,ha;

inline void add(int &x,int y){
    x += y;if(x >= ha) x -= ha;
}
// a < b : a -> b
int small[(1<<MAXN)+3],big[(1<<MAXN)+3];
int f[MAXN][(1<<MAXN)+3];
// 选出了 S 内 i 组,组内相同的方案数
// 每次从小到大划分组

int tmp[MAXN];

inline int C(int n,int m){
    if(n < m) return 0;
    FOR(i,1,m) tmp[i] = n-i+1;
    FOR(i,2,m){
        int x = i;
        FOR(j,1,m){
            int g = std::__gcd(tmp[j],x);
            x /= g;tmp[j] /= g;
        }
    }
    int ans = 1;
    FOR(i,1,m) ans = 1ll*ans*tmp[i]%ha;
    return ans;
}

int main(){
    scanf("%d%d%d",&m,&n,&ha);//ha = 998244353;
    FOR(i,0,m-1){
        int k;scanf("%d",&k);
        while(k--){
            int x;scanf("%d",&x);--x;
            small[1<<i] |= (1<<x);
            big[1<<x] |= (1<<i);
        }
        scanf("%d",&k);
        while(k--){
            int x;scanf("%d",&x);--x;
            small[1<<x] |= (1<<i);
            big[1<<i] |= (1<<x);
        }
    }
    FOR(S,0,(1<<m)-1){
        FOR(i,0,m-1){
            if((S>>i)&1){
                small[S] |= small[S^(1<<i)];
                big[S] |= big[S^(1<<i)];
            }
        }
    }
    f[0][0] = 1;
    FOR(i,0,m-1){
        FOR(S,0,(1<<m)-1){
            if(!f[i][S]) continue;
            int s = ((1<<m)-1)^S;
            for(int T = s;T;T = (T-1)&s){
                if(((big[T]&S) == 0)){
                    add(f[i+1][S^T],f[i][S]);
                }
            }
        }
    }
    int ans = 0;
//    DEBUG(f[1][1]);
//    DEBUG(f[2][1|(1<<3)]);
    FOR(i,1,m) (ans += 1ll*C(n,i)*f[i][(1<<m)-1]%ha) %= ha;
    printf("%d\n",ans);
    return 0;
}