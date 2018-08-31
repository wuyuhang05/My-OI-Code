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

const int MAXN = 26 + 5;

struct Node{
    char ch;
    Node *lc,*rc;
}node[MAXN];

#define c_int(x) (int)(x-'a'+1)
int N;
std::string str;

void dfs(Node *v){
    printf("%c",v->ch);
    if(v->lc) dfs(v->lc);
    if(v->rc) dfs(v->rc);
}

int main(){
    int root;
    scanf("%d",&N);
    FOR(i,1,26) node[i].ch = 'a' + i - 1;
    FOR(i,1,N){
        std::cin >> str;
        int v = c_int(str[0]);
        if(i == 1) root = v;
        if(str[1] != '*') node[v].lc = &node[c_int(str[1])];
        if(str[2] != '*') node[v].rc = &node[c_int(str[2])];
    }
    dfs(&node[root]);
    puts("");
    return 0;
}
