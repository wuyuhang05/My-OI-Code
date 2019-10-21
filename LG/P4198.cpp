/*
 * sto Qingyu orz
 * 感谢真神sqy无私的教诲。膜时队者处处阿克，只因大师sqy在他背后。不膜大师者违背了真神的旨意，真神必将降下天谴,
 * 使其天天爆零
 * 我不由自主地膜拜真神sqy。
 * Author: RainAir
 * Time: 2019-10-18 14:44:36
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
#define LL long long
#define pb push_back
#define MP std::make_pair
#define all(x) x.begin(),x.end()
#define CLR(i,a) memset(i,a,sizeof(i))
#define FOR(i,a,b) for(int i = a;i <= b;++i)
#define ROF(i,a,b) for(int i = a;i >= b;--i)
#define DEBUG(x) std::cerr << #x << '=' << x << std::endl

const int MAXN = 1e5 + 5;
#define lc (x<<1)
#define rc (x<<1|1)

int sm[MAXN<<2];
double mx[MAXN<<2];
double a[MAXN];

inline int pushup(int x,double d,int l,int r){
    if(mx[x] <= d) return 0;
    if(a[l] > d) return sm[x];
    if(l == r) return a[l]>d;
    int mid = (l + r) >> 1;
    if(mx[lc] <= d) return pushup(rc,d,mid+1,r);
    else return pushup(lc,d,l,mid)+sm[x]-sm[lc];
}

inline void update(int x,int l,int r,int p,double d){
    if(l == r){
        sm[x] = 1;
        mx[x] = d;
        return;
    }
    int mid = (l + r) >> 1;
    if(p <= mid) update(lc,l,mid,p,d);
    else update(rc,mid+1,r,p,d);
    mx[x] = std::max(mx[lc],mx[rc]);
    sm[x] = sm[lc] + pushup(rc,mx[lc],mid+1,r);
}

int n,m;

int main(){
    scanf("%d%d",&n,&m);
    FOR(i,1,m){
        int x,y;scanf("%d%d",&x,&y);
        double t = 1.0*y/x;
        a[x] = t;
        update(1,1,n,x,t);
        printf("%d\n",sm[1]);
    }
    return 0;
}
