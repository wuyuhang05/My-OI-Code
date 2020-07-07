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
#define FOR(i,a,b) for(int i = a;i <= b;++i)
#define ROF(i,a,b) for(int i = a;i >= b;--i)
#define DEBUG(x) std::cerr << #x << '=' << x << std::endl
int n;

struct Node{
    int a,b,c,d;
    Node(int a=0,int b=0,int c=0,int d=0) : a(a),b(b),c(c),d(d) {}

    bool operator < (const Node &t) const {
        if(a != t.a) return a < t.a;
        if(b != t.b) return b < t.b;
        if(c != t.c) return c < t.c;
        return d < t.d;
    }
};
const int MAXN = 64 + 5;
const int BLO = 12;
int a[MAXN][MAXN];
std::map<Node,int> S;
int score;
inline int query(int xl,int xr,int yl,int yr){
    xl = std::max(xl,1);xr = std::min(xr,n);
    yl = std::max(yl,1);yr = std::min(yr,n);
    if(xl > xr || yl > yr) return 0;
   // int t = a[xr][yr]-a[xr][yl-1]-a[xl-1][yr]+a[xl-1][yl-1];
    if(S.count(Node(xl,xr,yl,yr))) return S[Node(xl,xr,yl,yr)];
   // int a = xr-xl+1,b = yr-yl+1;
   // score += std::ceil(1.0*(2*n-a)*(2*n-b)/(1+t));
   // return S[Node(xl,xr,yl,yr)] = t;
    printf("1 %d %d %d %d\n",xl,yl,xr,yr);std::fflush(stdout);
    int x;scanf("%d",&x);return S[Node(xl,xr,yl,yr)] = x;
}
int ans[MAXN][MAXN];

inline void work(int xl,int xr,int yl,int yr,int sm){
    if(sm == 0) return;
    if(sm == (xr-xl+1)*(yr-yl+1)){
        FOR(i,xl,xr) FOR(j,yl,yr) ans[i+1][j+1] = 1;
        return;
    }
    if(xl == xr && yl == yr){
        ans[xl+1][xr+1] = sm;return;
    }
    if(xr-xl < yr-yl){
        int mid = (yr+yl)>>1;
        int t = query(xl+1,xr+1,yl+1,mid+1);
        work(xl,xr,yl,mid,t);work(xl,xr,mid+1,yr,sm-t);
    }
    else{
        int mid = (xl+xr)>>1;
        int t = query(xl+1,mid+1,yl+1,yr+1);
        work(xl,mid,yl,yr,t);work(mid+1,xr,yl,yr,sm-t);
    }
}

