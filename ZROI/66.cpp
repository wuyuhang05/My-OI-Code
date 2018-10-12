// F**K “熟练”剖分
// MD RE 指针 调不出来
// tao ban zi qwq
// 
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
#define lson root<<1
#define rson root<<1|1
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

struct Node{
    LL l,r,sum,tag;
}tr[400040];
LL f[100010][20],son[100010],size[100010],deep[100010],id[100010],c[100010],w[1000010],top[100010];
int cnt,root,N,Q;
std::vector<LL> g[100010];

void pushup(LL root){
    tr[root].sum = tr[lson].sum + tr[rson].sum;
}

void pushdown(LL root){
    LL mid = (tr[root].l + tr[root].r)>>1;
    tr[lson].sum += tr[root].tag * (mid - tr[root].l+1);
    tr[lson].tag += tr[root].tag;
    tr[rson].sum += tr[root].tag * (tr[root].r - mid);
    tr[rson].tag += tr[root].tag;
    tr[root].tag=0;
}

void build(LL v,LL l,LL r){
    if(l == r){
        tr[v].l = l;
        tr[v].r = r;
        tr[v].sum = w[l];
        return;
    }
    tr[v].l = l;tr[v].r = r;
    LL mid=(l+r)>>1;
    build(v<<1,l,mid);
    build(v<<1|1,mid+1,r);
    pushup(v);
}

void update(LL root,LL l,LL r,LL val){
    if(l > r) return; // RERERERERE
    if(l == tr[root].l && r == tr[root].r){
        tr[root].sum += val*(tr[root].r-tr[root].l+1);
        tr[root].tag += val;
        return ;
    }
    if(tr[root].tag)
        pushdown(root);
    LL mid = (tr[root].l + tr[root].r)>>1;
    if(l>mid)
        update(rson,l,r,val);
    else
        if(r<=mid)
            update(lson,l,r,val);
        else
            update(lson,l,mid,val),update(rson,mid+1,r,val);
    pushup(root);
}

LL query(LL root,LL l,LL r){
    if(l>r) return 0;
    if(l == tr[root].l && r == tr[root].r)
        return tr[root].sum;
    LL mid=(tr[root].l+tr[root].r)>>1;
    if(tr[root].tag)
        pushdown(root);
    if(l>mid) return query(rson,l,r);
    if(r<=mid) return query(lson,l,r);
    return query(lson,l,mid)+query(rson,mid+1,r);
}
// 套 版 子
void fuckdfs1(LL now,LL fa,LL dep){
    deep[now] = dep;
    f[now][0] = fa;
    size[now] = 1;
    LL maxson = -1;
    int sz = (int)g[now].size()-1;
    FOR(i,0,sz){
        if(g[now][i] == fa)
            continue;
        fuckdfs1(g[now][i],now,dep+1);
        size[now] += size[g[now][i]];
        if(size[g[now][i]] > maxson){
            maxson =size[g[now][i]];
            son[now] = g[now][i];
        }
    }
}

void fuckdfs2(LL now,LL topf){
    id[now] = ++cnt;
    w[cnt] = c[now];
    top[now] = topf;
    if(!son[now]) return;
    fuckdfs2(son[now],topf);
    int sz = (int)g[now].size()-1;
    FOR(i,0,sz){
        if(g[now][i] == f[now][0] || g[now][i] == son[now]) continue;
        fuckdfs2(g[now][i],g[now][i]);
    }
}

void opt2(LL p,LL val){
    if(p == root){
        update(1,1,N,val);
        return;
    }
    LL t = root;
    ROF(i,17,0)
        if(deep[f[t][i]] > deep[p])
            t = f[t][i];
    if(f[t][0]!=p)
        update(1,id[p],id[p]+size[p]-1,val);
    else
        update(1,1,id[t]-1,val),update(1,id[t]+size[t],N,val);
}

int main(){
    read(N);read(Q);
    FOR(i,1,N-1){
        int u,v;
        read(u);read(v);
        g[u].push_back(v);g[v].push_back(u);
    }
    root=1;
    fuckdfs1(1,0,1);
    fuckdfs2(1,1);
    build(1,1,N);
    FOR(j,1,17) FOR(i,1,N) f[i][j] = f[f[i][j-1]][j-1];
    while(Q--){
        LL opt,v,delta;
        read(opt);
        if(opt == 1) read(root);
        if(opt == 2){
            read(v);read(delta);
            opt2(v,delta);
        }
        if(opt == 3){
            read(v);
            printf("%lld\n",query(1,v,v));
        }
    }
}