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
#define U unsigned
#define P std::pair
#define Re register
#define LL long long
#define pb push_back
#define MP std::make_pair
#define all(x) x.begin(),x.end()
#define CLR(i,a) memset(i,a,sizeof(i))
#define FOR(i,a,b) for(Re int i = a;i <= b;++i)
#define ROF(i,a,b) for(Re int i = a;i >= b;--i)
#define DEBUG(x) std::cerr << #x << '=' << x << std::endl

const int MAXN = 1000+5;
int n,s;
double f[MAXN][MAXN];

int main(){
    scanf("%d%d",&n,&s);f[n][s] = 0;
    ROF(i,n,0){
        ROF(j,s,0){
            if(i == n && j == s) continue;
            double p1 = 1.0*i*j/(n*s); // f[i][j]
            double p2 = 1.0*(n-i)*j/(n*s); // f[i+1][j];
            double p3 = 1.0*i*(s-j)/(n*s); // f[i][j+1];
            double p4 = 1.0*(n-i)*(s-j)/(n*s); // f[i+1][j+1];
            f[i][j] = 1.0*(1+p2*f[i+1][j]+p3*f[i][j+1]+p4*f[i+1][j+1])/(1-p1);
        }//
    }
    printf("%.4f\n",f[0][0]);
    return 0;
}