int p;
#include<bits/stdc++.h>
std::mt19937 g(23334);
inline int gen(){
    if(1+g()%100 <= p) return 1;
    return 0;
}
bool ua[MAXN],ub[MAXN];
bool uu[MAXN][MAXN];
inline void Solve(){
    S.clear();score = 0;
    scanf("%d%d",&n,&p);CLR(ans,0);
 //   n = 60;p = 10;
    FOR(i,1,n) FOR(j,1,n) a[i][j] = gen();//scanf("%d",&a[i][j]);
    FOR(i,1,n) FOR(j,1,n) a[i][j] += a[i-1][j]+a[i][j-1]-a[i-1][j-1];
    CLR(ua,0);CLR(ub,0);CLR(uu,0);
    if(p == 1){
        FOR(i,1,n){
            if(query(1,i,1,n)-query(1,i-1,1,n) == 0) ua[i] = 1;
            if(query(1,n,1,i)-query(1,n,1,i-1) == 0) ub[i] = 1;
        }
    }
    else{
        FOR(i,n/2+1,n){
            if(query(1,i,1,n)-query(1,i-1,1,n) == 0) ua[i] = 1;
            if(query(1,n,1,i)-query(1,n,1,i-1) == 0) ub[i] = 1;
        }
    }
    if(p != 2){
        for(int i = 2;i <= 60;i += 2){
            for(int j = 2;j <= 60;j += 2){
                int xl = i-2+1,xr = i,yl = j-2+1,yr = j,t;
                if(i <= 30 && j <= 30){
                    t = query(xl,n,yl,n)-query(xr+1,n,yl,n)-query(xl,n,yr+1,n)+query(xr+1,n,yr+1,n);
                }
                else if(i > 30 && j <= 30){
                    t = query(1,xr,yl,n)-query(1,xl-1,yl,n)-query(1,xr,yr+1,n)+query(1,xl-1,yr+1,n);
                }
                else if(i <= 30 && j > 30){
                    t = query(xl,n,1,yr)-query(xr+1,n,1,yr)-query(xl,n,1,yl-1)+query(xr+1,n,1,yl-1);
                }
                else{
                    t = query(1,xr,1,yr)-query(1,xl-1,1,yr)-query(1,xr,1,yl-1)+query(1,xl-1,1,yl-1);
                }
                if(!t) FOR(x,xl,xr) FOR(y,yl,yr) uu[x][y] = 1;
                if(t == 4){
                    FOR(x,xl,xr) FOR(y,yl,yr) ans[x][y] = 1;
                }
            }
        }
    }
    if(p == 2){
        for(int i = 3;i <= 60;i += 3){
            for(int j = 3;j <= 60;j += 3){
                int xl = i-3+1,xr = i,yl = j-3+1,yr = j,t;
                if(i <= 30 && j <= 30){
                    t = query(xl,n,yl,n)-query(xr+1,n,yl,n)-query(xl,n,yr+1,n)+query(xr+1,n,yr+1,n);
                }
                else if(i > 30 && j <= 30){
                    t = query(1,xr,yl,n)-query(1,xl-1,yl,n)-query(1,xr,yr+1,n)+query(1,xl-1,yr+1,n);
                }
                else if(i <= 30 && j > 30){
                    t = query(xl,n,1,yr)-query(xr+1,n,1,yr)-query(xl,n,1,yl-1)+query(xr+1,n,1,yl-1);
                }
                else{
                    t = query(1,xr,1,yr)-query(1,xl-1,1,yr)-query(1,xr,1,yl-1)+query(1,xl-1,1,yl-1);
                }
                if(!t) FOR(x,xl,xr) FOR(y,yl,yr) uu[x][y] = 1;
                if(t == 9){
                    FOR(x,xl,xr) FOR(y,yl,yr) ans[x][y] = 1;
                }
            }
        }
    }
    FOR(i,1,n){
        if(ua[i]) continue;
        FOR(j,1,n){
            if(ub[j]) continue;
            if(uu[i][j]) continue;
            if(ans[i][j]) continue;
            if(i >= n-i+1 && j >= n-i+1){
                ans[i][j] = query(1,i,1,j)-query(1,i-1,1,j)-query(1,i,1,j-1)+query(1,i-1,1,j-1);
            }
            else if(i >= n-i+1 && j < n-i+1){
                ans[i][j] = query(1,i,j,n)-query(1,i-1,j,n)-query(1,i,j+1,n)+query(1,i-1,j+1,n);
            }
            else if(i < n-i+1 && j >= n-i+1){
                ans[i][j] = query(i,n,1,j)-query(i+1,n,1,j)-query(i,n,1,j-1)+query(i+1,n,1,j-1);
            }
            else{
                ans[i][j] = query(i,n,j,n)-query(i+1,n,j,n)-query(i,n,j+1,n)+query(i+1,n,j+1,n);
            }
        }
    }
//    DEBUG(score);
   // exit(0);
    puts("2");
//    FOR(i,1,n) FOR(j,1,n) assert(ans[i][j] == a[i][j]-a[i-1][j]-a[i][j-1]+a[i-1][j-1]);
  //  exit(0);
    FOR(i,1,n) FOR(j,1,n) printf("%d%c",ans[i][j]," \n"[j==n]);
    std::fflush(stdout);int x;scanf("%d",&x);
    if(x == -1) exit(-1);
}

int main(){
    int T;scanf("%d",&T);
  //  int T = 1;
    while(T--) Solve();
    return 0;
}



