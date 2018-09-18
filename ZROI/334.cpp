#include <algorithm>
#include <iostream>
#include <cstring>
#include <climits>
#include <cstdio>
#include <vector>
#include <cmath>
#include <queue>
#include <stack>
#include <map>
#include <set>

#define R register
#define LL long long
#define U unsigned
#define FOR(i,a,b) for(R int i = a;i <= b;++i)
#define RFOR(i,a,b) for(R int i = a;i >= b;--i)
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

const int MAXN = 1000000 + 5;

int N,M;
std::map<int,int> S;
int u[15],v[15];

struct Node{
    struct Edge *firstEdge;
    bool vis;
    int num;
}node[MAXN];

struct Edge{
    Node *s,*t;
    Edge *next;
}pool[MAXN*2],*frog = pool;

Edge *New(Node *s,Node *t){
    Edge *ret = ++frog;
    ret->s = s;ret->t = t;
    ret->next = s->firstEdge;
    return ret;
}

inline void add(int u,int v){
    node[u].firstEdge = New(&node[u],&node[v]);
    node[v].firstEdge = New(&node[v],&node[u]);
}

LL get(int x){
    if(S[x]) return S[x];
    return S[x] = (int)S.size();
}

LL calc(int v,int n,int d){
    LL t = v,c = 0,ret = 0;
    while(t){
        c++;
        t /= 2;
    }
    ret = (1<<(d-c+1))-1;t=c;
    while(t < d){
        t++;
        v = v << 1 | 1;
    }
    return ret - std::max(std::min(v-n,1<<(d-c)),0);
}

LL num[MAXN];
const int ha = 1000000007;

inline void init(Node *v,Node *fa){
    for(Edge *e = v->firstEdge;e;e = e->next){
        if(e->t != fa){
            num[v->num] = (num[v->num] - num[e->t->num]+ha)%ha;
            init(e->t,v);
        }
    }
}

void dfs(Node *v,LL &tot){
    tot = (tot + num[v->num])%ha;// DEBUG(tot);
    v->vis = true;
    for(Edge *e = v->firstEdge;e;e = e->next){
        if(!e->t->vis) dfs(e->t,tot);
    }
    v->vis = false;
}


int main(){
    read(N);read(M);
    FOR(i,1,MAXN-1) node[i].num = i;
    int d = 0;
    while((1 << d) <= N) d++;
    get(1);
    FOR(i,1,M){
        read(u[i]);read(v[i]);
        for(int t = u[i];t;get(t),t/=2);
        for(int t = v[i];t;get(t),t/=2);
    }
    for(std::map<int,int>::iterator it = S.begin();it != S.end();it++){
        int v=it->first,id=it->second;
        if(v>1) add(get(v),get(v/2));
        num[id] = calc(v,N,d);
    }
    init(&node[1],NULL);
    FOR(i,1,M){
        add(get(u[i]),get(v[i]));
    }
    LL ans = 0;
    FOR(i,1,S.size()){
        LL tot=0;
        dfs(&node[i],tot);
        ans = (ans + (tot*num[i])%ha)%ha;
    }
    printf("%lld\n",ans);
    return 0;
}
