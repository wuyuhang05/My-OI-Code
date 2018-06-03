#include <algorithm>
#include <iostream>
#include <cstring>
#include <cstdio>
#include <vector>

#define DEBUG(x) std::cerr << #x << '=' << x << std::endl

const int MAXN = 50000 + 5;

struct Edge{
    int l,r;
    bool operator < (const Edge &a) const {
        return l < a.l;
    }
}e[MAXN];

int N;
std::vector<Edge> ans;

int main(){
    scanf("%d",&N);
    for(int i = 1;i <= N;i++)
        scanf("%d%d",&e[i].l,&e[i].r);
    std::sort(e + 1,e + N + 1);
    int l = e[1].l,r = e[1].r;
    for(int i = 2;i <= N;i++){
        if(e[i].l >= l && e[i].l <= r && e[i].r >= r)
            r = e[i].r;
        else if(e[i].l >= r){
            printf("%d %d\n",l,r);
            l = e[i].l;r = e[i].r;
        }
    }
    printf("%d %d",l,r);
    //getchar();getchar();
    return 0;
}
