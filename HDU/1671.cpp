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
#define ROF(i,a,b) for(Re int i = a;i >= b;--i)
#define SFOR(i,a,b,c) for(Re int i = a;i <= b;i+=c)
#define SROF(i,a,b,c) for(Re int i = a;i >= b;i-=c)
#define CLR(i,a) memset(i,a,sizeof(i))
#define BR printf("--------------------\n")
#define DEBUG(x) std::cerr << #x << '=' << x << std::endl

inline int getid(char x){
    return x-'0';
}

const int MAXN = 100000+5;

struct Node{
    int end;
    Node *next[10];
}pool[MAXN],*frog = pool,*root;

Node *New(){
    Node *cur = ++frog;
    cur->end = 0;CLR(cur->next,NULL);
    return cur;
}

inline bool insert(char *str){
    int len = strlen(str+1);
    bool flag = false;
    Node *v = root;
    FOR(i,1,len){
        int x = getid(str[i]);
        //DEBUG(v->bel);
        if(!v->next[x]){
            v->next[x] = New();
            flag = true;
        }
        v = v->next[x];
        if(v->end) return false;
        //DEBUG(v->bel);
    }
    v->end++;
    return flag;
}

int N;
char str[MAXN];
bool flag;

inline void Solve(){
    scanf("%d",&N);flag = true;frog = pool;CLR(pool,0);
    root = New();
    FOR(i,1,N) scanf("%s",str+1),flag &= insert(str);
    puts(flag ? "YES" : "NO");
}

int main(){
    int T;scanf("%d",&T);
    while(T--) Solve();
    return 0;
}