/*
 * Author: RainAir
 * Time: 2019-08-04 18:32:40
 */
#include <unordered_map>
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

const int MAXN = 5000+5;

struct _{
    int l1,r1,l2,r2;

    bool operator < (const _ &t) const {
        return l2 < t.l2;
    }
}a[MAXN];
int n,m1,m2,q;
//char base[MAXN];
std::unordered_map<int,char> base;
std::pair<int,char> mo[MAXN];

inline int calc(int pos){
    int i = m2;
    while(i){
        if(a[i].l2 <= pos && pos <= a[i].r2){
            int t = a[i].l2-a[i].l1;
            pos = pos - (pos-a[i].l1)/t * t;// 重叠
            //while(pos)
        }
        else i--;
    }
    return pos;
}

int main(){
    scanf("%d%d%d%d",&n,&m1,&m2,&q);
    FOR(i,1,m1){
        char str[23];int x;scanf("%d%s",&x,str+1);
        mo[i] = MP(x,str[1]);
    }
    FOR(i,1,m2) scanf("%d%d%d%d",&a[i].l1,&a[i].r1,&a[i].l2,&a[i].r2);
    std::sort(a+1,a+m2+1);
    FOR(i,1,m1){
        int pos = calc(mo[i].fi);
        base[pos] = mo[i].se;
    }
    FOR(i,1,q){
        int pos;scanf("%d",&pos);
        pos = calc(pos);
        putchar(base[pos] == 0 ? '?' : base[pos]);puts("");
    }
    return 0;
}
