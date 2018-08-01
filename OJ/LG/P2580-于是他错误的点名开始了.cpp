#include <algorithm>
#include <iostream>
#include <cstring>
#include <climits>
#include <cstdlib>
#include <cstdio>
#include <vector>
#include <cmath>
#include <queue>
#include <stack>
#include <map>
#include <set>

#define LL long long
#define ULL unsigned long long
#define DEBUG(x) std::cerr << #x << '=' << x << std::endl

const int MAXC = 26 + 5;
const int MAXN = 10000 + 5;
const int MAXM = 100000 + 5;

int N,M;

struct Node;
Node *New();

struct Node{
    char c;
    Node *ch[MAXC];
    int size,tag;
    bool rep;
}pool[MAXN * MAXC],*frog = pool,*root;

Node *New(char c){
    Node *ret = ++frog;
    ret->c = c;
    memset(ret->ch,0,sizeof(ret->ch));
    ret->tag = ret->rep = ret->size = 0;
    return ret;
}

void insert(char *str){
    Node *p = root;
    int len = strlen(str);
    for(int i = 0;i < len;i++){
        int j;
        for(j = 0;j < p->size;j++)
            if(p->ch[j]->c == str[i])
                break;
        if(j == p->size){
            Node *v = New(str[i]);
            p->ch[p->size++] = v;
            p = v;
        }
        else p = p->ch[j];
    }
    p->tag = 1;
}

int query(char *str){
    Node *p = root;
    int len = strlen(str);
    for(int i = 0;i < len;i++){
        int j;
        for(j = 0;j < p->size;j++)
            if(p->ch[j]->c == str[i]) break;
        if(j == p->size) return 0;
        p = p->ch[j];
    }
    if(!p->rep){
        p->rep = true;return p->tag;
    }
    else if(p->rep) return 2;
}

int main(int argc,char *argv[]){
    root = New(0);
    scanf("%d",&N);
    char str[55];
    for(int i = 1;i <= N;i++){
        scanf("%s",str);
        insert(str);
    }
    scanf("%d",&M);
    for(int i = 1;i <= M;i++){
        scanf("%s",str);
        int cmd = query(str);
        if(!cmd) puts("WRONG");
        else if(cmd&1) puts("OK");
        else puts("REPEAT");
    }
    getchar();getchar();
    return 0;
}
