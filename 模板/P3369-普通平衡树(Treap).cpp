#include <iostream>
#include <cstring>
#include <cstdio>
#include <cstdlib>
#include <ctime>

int ans,N,x,y;

struct Node{
    int key,priority; //key表示键值，priority表示优先级
    int size,num; //size表示该树的结点数量，num表示当前结点元素的数量（相同的元素数量）
    Node *ch[2]; //左右子树指针

    Node(){
        key = 0;
        priority = rand();
        size = num = 1;
        ch[0] = ch[1] = NULL;
    }
    void push(){ //更新
        size = num;
        if(ch[0] != NULL)
            size += ch[0]->size;
        if(ch[1] != NULL)
            size += ch[1]->size;
    }
}*root;

void rotate(Node *&v,int d){
    Node *t = v->ch[d^1];
    v->ch[d^1] = t->ch[d]; //改变t的子树位置
    t->ch[d] = v; //将t旋转到v上方
    v->push(); //先更新v再更新t
    t->push();
    v = t; //将t旋到v
}

void insert(Node *&v,int x){
    if(v == NULL){ //没有点就新建一个点
        v = new Node;
        v->key = x;
        return;
    }
    if(v->key == x){ //重复元素直接累加
        v->size++;
        v->num++;
        return;
    }
    if(x < v->key){ //x较小，插入左子树
        insert(v->ch[0],x);
        if(v->ch[0]->priority < v->priority) //旋转维护treap的重量平衡
            rotate(v,1);
        else v->size++; //直接更新
    }
    else{ //x较大，插入右子树
        insert(v->ch[1],x);
        if(v->ch[1]->priority < v->priority)
            rotate(v,0);
        else v->size++;
    }
}

void remove(Node *&v,int x){
    if(v == NULL) //不合法退出
        return;
    if(x == v->key){ //相等则删除
        if(v->num > 1){ //有多个相等元素，减少数量即可
            v->size--;
            v->num--;
            return;
        }
        else{ //需要完全删除
            if(v->ch[0] == NULL){ //左子树为空，将右子树移到结点上
                Node *t = v;
                v = v->ch[1];
                free(t);
                return;
            }
            if(v->ch[1] == NULL){ //右子树为空，将左子树移到结点上
                Node *t = v;
                v = v->ch[0];
                free(t);
                return;
            }
            //左右子树非空，将该结点向下旋转。
            if(v->ch[0]->priority < v->ch[1]->priority){ //左子树优先级小，为了维护treap的性质，将左子树向上旋转，作为当前树新的根结点
                rotate(v,1);
                remove(v->ch[1],x);
            }
            else{ //右子树优先级小，为了维护treap的性质，将右子树向上旋转，作为当前树新的根结点
                rotate(v,0);
                remove(v->ch[0],x);
            }
            v->size--; //删除后，更新根结点信息
        }
    }
    else{ //这个结点不需要删除
        if(x < v->key) //目标删除更小，去左子树删除
            remove(v->ch[0],x);
        else //目标删除更大，去右子树删除
            remove(v->ch[1],x);
        v->size--;
    }
}

int getk(Node *v,int x){ //询问x数的排名
    int s = 0; //s记录左子树的结点数量
    if(v->ch[0] != NULL) //判定这个结点的有无
        s = v->ch[0]->size;
    if(x <= s) //节点位于左子树内，排名为左子树内的排名
        return getk(v->ch[0],x);
    if(x <= s + v->num) //当前结点就是求的结点
        return v->key;
    else
        return getk(v->ch[1],x - s - v->num);  //节点位于左子树内，排名为左子树的元素数量 + 当前树根的结点元素数量 + 其在右子树中的排名
}

int getrank(Node *v,int x){ //查询排名是x的数
    int s = 0;  //s记录左子树的结点数量
    if(v->ch[0] != NULL) //判定这个结点的有无
        s = v->ch[0]->size;
    if(x < v->key)
        return getrank(v->ch[0],x); //目标结点位于左子树内，则其当前的排名是在左子树的排名
    if(x == v->key)
        return s + 1; //目标结点就是本结点
    else
        return s + v->num + getrank(v->ch[1],x); //目标结点位于右子树内，则其当前的排名是在右子树的排名
}

void pre(Node *v,int x){ //寻找x的前驱
    if(v == NULL) //不合法退出
        return;
    if(v->key < x){ //当前键值为可行解
        ans = v->key; //保存可行解
        pre(v->ch[1],x); //寻找更优解
    }
    else
        pre(v->ch[0],x); //不是可行解，返回
}

void succ(Node *v,int x){ //寻找x的后继
    if(v == NULL) return; //不合法退出
    if(v->key > x){ //当前键值为可行解
        ans = v->key; //保存可行解
        succ(v->ch[0],x); //寻找更优解
    }
    else
        succ(v->ch[1],x); //不是可行解，返回
}

int main(){
    srand(time(0));
    scanf("%d",&N);
    while(N--){
        scanf("%d%d",&x,&y);
        switch(x){
            case 1:
                insert(root,y);
                break;
            case 2:
                remove(root,y);
                break;
            case 3:
                printf("%d\n",getrank(root,y));
                break;
            case 4:
                printf("%d\n",getk(root,y));
                break;
            case 5:
                pre(root,y);
                printf("%d\n",ans);
                break;
            case 6:
                succ(root,y);
                printf("%d\n",ans);
                break;
        }
    }
    return 0;
}
