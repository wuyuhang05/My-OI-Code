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

#define Re register
#define LL long long
#define U unsigned
#define FOR(i,a,b) for(Re int i = a;i <= b;++i)
#define ROF(i,a,b) for(Re int i = a;i >= b;--i)
#define CLR(i,a) memset(i,a,sizeof(i))
#define BR printf("--------------------\n")
#define DEBUG(x) std::cerr << #x << '=' << x << std::endl

const int MAXN = 100000 + 5;

struct Node{
    int val,size,tag;
    //int v,s,t;
    Node *ch[2];  

    inline void pushup(){
        size = (ch[0] ? ch[0]->size : 0) + (ch[1] ? ch[1]->size : 0) + 1;
    }

    inline void pushdown(){
        if(tag){
            if(ch[0]) ch[0]->tag^=1;
            if(ch[1]) ch[1]->tag^=1;
            tag=0;
            std::swap(ch[0],ch[1]);
        }
    }

}pool[MAXN<<2],*frog = pool,*root;

Node *New(int val){
    Node *cur = ++frog;cur->val = val;
    cur->size = 1;cur->tag = 0;
    return cur;
}

inline void rotate(Node *&v,int d){
    Node *t = v->ch[d^1];
    t->pushdown();
    v->ch[d^1] = t->ch[d];
    t->ch[d] = v;
    v->pushup();t->pushup();
    v = t;
}

void insert(Node *&v,int val){
    if(!v) v = New(val);
    else{
        insert(v->ch[val < v->val ? 0 : 1],val);
        v->pushup();    
    }
}

void splay(Node *&v,int k){
    v->pushdown();
    int ls = v->ch[0] ? v->ch[0]->size : 0;
    if(ls + 1 == k) return;
    int d = k <= ls ? 0 : 1;
    if(v->ch[d]) v->ch[d]->pushdown();
    int k2 = d ? k - ls - 1 : k;
    int ls2 = v->ch[d]->ch[0] ? v->ch[d]->ch[0]->size : 0;
    if(ls2+1 != k2){
        int d2 = k2 <= ls2 ? 0 : 1;
        splay(v->ch[d]->ch[d2],d2 ? k2 - ls2 - 1 : k2);
        if(d == d2) rotate(v,d^1);
        else rotate(v->ch[d],d2^1);
    }
    rotate(v,d^1);
}

int kth(Node *&v,int val){
    splay(v,val);
    return v->val;
}

int N,M;

int main(){
    scanf("%d%d",&N,&M);
    FOR(i,1,N){
        insert(root,i);DEBUG(i);
        splay(root,i);
    }
    FOR(i,1,M){
        int l,r;scanf("%d%d",&l,&r);
        if(l == 1 && r == N) root->tag ^= 1;
        else if(l == 1){
            splay(root,r+1);
            root->ch[0]->tag ^= 1;
        }
        else if(r == N){
            splay(root,l-1);
            root->ch[1]->tag ^= 1;
        }
        else{
            splay(root,l-1);
            splay(root->ch[1],r - (root->ch[0] ? root->ch[0]->size : 0));
            root->ch[1]->ch[0]->tag ^= 1;
        }
    }
    FOR(i,1,N) printf("%d%c",kth(root,i),(i == N) ? '\n' : ' ');
    return 0;
}
