// f[i][j] = f[i][root]*f[root+1][j]
#include <algorithm>
#include <iostream>
#include <cstring>
#include <climits>
#include <cstdio>
#include <vector>
#include <cstdlib>
#include <ctime>
#include <cmath>
#include <queue>
#include <stack>
#include <map>
#include <set>
#define Re register
#define LL long long
#define U unsigned
#define FOR(i,a,b) for(Re int i = a;i <= b;++i)
#define ROF(i,a,b) for(Re int i = a;i >= b;--i)
#define SFOR(i,a,b,c) for(Re int i = a;i <= b;i+=c)
#define SROF(i,a,b,c) for(Re int i = a;i >= b;i-=c)
#define CLR(i,a) memset(i,a,sizeof(i))
#define BR printf("--------------------\n")
#define DEBUG(x) std::cerr << #x << '=' << x << std::endl
namespace fastIO{
    #define BUF_SIZE 100000
    #define OUT_SIZE 100000
    #define ll long long
    bool IOerror=0;
    inline char nc(){
        static char buf[BUF_SIZE],*p1=buf+BUF_SIZE,*pend=buf+BUF_SIZE;
        if (p1==pend){
            p1=buf; pend=buf+fread(buf,1,BUF_SIZE,stdin);
            if (pend==p1){IOerror=1;return -1;}
        }
        return *p1++;
    }
    inline bool blank(char ch){return ch==' '||ch=='\n'||ch=='\r'||ch=='\t';}
    inline void read(int &x){
        bool sign=0; char ch=nc(); x=0;
        for (;blank(ch);ch=nc());
        if (IOerror)return;
        if (ch=='-')sign=1,ch=nc();
        for (;ch>='0'&&ch<='9';ch=nc())x=x*10+ch-'0';
        if (sign)x=-x;
    }
    inline void read(ll &x){
        bool sign=0; char ch=nc(); x=0;
        for (;blank(ch);ch=nc());
        if (IOerror)return;
        if (ch=='-')sign=1,ch=nc();
        for (;ch>='0'&&ch<='9';ch=nc())x=x*10+ch-'0';
        if (sign)x=-x;
    }
    #undef ll
    #undef OUT_SIZE
    #undef BUF_SIZE
};
using namespace fastIO;
#define int LL
const int MAXN = 400+5;
const int ha = 1000000000+7;
int f[MAXN][MAXN];
int N,M;
int a[MAXN][MAXN];
int s[MAXN][MAXN];

inline int calc(int a,int b,int c,int d){ // 如果返回非0，说明[a,c]中的一个点 < [b,d]中的一个点
    return s[c][d]-s[a-1][d]-s[c][b-1]+s[a-1][b-1];
}

inline bool pd(int i,int xa,int xb,int ya,int yb){ // i,i+1,k,k+1,j
    if(calc(ya,xa,yb,xb)) return false; // [k+1,j] < [i+1,k],即左子树的中序遍历 < 右子树的中序遍历?
    if(calc(ya,i,yb,i)) return false; // [k+1,j] < i?,即特判左端点中序遍历 < 右子树中序遍历?
    if(calc(i,xa,i,xb)) return false; // i < [i+1,k]?,特判左端点中序遍历 < 左子树中序遍历?
    return true; // 上面的不满足均合法可以转移
}

inline void add(int &a,int b){
    a += b;
    if(a > ha) a -= ha;
}

inline void Solve(){
    read(N);read(M);
    CLR(f,0);CLR(a,0);CLR(s,0);
    FOR(i,1,M){
        int u,v;read(u);read(v);
        a[u][v] = 1;
    }
    FOR(i,1,N) FOR(j,1,N) s[i][j] = s[i-1][j]+s[i][j-1]-s[i-1][j-1]+a[i][j];
    FOR(i,1,N) f[i][i] = 1;
    FOR(l,1,N){
        FOR(i,1,N){
            if(i+l > N) break;
            int j = i+l;
            // i as root
            if(!calc(i,i+1,i,j)) add(f[i][j],f[i+1][j]);
            if(!calc(i+1,i,j,i)) add(f[i][j],f[i+1][j]);
            // root as root
            FOR(root,i+1,j-1){
                if(pd(i,i+1,root,root+1,j)) add(f[i][j],(f[i+1][root]*f[root+1][j])%ha);
            }
        }
    }
    printf("%lld\n",f[1][N]%ha);
}

signed main(){
    int T;read(T);
    while(T--) Solve();
    // system("pause");
    return 0;
}
/*
5
10 22
3 6
7 9
5 9
8 10
4 8
7 8
7 10
3 7
1 5
3 5
9 10
8 9
2 6
4 6
7 10
6 7
4 7
1 5
3 9
4 8
3 7
6 10
10 24
1 9
1 7
5 7
3 10
6 9
2 4
2 7
1 7
4 10
2 7
1 4
6 9
1 9
10 8
10 8
6 8
3 6
6 8
1 8
1 3
4 9
1 6
9 8
4 7
10 28
5 10
6 7
2 8
7 9
5 8
6 9
3 4
4 9
3 2
3 4
6 10
5 8
3 8
7 10
7 10
2 6
8 7
7 9
5 7
6 1
2 6
5 8
1 8
2 9
2 10
3 7
6 10
6 10
10 22
4 5
4 7
10 9
1 10
2 1
5 10
4 9
5 10
5 8
5 8
3 2
5 7
3 6
5 8
2 8
4 10
7 9
5 9
6 8
10 9
4 10
2 5
10 2
1 5
6 2
Ans:
64
116
18
98
2529
*/