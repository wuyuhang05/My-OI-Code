#include <iostream>
#include <cstring>
#include <climits>
#include <cstdio>

namespace splay{
    const int inf = 0x7fffffff;
    struct Node *nil;
    struct Node{
        Node *ch[2];
        int val,cnt,size; //val表示元素的值，cnt表示个数，size该结点的子树包含元素的个数
        int cmp(int v){  //返回寻找v应该向左走还是向右走
            if(v == val) return -1;
            return v < val ? 0 : 1;
        }
        int cmpk(int k){ //同上，只不过是寻找第k小
            if(k <= ch[0]->size)
                return 0;
            if(k <= ch[0]->size + cnt)
                return -1;
            return 1;
        }
        void push(){
            size = cnt + ch[0]->size + ch[1]->size;
        }
        Node(int v) : val(v),cnt(1),size(1) {ch[0] = ch[1] = nil;}
    } *root;

    void init(){
        nil = new Node(0);
        root = nil->ch[0] = nil->ch[1] = nil;
        nil->size = nil->cnt = 0;
    }

    void rotate(Node *&t,int d){
        Node *k = t->ch[d ^ 1];
        t->ch[d ^ 1] = k->ch[d];
        k->ch[d] = t;
        t->push();k->push();
        t = k;
    }

    void splay(int v,Node *&t){ //在树t中寻找值为v的节点，并伸展成为t的根节点
        int d = t->cmp(v); // 定义方向
        if(d != -1 && t->ch[d] != nil){
            int d2 = t->ch[d]->cmp(v);
            if(d2 != -1 && t->ch[d]->ch[d2] != nil){
                splay(v,t->ch[d]->ch[d2]);
                if(d == d2)
                    rotate(t,d2^1),rotate(t,d^1);
                else
                    rotate(t->ch[d],d2^1),rotate(t,d ^ 1);
        }
        else rotate(t,d ^ 1);
    }
}

void splayk(int k,Node *&t){  //在树t中寻找第K小的节点，并伸展成为t的根节点
    int d = t->cmpk(k);
    if(d == 1)
        k -= t->ch[0]->size + t->cnt;
    if(d != -1){
        int d2 = t->ch[d]->cmpk(k);
        int k2 = (d2 == 1) ? k-(t->ch[d]->ch[0]->size + t->ch[d]->cnt) : k;
        if(d2 != -1){
            splayk(k2,t->ch[d]->ch[d2]);
            if(d == d2)
                rotate(t,d2^1),rotate(t,d^1);
            else
                rotate(t->ch[d],d2^1),rotate(t,d^1);
        }
        else rotate(t,d^1);
    }
}

int pre(int v,Node *&t = root){ //前驱,找左边
    splay(v,t);
    if(t->val >= v){
        if(t->ch[0] == nil)
            return -inf;
        splay(inf,t->ch[0]);
        return t->ch[0]->val;
    }
    else
        return t->val;
}

int succ(int v,Node *&t = root){ //后继，找右边
    splay(v,t);
    if(t->val <= v){
        if(t->ch[1] == nil)
            return inf;
        splay(-inf,t->ch[1]);
        return t->ch[1]->val;
    }
    else
        return t->val;
}

int getrank(int v,Node *&t = root){ //求排名为v的结点
    splay(v,t);
    return t->ch[0]->size + 1;
}

int getk(int k,Node *&t = root){ //求第K大
    splayk(k,t);
    return t->val;
}

Node *split(int v,Node *&t){ //分裂,树t都是小于等于X的元素，返回的树都是大于X的元素
    if(t == nil)
        return nil;
    splay(v,t);
    Node *t1,*t2;
    if(t->val <= v){
        t1 = t;t2 = t->ch[1];t->ch[1] = nil;
    }
    else{
        t1 = t->ch[0];t2 = t;t->ch[0] = nil;
    }
    t->push();
    t = t1;
    return t2;
}

void merge(Node *&t1,Node *&t2){
    if(t1 == nil)
        std::swap(t1,t2);
    splay(inf,t1);
    t1->ch[1] = t2;
    t2 = nil;
    t1->push();
}

void insert(int v,Node *&t = root){
    Node *t2 = split(v,t);
    if(t->val == v)
        t->cnt++;
    else{
        Node *node = new Node(v);
        merge(t,node);
    }
    merge(t,t2);
}

void erase(int v,Node *&t = root){
    Node *t2 = split(v,t);
    if(t->val == v && --(t->cnt) < 1){
        Node *t3 = t->ch[0];
        delete t;
        t = t3;
    }
    merge(t,t2);
}
}

int main(){
    splay::init();
    int N,opt,x;
    scanf("%d",&N);
    while(N--){
        scanf("%d%d",&opt,&x);
        switch(opt){
            case 1:
                splay::insert(x);
                break;
            case 2:
                splay::erase(x);
                break;
            case 3:
                printf("%d\n",splay::getrank(x));
                break;
            case 4:
                printf("%d\n",splay::getk(x));
                break;
            case 5:
                printf("%d\n",splay::pre(x));
                break;
            case 6:
                printf("%d\n",splay::succ(x));
                break;
        }
    }
    getchar();getchar();
    return 0;
}
