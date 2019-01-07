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

const int MAXN = 600000+5;

struct Node{
    std::vector<int> idx;
    Node *ch[28];
    char a;
    Node(){
        idx.clear();CLR(ch,NULL);
    }
}*root;

Node *New(){
    Node *cur = new Node();
    CLR(cur->ch,NULL);
    cur->idx.clear();
    return cur;
}

inline int get(char x){
    if(x == '*') return 27;
    if(x == '?') return 26;
    return (int)x-'a';
}

inline void insert(char *str,int pos){
    int len = strlen(str+1);
    Node *v = root;//DEBUG(len);
    FOR(i,1,len){
        int x = get(str[i]);//DEBUG(x);
        if(!v->ch[x]){
            v->ch[x] = New();
            v->a = str[i];
        }
        v = v->ch[x];
    }
    v->idx.push_back(pos-1);
}

std::vector<int> ans;
bool vis[100000+5];
char str[20+5];
int len;

inline void dfs(int pos,Node *v=root){
    //DEBUG(pos);
    if(v->ch[get('*')]){
        FOR(i,pos,len+1)
            dfs(i,v->ch[27]);
    }
    if(pos == len+1){
        FOR(i,0,(int)v->idx.size()-1){
            //DEBUG(i);
            if(!vis[v->idx[i]]){
                vis[v->idx[i]] = true;
                ans.push_back(v->idx[i]);
            }
        }
        return;
    }
    int x = get(str[pos]);//DEBUG(x);
    if(v->ch[x]) dfs(pos+1,v->ch[x]);
    if(v->ch[get('?')]) dfs(pos+1,v->ch[get('?')]);
    // if(v->ch[get('*')]) dfs(pos+1,v->ch[get('*')]),dfs(pos,v->ch[get('*')]);
    //if(v->a == '*') dfs(pos+1,v);
}

inline void print(){
    if(!ans.size()) puts("Not match");
    else{
        std::sort(ans.begin(),ans.end());
        FOR(i,0,(int)ans.size()-1) printf("%d ",ans[i]);puts("");
    }
    ans.clear();CLR(vis,0);
}

int N,M;

inline void Solve(){
    // scanf("%d%d",&N,&M);
    root = New();
    FOR(i,1,N){
        scanf("%s",str+1);
        insert(str,i);
    }
    FOR(i,1,M){
        scanf("%s",str+1);len = strlen(str+1);
        //str[len+1] = '\0';
        dfs(1);print();
    }
}

int main(){
    while(~scanf("%d%d",&N,&M)) Solve();
    return 0;
}