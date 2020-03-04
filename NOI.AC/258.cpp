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
#define U unsigned
#define P std::pair
#define LL long long
#define pb push_back
#define MP std::make_pair
#define all(x) x.begin(),x.end()
#define CLR(i,a) memset(i,a,sizeof(i))
#define FOR(i,a,b) for(int i = a;i <= b;++i)
#define ROF(i,a,b) for(int i = a;i >= b;--i)
#define DEBUG(x) std::cerr << #x << '=' << x << std::endl

const int MAXN = 2e5 + 5;
int n,m,Q,ha,C1,C2;
std::map<LL,LL> S;

struct Matrix{
    int a[2][2];

    inline Matrix operator * (const Matrix &t) const {
        Matrix res;CLR(res.a,0);
        FOR(i,0,1){
            FOR(j,0,1){
                FOR(k,0,1){
                    (res.a[i][j] += 1ll*a[i][k]*t.a[k][j]%ha)%= ha;
                }
            }
        }
        return res;
    }
}base,A1[MAXN],A2[MAXN];

inline Matrix qpow(Matrix a,LL n){
    return A2[n/m]*A1[n%m];
    // Matrix res;CLR(res.a,0);res.a[0][0] = res.a[1][1] = 1;
    // while(n){
    //     if(n & 1) res = res*a;
    //     a = a*a;
    //     n >>= 1;
    // }
    // return res;
}

inline int f(LL n){
    if(n == 0) return C1;
    if(n == 1) return C2;
    if(n == -1) return (C2+ha-C1)%ha;
    Matrix res = qpow(base,n-1);
    // DEBUG(n-1);FOR(i,0,1) FOR(j,0,1) printf("%d ",res.a[i][j]);puts("");
    return (1ll*C2*res.a[0][0]%ha+1ll*C1*res.a[1][0]%ha)%ha;
}

inline int A(int x,int y){
    LL id = 1ll*(x-1)*m+y;
    if(S.count(id)) id = S[id];
    return (1ll*f(id+1)*f(id)%ha+ha-1ll*f(0)*f(-1)%ha)%ha;
}

int main(){
    base.a[0][0] = base.a[0][1] = base.a[1][0] = 1;base.a[1][1] = 0;
    scanf("%d%d%d%d%d%d",&n,&m,&Q,&ha,&C1,&C2);
    A1[0].a[0][0] = A1[0].a[1][1] = 1;A1[0].a[1][0] = A1[0].a[0][1] = 0;
    FOR(i,1,m) A1[i] = A1[i-1]*base;
    A2[0].a[0][0] = A2[0].a[1][1] = 1;A2[0].a[1][0] = A2[0].a[0][1] = 0;
    A2[1] = A1[m];
    FOR(i,2,n+1) A2[i] = A2[i-1]*A2[1];
    // FOR(i,1,10) DEBUG(f(i));
    FOR(i,1,Q){
        LL x,y;scanf("%lld%lld",&x,&y);
        if(!S.count(x)) S[x] = x;
        if(!S.count(y)) S[y] = y;
        std::swap(S[x],S[y]);
    }
    int x=1,y=1;
    FOR(i,1,n+m-1){
        // DEBUG(i);
        printf("%d ",A(x,y));
        if(x == n) y++;
        else if(y == m) x++;
        else{
            int t1 = A(x+1,y),t2 = A(x,y+1);
            if(t1 <= t2) x++;
            else y++;
        } 
    }puts("");
    return 0;
}