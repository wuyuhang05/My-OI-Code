#pragma GCC optimize("Ofast")
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

const int MAXN = 40000+5;
const int EPS = 1e-9;

inline int sgn(double x){
    if(std::fabs(x) <= EPS) return 0;
    if(x < 0) return -1;
    return 1;
}

int n;
int aa[MAXN],bb[MAXN],cc[MAXN];
std::pair<double,double> seg[MAXN];
double a[MAXN];
int c[MAXN];

struct BIT{
    int tree[MAXN];
    #define lowbit(x) ((x)&(-(x)))

    inline void add(int pos,int x){
        while(pos < MAXN){
            tree[pos] += x;
            pos += lowbit(pos);
        }
    }

    inline int query(int pos){
        int res = 0;
        while(pos){
            res += tree[pos];
            pos -= lowbit(pos);
        }
        return res;
    }
}bit;

inline bool chk(double x){ // <=x 的交点个数是否超过一半
    LL ans = 0;
    std::sort(seg+1,seg+n+1);
    FOR(i,1,n) a[i] = seg[i].se+x*seg[i].fi;
    std::vector<double> S;
    FOR(i,1,n) S.pb(a[i]);
    std::sort(all(S));S.erase(std::unique(all(S)),S.end());
    FOR(i,1,n) c[i] = std::lower_bound(all(S),a[i])-S.begin()+1;
    CLR(bit.tree,0);
    FOR(i,1,n){
        ans += bit.query(c[i]);
        bit.add(c[i],1);
    }
    LL lim = 1ll*n*(n-1)/2;
//    DEBUG(ans);
    return ans >= lim - ans;
}

inline double work(){
    std::sort(seg+1,seg+n+1);
    double l = -1e9,r = 1e9,ans=0;
    FOR(i,1,70){
        double mid = (l + r)/2.0;
        if(chk(mid)) ans = mid,r = mid;
        else l = mid;
    }
    return ans;
}

int main(){
    scanf("%d",&n);
    FOR(i,1,n){
        scanf("%d%d%d",aa+i,bb+i,cc+i);
        seg[i] = MP(-1.0*(1.0*aa[i]/bb[i]),1.0*cc[i]/bb[i]);
    }
    printf("%.6f ",work());
    FOR(i,1,n){
        seg[i] = MP(-1.0*(1.0*bb[i]/aa[i]),1.0*cc[i]/aa[i]);
    }
 //   DEBUG(chk(-4905.877264));
 //   exit(0);
    printf("%.6f\n",work());
    return 0;
}
