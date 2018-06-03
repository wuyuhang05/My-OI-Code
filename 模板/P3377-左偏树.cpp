#include <iostream>
#include <cstring>
#include <cstdio>

const int MAXN = 100000 + 5;

struct LeftistTree{
    int ch[2],key,fa,dist;
}h[MAXN];

int N,M;

inline void Read(int &x){
    x = 0;
    int flag = 1;
    char ch = getchar();
    while(ch < '0' || ch > '9'){
        if(ch == '-') flag = -1;
        ch = getchar();
    }
    while(ch >= '0' && ch <= '9'){
        x = x * 10 + ch - '0';
        ch = getchar();
    }
    x *= flag;
}

int find(int x){
    return h[x].fa ? find(h[x].fa) : x;
}

int merge(int x,int y){
    if(!x || !y) return x + y;
    if(h[x].key > h[y].key || (h[x].key == h[y].key && x > y))
        std::swap(x,y);                     //维护左偏性质
    int &xl = h[x].ch[0],&xr = h[x].ch[1];
    xr = merge(xr,y);  //递归合并x的右子树和y
    h[xr].fa = x;
    if(h[xl].dist < h[xr].dist) std::swap(xl,xr); //按秩合并
    h[x].dist = h[y].dist + 1;
    return x;
}

void pop(int v){
    int vl = h[v].ch[0],vr = h[v].ch[1];
    h[v].key = -1;h[vl].fa = 0;h[vr].fa = 0;
    merge(vl,vr);
}

int main(){
    Read(N);Read(M);
    h[0].dist = -1;
    for(int i = 1; i <= N;i++)
        Read(h[i].key);
    while(M--){
        int opt,x;
        Read(opt);Read(x);
        if(opt & 1){
            int y;
            Read(y);
            if(h[x].key != -1 && h[y].key != -1){
                int fx = find(x),fy = find(y);
                if(fx != fy)
                merge(fx,fy);
            }
         }
         else{
             if(h[x].key == -1) printf("-1\n");
             else{
                 int fx = find(x);
                 printf("%d\n",h[fx].key);
                 pop(fx);
             }
         }
    }
    return 0;
}
