#include <algorithm>
#include <iostream>
#include <cstring>
#include <climits>
#include <cstdlib>
#include <cstdio>
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
#define Re register
#define LL long long
#define pb push_back
#define ld long double
#define MP std::make_pair
#define all(x) x.begin(),x.end()
#define CLR(i,a) memset(i,a,sizeof(i))
#define FOR(i,a,b) for(Re int i = a;i <= b;++i)
#define ROF(i,a,b) for(Re int i = a;i >= b;--i)
#define DEBUG(x) std::cerr << #x << '=' << x << std::endl

const double PI = acos(-1);
const int MAXN = 300000+5;

int N,M;

struct cp{
    ld x,y;
    cp(ld x=0,ld y=0) : x(x), y(y) {}
    cp operator + (const cp &t) const {
        return cp(x+t.x,y+t.y);
    }
    cp operator - (const cp &t) const {
        return cp(x-t.x,y-t.y);
    }
    cp operator * (const cp &t) const {
        return cp(x*t.x-y*t.y,x*t.y+y*t.x);
    }
    LL D(){
        LL t = (x+0.499);
        return t;
    }
}w[1<<17][101];
int r[MAXN];
const int haha = 32768;
int ha;

inline void init(){
    for(int i = 2,j = 0;j < 17;j++,i <<= 1){
        FOR(k,0,i-1) w[k][j] = cp(cos(2*PI*k/i),sin(2*PI*k/i));
    }
}

inline void FFT(cp *A,int limit,int opt){
    FOR(i,0,limit) if(i < r[i]) std::swap(A[i],A[r[i]]);
    for(int mid = 1,i = 0;mid < limit;mid <<= 1,++i){
        for(int j = 0;j < limit;j += (mid<<1)){
            for(int k = 0;k < mid;++k){
                cp w = ::w[k][i];if(opt == -1) w.y = -w.y;
                cp x = A[j+k],y = w*A[j+mid+k];
                A[j+k] = x+y,A[j+mid+k] = x-y;
            }
        }
    }
    if(opt == -1){
        FOR(i,0,limit-1) A[i].x = A[i].x/limit;
    }
}

struct Poly{
    LL a[MAXN];
    Poly(){
        CLR(a,0);
    }
    friend Poly operator * (const Poly &a,const Poly &b){
        Poly ans;
        static cp A[MAXN],B[MAXN],C[MAXN],D[MAXN],E[MAXN],F[MAXN],G[MAXN];
        CLR(A,0);CLR(B,0);CLR(C,0);CLR(D,0);
        FOR(i,0,N-1) A[i].x = a.a[i]%haha,B[i].x = a.a[i]/haha;
        FOR(i,0,N-1) C[i].x = b.a[i]%haha,D[i].x = b.a[i]/haha;
        FFT(A,N,1);FFT(B,N,1);FFT(C,N,1);FFT(D,N,1);
        FOR(i,1,N){
            E[i] = A[i]*B[i];
            F[i] = A[i]*D[i]+B[i]*C[i];
            G[i] = B[i]*D[i];
        }
        FFT(E,N,-1);FFT(F,N,-1);FFT(G,N,-1);
        FOR(i,0,N-1) ans.a[i] = 1ll*(E[i].D()%ha+F[i].D()%ha*haha%ha+G[i].D()%ha*haha%ha*haha%ha)%ha;
        return ans;
    }
}A,B;

int main(){
    init();
    scanf("%d%d%d",&N,&M,&ha);
    FOR(i,0,n) scanf("%lld",&A.a[i]);
    FOR(i,0,m) scanf("%lld",&B.a[i]);
    Poly ans = A*B;
    FOR(i,0,n+m) printf("%lld ",ans.a[i]);
    return 0;
}
