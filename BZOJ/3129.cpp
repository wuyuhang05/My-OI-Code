#include <iostream>
#include <cstring>
#include <cstdio>
#include <cmath>
#define DEBUG(x) std::cerr << #x << '=' << x << std::endl

#define LL long long

const int MAXN = 100000 + 5;

LL n,n1,n2,m,T;
LL ha,ans;
LL data[MAXN],tot;
LL fac[MAXN];
LL a[MAXN],b[MAXN],c[MAXN],d[MAXN],prime[MAXN];

inline void pre(){
    LL k = sqrt(ha) + 1;
    LL x = ha;
    // DEBUG(k);
    for(int i = 2;i <= k;i++){
        if(!(x%i)){
            int cnt = 0;
            d[++tot] = 1;
            prime[tot] = i;
            while(!(x%i)){
                ++cnt;
                x/=i;
                d[tot] *= i;
            }
        }
    }
    if(x != 1){
        d[++tot] = x;
        prime[tot] = x;
    }
    for(int i = 1;i <= tot;i++){
        c[i] = ha / d[i];
    }
}

LL qpow(LL a,LL n,LL p){
    LL ret = 1;
    while(n){
        if(n&1) ret = (ret * a) % p;
        a = (a * a) % p;
        n >>= 1;
    }
    return ret % p;
}

LL exgcd(LL a,LL b,LL &x,LL &y){
    if(!b){
        x = 1;
        y = 0;
        return a;
    }
    LL d = exgcd(b,a%b,x,y);
    LL t = x;x = y;
    y = t - (a/b) * y;
    return d;
}

LL rev(LL a,LL p){
    LL x,y;
    exgcd(a,p,x,y);
    return (x%p + p) % p;
}

LL qfac(LL n,LL p,LL t){ // n!%p^t
    if(n < t) return fac[n];
    LL s = qpow(fac[p-1],n/p,p);
    s = s * fac[n%p] % p;
    return s = s * qfac(n/t,p,t) % p;
}

LL exLucas(LL n,LL m,LL p,LL t){
    LL ap=0,bp=0,cp=0;
    fac[0] = 1;
    for(int i = 1;i < p;i++){
        if(!(i%t))
            fac[i] = fac[i-1];
        else fac[i] = (fac[i-1] * i) % p;
    }
    for(LL i = m;i;i/=t)
        ap += i/t;
    for(LL i = n;i;i /= t)
        bp += i/t;
    for(LL i = m-n;i;i/=t)
        cp += i/t;
    ap -= bp+cp;
    LL ret = qpow(t,ap,p);
    ap = qfac(m,p,t);bp = qfac(n,p,t);cp = qfac(m-n,p,t);
    return ret = (((ret * ap % p)*rev(bp,p)%p)*rev(cp,p)%p)%p;
}

LL C(LL n,LL m,LL p){
    if(n > m) return 0ll;
    for(int i = 1;i <= tot;i++)
        b[i] = exLucas(n,m,d[i],prime[i]);
    for(int i = 1;i <= tot;i++)
        a[i] = rev(c[i],d[i]);
    LL ret = 0ll;
    for(int i = 1;i <= tot;i++)
        ret = (ret + (a[i]*b[i]%p)*c[i]%p) % p;
    return ret;
}

void dfs(LL step,LL m,LL cnt){
    // DEBUG(step);
    if(step > n1){
        ans = (ans + C(n-1,m-1,ha)*cnt + ha) % ha;
        return;
    }
    dfs(step + 1,m,cnt);
    if(m >= data[step]) dfs(step + 1,m-data[step],-cnt);
}

int main(){
    scanf("%lld%lld",&T,&ha);
    pre();
    while(T--){
        scanf("%lld%lld%lld%lld",&n,&n1,&n2,&m);
        for(int i = 1;i <= n1;i++)
            scanf("%lld",data+i);
        for(int i = 1;i <= n2;i++){
            LL x;
            scanf("%lld",&x);
            if(x) m -= x-1;
        }
        if(m < n1) puts("0");
        else{
            ans = 0;
            dfs(1,m,1);
            printf("%lld\n",ans);
        }
        
    }
    
    return 0;
}

