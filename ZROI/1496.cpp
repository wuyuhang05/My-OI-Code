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
#define db double
#define U unsigned
#define P std::pair<int,int>
#define LL long long
#define pb push_back
#define MP std::make_pair
#define all(x) x.begin(),x.end()
#define CLR(i,a) memset(i,a,sizeof(i))
#define FOR(i,a,b) for(register int i = a;i <= b;++i)
#define ROF(i,a,b) for(register int i = a;i >= b;--i)
#define DEBUG(x) std::cerr << #x << '=' << x << std::endl

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

const int MAXN = 2e5 + 5;
const int MAXM = 17;
const LL ha = 3311451419260817ll;
int n,a[MAXN];
LL b[MAXN],sm[MAXN];
int pc[MAXN],mx[MAXM+1][MAXN];

inline LL mul(LL x,LL y){
    LL res = x*y-(LL)((long double)x*y/ha+0.5)*ha;
    return res<0?res+ha:res;
}

inline void mod(LL &x){
    if(x >= ha) x -= ha;
}

inline LL qpow(LL a,int n){
    LL res = 1;
    while(n){
        if(n & 1) res = mul(res,a);
        a = mul(a,a);
        n >>= 1;
    }
    return res;
}

inline int query(int l,int r){
    int c = pc[r-l+1];
    return a[mx[c][l]] > a[mx[c][r-(1<<c)+1]] ? mx[c][l] : mx[c][r-(1<<c)+1];
}

struct H{
    const int M = 19260817;
    struct Edge{
        LL key;int val,nxt;
    }e[MAXN];
    int head[19260817],cnt;
    inline void insert(LL key,int val){
        int ps = key%M;
        e[++cnt] = (Edge){key,val,head[ps]};head[ps] = cnt;
    }
    inline int query(LL key){
        int ps = key%M;
        for(int i = head[ps];i;i = e[i].nxt){
            if(e[i].key == key) return e[i].val;
        }
        return -1;
    }
}S;

int ans = 0;

inline void work(int l,int r){
    if(l == r) ans++;if(l >= r) return;
    int mid = query(l,r);
    if(mid-l <= r-mid){
        ROF(i,mid,l){
            LL t = b[mid];
            FOR(k,0,pc[r-l+1]){
                LL w = t+sm[i-1];mod(w);
                int p = S.query(w);
                if(mid <= p && p <= r) ans++;
                t = t+t;mod(t);
            }
        }
    }
    else{
        FOR(i,mid,r){
            LL t = b[mid];
            FOR(k,0,pc[r-l+1]){
                LL w = sm[i]+ha-t;mod(w);
                int p = S.query(w)+1;
                if(l <= p && p <= mid) ans++;
                t = t+t;mod(t);
            }
        }
    }
    work(l,mid-1);work(mid+1,r);
}

int main(){
//    srand(123123);
    pc[0] = -1;FOR(i,1,MAXN-1) pc[i] = pc[i>>1]+1;
    read(n);
    S.insert(0,0);
    FOR(i,1,n) read(a[i]),mx[0][i] = i,b[i] = qpow(2,a[i]),sm[i] = sm[i-1]+b[i],mod(sm[i]);
    FOR(i,1,n) S.insert(sm[i],i);
    FOR(i,1,MAXM){
        for(int j = 0;j+(1<<(i-1))<MAXN;++j){
            mx[i][j] = a[mx[i-1][j]] > a[mx[i-1][j+(1<<(i-1))]] ? mx[i-1][j] : mx[i-1][j+(1<<(i-1))];
        }
    }
    work(1,n);
    printf("%d\n",ans);
    return 0;
}

