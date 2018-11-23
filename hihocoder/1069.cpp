#include <algorithm>
#include <iostream>
#include <cstring>
#include <climits>
#include <cstdlib>
#include <cstdio>
#include <vector>
#include <queue>
#include <stack>
#include <map>
#include <set>

#define Re register
#define LL long long
#define CLR(a,b) memset(a,b,sizeof(a))
#define FOR(i,a,b) for(Re int i = a;i <= b;++i)
#define ROF(i,a,b) for(Re int i = a;i >= b;--i)
#define DEBUG(x) std::cerr << #x << '=' << x << std::endl

int N,cnt;
std::map<std::string,int> S;
std::map<int,std::string> rS;

inline int calc(const std::string &str){
    if(S[str]) return S[str];
    S[str] = ++cnt;
    rS[cnt] = str;
    return cnt;
}

const int MAXN = 100000+5;

struct Node{
    struct Edge *firstEdge;
    int depth,num;
}node[MAXN];

struct Edge{
    Node *s,*t;
    Edge *next;
}pool[MAXN<<1],*frog = pool;

Edge *New(Node *s,Node *t){
    Edge *ret = ++frog;
    ret->s = s;ret->t = t;
    ret->next = s->firstEdge;
    return ret;
}

inline void add(int u,int v){
    //DEBUG(u);DEBUG(v);
    node[u].firstEdge = New(&node[u],&node[v]);
    node[v].firstEdge = New(&node[v],&node[u]);
}

int f[MAXN][30];
float log2N;
// f[v][i] = f[f[v][i-1]][i-1]

inline void pre(){
    CLR(f,-1);
    FOR(i,1,cnt){
        node[i].depth = 0;
        node[i].num = i;
    }
    log2N = log2(cnt)+1;
}

void dfs(Node *v,Node *fa=NULL){
    FOR(i,1,log2N){
        if(v->depth <= (1<<i)) break;
        f[v->num][i] = f[f[v->num][i-1]][i-1];
    }
    for(Edge *e = v->firstEdge;e;e = e->next){
        if(e->t == fa) continue;
        e->t->depth = v->depth + 1;
        f[e->t->num][0] = v->num;
        dfs(e->t,v);
    }
}

int lca(int x,int y){
    int dx = node[x].depth,dy = node[y].depth;
    if(dx != dy){
        if(dx < dy){
            std::swap(x,y);
            std::swap(dx,dy);
        }
        int d = dx-dy;
        FOR(i,0,log2N)
            if((1<<i)&d)
                x = f[x][i];
    }
    if(x == y) return x;
    ROF(i,log2N,0){
        if(f[x][i] == f[y][i]) continue;
        x = f[x][i],y = f[y][i];
    }
    return f[x][0];
}

std::string str1,str2;
int M;
int main(){
    std::ios::sync_with_stdio(false);
    std::cin >> N;
    FOR(i,1,N){
        std::cin >> str1 >> str2;
        int u = calc(str1),v = calc(str2);
        add(u,v);
    }pre();node[1].depth = 1;
    dfs(&node[1]);
    std::cin >> M;
    while(M--){
        std::cin >> str1 >> str2;
        int x = calc(str1),y = calc(str2);
        //DEBUG(x);DEBUG(y);
        std::cout << rS[lca(x,y)] << std::endl;
    }
    system("pause");
    return 0;
}