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

const int MAXN = 2000+5;
int g1[MAXN][MAXN],g2[MAXN][MAXN],f[MAXN][MAXN];
int n,m,k;
int a[MAXN][MAXN];
int pre[MAXN],suf[MAXN];
int sm[MAXN][MAXN];

inline void init(int f[],int g[]){
    pre[0] = suf[m+1] = 1e9;
    FOR(i,1,m) pre[i] = std::min(pre[i-1],f[i]);
    ROF(i,m,1) suf[i] = std::min(suf[i+1],f[i]);
    FOR(i,1,m) g[i] = std::min(pre[i-1],suf[i+1]);
}

int h[MAXN];

int main(){
    read(n);read(m);read(k);
    FOR(i,1,n) FOR(j,1,m) read(a[i][j]);
    FOR(i,1,m) FOR(j,1,n) sm[i][j] = sm[i][j-1]+a[j][i];
    FOR(i,1,m) f[1][i] = a[1][i];
    init(f[1],g1[1]);
    FOR(i,2,n){
        FOR(j,1,m){
            f[i][j] = g1[i-1][j]+a[i][j];
        }
        init(f[i],g1[i]);
    }
    FOR(i,1,m) f[n][i] = a[n][i];
    init(f[n],g2[n]);
    ROF(i,n-1,1){
        FOR(j,1,m){
            f[i][j] = g2[i+1][j]+a[i][j];
        }
        init(f[i],g2[i]);
    }
    // 选择区间[l,r]涂成 颜色 v
    // sm[v][r]+g2[r+1][v] +g1[l-1][v]-sm[v][l-1]
    // h1[i] = min_v g1[i][v]-sm[v][i]
    // h2[i] = min_v sm[v][i]+g2[i+1][v]
    // h1[i-1]+h2[i]
    int ans = 1e9;
    FOR(v,1,m){
        //h2[n+1] = 1e9;
        std::deque<int> q;
        FOR(i,1,n) h[i] = g2[i+1][v]+sm[v][i];
        ROF(l,n,1){
            // sm[v][r]+g2[r+1][v]+g1[l-1][v]-sm[v][l-1]
            while(!q.empty() && q[0]-l+1 > k) q.pop_front();
            while(!q.empty() && h[q.back()] >= h[l]) q.pop_back();
            q.pb(l);
            ans = std::min(ans,h[q.front()]+g1[l-1][v]-sm[v][l-1]);
        }
    }
    printf("%d\n",ans);
    return 0;
}