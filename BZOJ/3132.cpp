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

#define fi first
#define lc (x<<1)
#define se second
#define U unsigned
#define rc (x<<1|1)
#define Re register
#define LL long long
#define MP std::make_pair
#define CLR(i,a) memset(i,a,sizeof(i))
#define FOR(i,a,b) for(Re int i = a;i <= b;++i)
#define ROF(i,a,b) for(Re int i = a;i >= b;--i)
#define SFOR(i,a,b,c) for(Re int i = a;i <= b;i+=c)
#define SROF(i,a,b,c) for(Re int i = a;i >= b;i-=c)
#define DEBUG(x) std::cerr << #x << '=' << x << std::endl

const int MAXN = 2048+5;
int n,m;

inline void read(int &x){
    char ch = getchar();int flag = 0;x = 0;
    while(!isdigit(ch)){
        if(ch == '-') flag = 1;
        ch = getchar();
    }
    while(isdigit(ch)){
        x = (x<<1) + (x<<3) + (ch^'0');
        ch = getchar();
    }
    if(flag) x = -x;
}

struct BIT{
    #define lowbit(x) (x&-x)
    int tree[MAXN][MAXN];

    inline void add(int x,int y,int delta){
        for(int i = x;i <= n;i += lowbit(i)){
            for(int j = y;j <= m;j += lowbit(j)){
                tree[i][j] += delta;
            }
        }
    }

    inline int query(int x,int y){
        int res = 0;
        for(int i = x;i >= 1;i -= lowbit(i)){
            for(int j = y;j >= 1;j -= lowbit(j)){
                res += tree[i][j];
            }
        }
        return res;
    }
    #undef lowbit
}A,Ai,Aj,Aij;

inline int calc(int x,int y){
    return A.query(x,y)*(x*y+x+y+1) - Ai.query(x,y)*(y+1) - Aj.query(x,y)*(x+1) + Aij.query(x,y);
}

inline void add(int x,int y,int num){
    A.add(x,y,num);Ai.add(x,y,num*x);
    Aj.add(x,y,num*y);Aij.add(x,y,num*x*y);
}
int opt[3];
int main(){
    read(n);read(m);
    while(~scanf("%s",opt)){
        int a,b,c,d;read(a);read(b);read(c);read(d);
        if(opt[0] == 'L'){
            int del;read(del);
            add(a,b,del);add(a,d+1,-del);add(c+1,b,-del);add(c+1,d+1,del);
        }
        else printf("%d\n",calc(c,d)-calc(a-1,d)-calc(c,b-1)+calc(a-1,b-1));
    }
    return 0;
}