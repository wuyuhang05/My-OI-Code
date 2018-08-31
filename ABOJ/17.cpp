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

const int MAXN = 3000 + 5;

struct Node{
    struct Edge *firstEdge;
    int du;
}node[MAXN];

struct Edge{
    Node *s,*t;
    Edge *next;
}pool[MAXN*MAXN],*frog = pool;

Edge *New(Node *s,Node *t){
    Edge *ret = ++frog;
    ret->s = s;ret->t = t;
    ret->next = s->firstEdge;
    return ret;
}

inline void add(int u,int v){
    node[u].firstEdge = New(&node[u],&node[v]);
}

int T,N;

bool topsort(){
    std::queue<Node *> q;
    int num = 0;
    FOR(i,1,N)
        if(!node[i].du){
            q.push(&node[i]);
            ++num;
        }
    while(!q.empty()){
        Node *v = q.front();
        q.pop();
        for(Edge *e = v->firstEdge;e;e = e->next){
            if(--e->t->du == 0){
                q.push(e->t);
                num++;
            }
        }
    }
    if(num == N) return true;
    return false;
}
#define SSS system("sleep 1");
char str[MAXN][MAXN];

inline void Solve(){
    memset(node,0,sizeof(node));
    // std::string str[MAXN];
    // char str[MAXN][MAXN];
    frog = pool;
    scanf("%d",&N);
    FOR(i,1,N){
        // std::cin >> str[i];
        scanf("%s",str[i]);
        FOR(j,0,N-1){
            if(str[i][j] != 'O'){
                add(i,j+1);
                ++node[j+1].du;
            }
        }
    }
    if(!topsort()){
        puts("N0");
        return;
    }
    memset(node,0,sizeof(node));
    FOR(i,1,N){
        FOR(j,0,N-1){
            if(str[i][j] == 'O') continue;
            if(str[i][j] == 'H'){
                add(i,j+1);
                node[j+1].du++;
            }
            else{
                add(j+1,i);
                node[i].du++;
            }
        }
    }
    if(!topsort()) puts("N0");
    else puts("YE5");
}

int main(){
    // freopen("p.in","r",stdin);
    // freopen("p.out","w",stdout);
    scanf("%d",&T);
    while(T--)
        Solve();
    return 0;
}
