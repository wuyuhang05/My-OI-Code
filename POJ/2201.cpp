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

const int MAXN = 50000+5;

struct Node{
    int k,a,id;
    bool operator < (const Node &t) const {
        return k < t.k;
    }
}p[MAXN];
int n,cnt;
int stk[MAXN],top,l[MAXN],r[MAXN],f[MAXN],val[MAXN],id[MAXN];


inline bool cmp(const Node &a,const Node &b){
    return a.id < b.id;
}

inline void build(int n){
    stk[top = 0] = 1;
    FOR(i,2,n){
        int j = 0;
        while(top >= 0 && val[stk[top]] > val[i]) top--;
        if(top > -1){
            f[i] = stk[top];
            f[r[stk[top]]] = i;
            l[i] = r[stk[top]];
            r[stk[top]] = i;
        }
        else{
            f[stk[0]] = i;
            l[i] = stk[0];
        }
        stk[++top] = i;
    }
}

int al[MAXN],ar[MAXN],af[MAXN];

int main(){
    scanf("%d",&n);
    FOR(i,1,n) scanf("%d%d",&p[i].k,&p[i].a),p[i].id = i;
    std::sort(p+1,p+n+1);FOR(i,1,n){
        id[i] = p[i].id;val[i] = p[i].a;
    }
    build(n);
    puts("YES");
    FOR(i,1,n){
        al[id[i]] = id[l[i]];
        ar[id[i]] = id[r[i]];
        af[id[i]] = id[f[i]];
    }
    FOR(i,1,n) printf("%d %d %d\n",af[i],al[i],ar[i]);
    return 0;
}
