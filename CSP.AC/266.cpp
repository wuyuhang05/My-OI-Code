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

const int MAXN = 1e6 + 5;
int n,m,k;
int x[MAXN],y[MAXN],z[MAXN];
bool vis[2][MAXN];

int main(){
//    freopen("B.in","r",stdin);
//    freopen("B.out","w",stdout);
    read(n);read(m);read(k);
    FOR(i,1,k) read(x[i]),read(y[i]),read(z[i]);
    int row=0,col=0;LL ans = 0;
    ROF(i,k,1){
        if(vis[x[i]][y[i]]) continue;
        vis[x[i]][y[i]] = 1;
        if(x[i] == 0) ans += z[i]*std::max(0,m-col),++row;
        else ans += z[i]*std::max(0,n-row),++col;
    }
    printf("%lld\n",ans);
    return 0;
}