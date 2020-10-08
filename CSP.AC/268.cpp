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

const int MAXN = 2000+5;
LL f[MAXN][MAXN],sma[MAXN],smb[MAXN];
int n,m,a[MAXN],b[MAXN];

inline void upmin(LL &x,LL y){
    if(x > y) x = y;
}

struct BIT{
    #define lowbit(x) ((x)&(-(x)))
    LL tree[MAXN];

    inline void add(int pos,LL x){
        ++pos;
        while(pos < MAXN){
            tree[pos] = std::min(tree[pos],x);
            pos += lowbit(pos);
        }
    }

    inline LL qry(int pos){
        LL res = 1e18;++pos;
        while(pos){
            res = std::min(res,tree[pos]);
            pos -= lowbit(pos);
        }
        return res;
    }
}mn1[MAXN],mn2[MAXN];

int main(){
    scanf("%d%d",&n,&m);
    FOR(i,1,n) scanf("%d",a+i),sma[i] = sma[i-1]+a[i];
    FOR(i,1,m) scanf("%d",b+i),smb[i] = smb[i-1]+b[i];
    FOR(i,1,m) smb[i] -= i;
    FOR(i,1,n) sma[i] -= i;
    FOR(i,1,n) a[i]--;FOR(i,1,m) b[i]--;
    CLR(f,0x3f);f[0][0] = 0;
    CLR(mn1,0x3f);CLR(mn2,0x3f);
    mn1[0].add(0,f[0][0]+sma[0]*b[1]);
    mn2[0].add(0,f[0][0]+smb[0]*a[1]);
    FOR(i,1,n){
        FOR(j,1,m){
            upmin(f[i][j],mn1[j-1].qry(i-1)+sma[i]*b[j]);
            upmin(f[i][j],mn2[i-1].qry(j-1)+smb[j]*a[i]);
            mn1[j].add(i,f[i][j]-sma[i]*b[j+1]);
            mn2[i].add(j,f[i][j]-smb[j]*a[i+1]);
            //FOR(k,0,i-1) upmin(f[i][j],f[k][j-1]+sma[i]b[j]-sma[k]b[j]);
            //FOR(k,0,j-1) upmin(f[i][j],f[i-1][k]+smb[j]a[i]-smb[k]a[i]);
        }
    }
    printf("%lld\n",f[n][m]);
    return 0;
}
