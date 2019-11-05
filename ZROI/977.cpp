/*
 * Author: RainAir
 * Time: 2019-11-03 20:52:03
 */
#include <algorithm>
#include <iostream>
#include <assert.h>
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

const int MAXN = 1000+5;
int a[MAXN][MAXN];
int n,m;
int cf[MAXN][MAXN],cfl[MAXN][MAXN],cfr[MAXN][MAXN];
std::vector<P> S;

inline void add(int a,int b,int c,int d){ // (a,b) <= (c,d)
//    printf("%d %d %d %d\n",a,b,c,d);
    cf[a][b]++;
    cf[a][d+1]--;
    cf[c+1][b]--;
    cf[c+1][d+1]++;
}

inline void addl(int a,int b,int c,int d){
//    assert(a-b == c-d);
    cfl[a][b]++;cfl[c+1][d+1]--;
}

inline void addr(int a,int b,int c,int d){// a < c
//    assert(a-b == d-c);
    cfr[a][b]++;cfr[c+1][d-1]--;
}

int main(){
    scanf("%d",&n);
    FOR(i,1,n) FOR(j,1,n) scanf("%d",&a[i][j]);
    FOR(i,1,n) FOR(j,1,n) if(a[i][j]) S.pb(MP(i,j));
    if(S.size() >= 2*n-1){
        FOR(i,1,n) FOR(j,1,n) printf("Y%c"," \n"[j==n]);
        return 0;
    }
    FOR(i,0,(int)S.size()-1){
        FOR(j,i+1,(int)S.size()-1){
            int x0 = S[i].fi,y0 = S[i].se,x1 = S[j].fi,y1 = S[j].se;
            if((x0+y0+x1+y1)&1) continue;
            if(x0 > x1) std::swap(x0,x1),std::swap(y0,y1);
            if(x0-x1 == y0-y1){
                //add(n,1,x1,y0);add(x0,y1,1,n);
                add(x1,1,n,y0);add(1,y1,x0,n);
                addr(x0,y1,x1,y0);
            }
            else if(x0-x1+y0-y1 == 0){
                add(1,1,x0,y1);add(x1,y0,n,n);
                addl(x0,y1,x1,y0);
            }
            else if(x0 == x1){
                int mid = (y0+y1)>>1;
                add(1,mid,n,mid);
            }
            else if(y0 == y1){
                int mid = (x0+x1) >> 1;
                add(mid,1,mid,n);
            }
            else if(x0 < x1 && y0 < y1){
                int xx = (x1-x0+y1+y0)/2,yy = (x0+y0+y1-x1)/2;
  //              assert(xx*2 == x1-x0+y1+y0);
      //          assert(yy*2 == x0+y0+y1-x1);
    //            assert(std::abs(1-x0)+std::abs(xx-y0) == std::abs(1-x1)+std::abs(xx-y1));
        //        assert(std::abs(n-x0)+std::abs(yy-y0) == std::abs(n-x1)+std::abs(yy-y1));
                add(1,xx,x0,xx);add(x1,yy,n,yy);
                addr(x0,xx,x1,yy);
            }
            else if(x0 < x1 && y0 > y1){
                int xx = (-x1+x0+y0+y1)/2,yy = (y0+y1-x0+x1)/2;
         //       assert(std::abs(1-x0)+std::abs(xx-y0) == std::abs(1-x1)+std::abs(xx-y1));
             //   assert(std::abs(n-x0)+std::abs(yy-y0) == std::abs(n-x1)+std::abs(yy-y1));
           //     assert(xx*2 == -x1+x0+y0+y1);
             //   assert(yy*2 == y0+y1-x0+x1);
                add(1,xx,x0,xx);add(x1,yy,n,yy);
                addl(x0,xx,x1,yy);
            }
            //else return -1;
        }
    }
    FOR(i,1,n){
        FOR(j,1,n){
            cf[i][j] += cf[i-1][j]+cf[i][j-1]-cf[i-1][j-1];
            cfl[i][j] += cfl[i-1][j-1];
            cfr[i][j] += cfr[i-1][j+1];
            if(cf[i][j]+cfl[i][j]+cfr[i][j] > 0){
                printf("Y%c"," \n"[j==n]);
            }
            else printf("N%c"," \n"[j==n]);
        }
    }
    return 0;
}
