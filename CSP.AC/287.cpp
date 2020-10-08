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

const int MAXN = 5e5 + 5;
const int ha = 998244353;
const int inv2 = 499122177;

inline void add(int &x,int y){
    x += y;if(x >= ha) x -= ha;
}

int a[MAXN],b[MAXN];

inline char nc(){
    #define SIZE 1000000+3
    static char buf[SIZE],*p1 = buf+SIZE,*p2 = buf+SIZE;
    if(p1 == p2){
        p1 = buf;p2 = buf+fread(buf,1,SIZE,stdin);
        if(p1 == p2) return -1;
    }
    return *p1++;
    #undef SIZE
}

template <typename T>
inline void read(T &x){
    x = 0;int flag = 0;char ch = nc();
    while(!isdigit(ch)){
        if(ch == '-') flag = 1;
        ch = nc();
    }
    while(isdigit(ch)){
        x = (x<<1) + (x<<3) + (ch^'0');
        ch = nc();
    }
    if(flag) x = -x;
}

struct BIT{
    #define lowbit(x) ((x)&(-(x)))
    int tree[MAXN];

    inline void add(int pos,int x){
        while(pos < MAXN){
            ::add(tree[pos],x);
            pos += lowbit(pos);
        }
    }

    inline int calc(int pos){
        if(!pos) return 0;
        int res = 0;
        while(pos){
            ::add(res,tree[pos]);
            pos -= lowbit(pos);
        }
        return res;
    }

    inline int query(int l,int r){
        return (calc(r)+ha-calc(l-1))%ha;
    }
}bit1,bit2,bit3;

int n,q;

int main(){
//    freopen("C.in","r",stdin);
//    freopen("C.out","w",stdout);
    read(n);read(q);
    FOR(i,1,n) read(a[i]),bit1.add(i,1ll*a[i]*a[i]%ha);
    FOR(i,1,n) read(b[i]),bit2.add(i,1ll*b[i]*b[i]%ha);
    FOR(i,1,n) bit3.add(i,1ll*a[i]*b[i]%ha);
    FOR(i,1,q){
        int opt;read(opt);
        if(opt == 1){
            int l,r;read(l);read(r);
            int a = bit1.query(l,r),b = bit2.query(l,r),c = bit3.query(l,r);
            int res = (1ll*a*b%ha+ha-1ll*c*c%ha)%ha;
            printf("%d\n",res);
        }
        else{
            int p;read(p);
            bit1.add(p,ha-1ll*a[p]*a[p]%ha);
            bit2.add(p,ha-1ll*b[p]*b[p]%ha);
            bit3.add(p,ha-1ll*a[p]*b[p]%ha);
            read(a[p]);read(b[p]);
            bit1.add(p,1ll*a[p]*a[p]%ha);
            bit2.add(p,1ll*b[p]*b[p]%ha);
            bit3.add(p,1ll*a[p]*b[p]%ha);
        }
    }
    return 0;
}
