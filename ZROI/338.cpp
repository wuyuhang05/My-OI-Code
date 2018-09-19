// buhui
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
#define RFOR(i,a,b) for(Re int i = a;i >= b;--i)
#define SFOR(i,a,b,c) for(Re int i = a;i <= b;i+=c)
#define CLR(i,a) memset(i,a,sizeof(i))
#define BR printf("--------------------\n")
#define DEBUG(x) std::cerr << #x << '=' << x << std::endl

const int MAXN = 200000 + 5;

int p[MAXN],s[MAXN];

struct SegmentTree{
    int l,r,pre,suf,min;
}node[MAXN*4];

inline void pushup(int now){
    node[now].pre = std::max(node[now<<1].pre,node[now<<1|1].pre);
    node[now].suf = std::max(node[now<<1].suf,node[now<<1|1].suf);
    node[now].min = std::max(node[now<<1].pre+node[now<<1|1].suf,std::max(node[now<<1].min,node[now<<1|1].min));
}

inline void build(int now,int l,int r){
    if(l == r){
        node[now].pre = p[l];
        node[now].suf = s[l];
        node[now].min = INT_MIN;
        return;    
    }
    int mid = (l + r) >> 1;
    build(now<<1,l,mid);
    build(now<<1|1,mid+1,r);
    pushup(now);
}

int left,res;

inline void query(int now,int l,int r,int L,int R){
   // DEBUG(now);system("sleep 1");
    if(L <= l && r <= R){
        if(left == INT_MIN) res = std::max(res,node[now].min),left=node[now].pre;
        else{
            res = std::max(res,std::max(node[now].min,left+node[now].suf));
            left = std::max(left,node[now].pre);
        }
        return;
    }
    int mid = (l + r) >> 1;
    if(L <= mid) query(now<<1,l,mid,L,R);
    if(R > mid) query(now<<1|1,mid+1,r,L,R);
}

char str[MAXN];
int N,Q;

int main(){
    scanf("%d%d%s",&N,&Q,str+1);
    FOR(i,1,N)
        p[i] = p[i-1] + ((str[i] == '1') ? 1 : -1);
    RFOR(i,N,1)
        s[i] = s[i+1] + ((str[i] == '1') ? 1 : -1);
    build(1,0,N+1);
    while(Q--){
        int l,r;scanf("%d%d",&l,&r);
        res = left = INT_MIN;
        l--;r++;
        query(1,0,N+1,l,r);
        printf("%d\n",res-p[l]-s[r]);
    }
    return 0;
}