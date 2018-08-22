#include <iostream>
#include <cstdio>
#include <cstring>
#include <cmath>
#include <algorithm>

const int MAXN = 30000 + 5;

inline void Read(int &x){
    int ret = 0,flag = 1;
    x = 0;
    char ch = getchar();
    while(ch > '9' || ch < '0'){
        if(ch == '-') flag = -1;
        ch = getchar();
    }
    while(ch >= '0' && ch <= '9'){
        ret = (ret << 1) + (ret << 3) + ch - '0';
        ch = getchar();
    }
    x = ret * flag;
}

int f[MAXN],num[MAXN],dist[MAXN],t;

inline void init(){
    for(int i = 1;i <= MAXN;i++){
        f[i] = i;
        num[i] = 1;
    }
}

int find(int x){
    if(x != f[x]){
        int t = f[x];
        f[x] = find(f[x]);
        dist[x] += dist[t];
        num[x] = num[f[x]];
    }
    return f[x];
}

void Union(int x,int y){
    int fx = find(x), fy = find(y);
    if(fx != fy){
        f[fx] = fy;
        dist[fx] = dist[fy] + num[fy];
        num[fy] += num[fx];
        num[fx] = num[fy];
    }
}

int query(int a,int b){
    int fa = find(a),fb = find(b);
    if(fa != fb) return -1;
    else
        return std::abs(dist[a] - dist[b]) - 1;
}

inline bool iscommand(char ch){
    return ch == 'C' || ch == 'M';
}

int main(){
    std::ios::sync_with_stdio(false);
    int T;
    Read(T);
    init();
    for(int i = 1;i <= T;i++){
        char ch;
        while(!iscommand(ch = getchar()));
        int l,r;
        Read(l);Read(r);
        if(ch == 'M') Union(l,r);
        else printf("%d\n",query(l,r));
    }
    //getchar();getchar();
    return 0;
}
