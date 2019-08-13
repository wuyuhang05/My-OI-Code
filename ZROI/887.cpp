/*
 * Author: RainAir
 * Time: 2019-08-08 09:34:07
 */
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

const int MAXN = 10000+5;

struct Node{
    int mx,mn,len;
    Node(){len = 1e9;}

    bool operator < (const Node &t) const {
        return len == t.len ? mx-mn < t.mx-t.mn : len < t.len;
    }
}f[MAXN];

int n,m,a[MAXN];

inline Node min(const Node &a,const Node &b){
    return a < b ? a : b;
}

inline Node update(Node a,int x){
    a.len++;a.mx = std::max(a.mx,x);
    a.mn = std::min(a.mn,x);
    return a;
}

int main(){
    scanf("%d%d",&n,&m);
    FOR(i,1,n) scanf("%d",a+i);
    std::sort(a+1,a+n+1);
  //  f[1][a[1]].mx = f[1][a[1]].mn = a[1];f[1][a[1]].len = 1;
//    f[1][0].mx = f[1][0].mn = 0;f[1][0].len = 0;
    f[0].len = 0,f[0].mn = m,f[0].mx = 0;
    FOR(i,1,n){
        ROF(j,m,a[i]){
            idf(f[j-a[i]].len >= 1e9) continue;
            Node t = update(f[j-a[i]],a[i]);
            if(f[j].len == 1e9) f[j] = t;
            else f[j] = std::min(f[j],t);
        }
    }
    if(f[m].len >= 1e9) puts("-1");
    else printf("%d\n",f[m].mx-f[m].mn);
    return 0;
}

