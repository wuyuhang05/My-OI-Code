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

#define fi first
#define lc (x<<1)
#define se second
#define U unsigned
#define rc (x<<1|1)
#define Re register
#define LL long long
#define MP std::make_pair
#define P std::pair<int,int>
#define CLR(i,a) memset(i,a,sizeof(i))
#define FOR(i,a,b) for(Re int i = a;i <= b;++i)
#define ROF(i,a,b) for(Re int i = a;i >= b;--i)
#define SFOR(i,a,b,c) for(Re int i = a;i <= b;i+=c)
#define SROF(i,a,b,c) for(Re int i = a;i >= b;i-=c)
#define DEBUG(x) std::cerr << #x << '=' << x << std::endl

const int MAXN = 200000+5;
const int alpha = 15;
int a[MAXN],bel[MAXN],blo,n,m;
std::vector<int> v[MAXN/100];

inline P calc(int pos){
    int top = 1;
    while(pos > v[top].size()) pos -= v[top++].size();
    return MP(top,pos-1);
}

inline void rebuild(){
    int top = 0;
    FOR(i,1,m){
        FOR(j,0,(int)v[i].size()-1) a[++top] = v[i][j];
        v[i].clear();
    }
    FOR(i,1,top) bel[i] = (i-1)/blo+1,v[bel[i]].push_back(a[i]);
    m = bel[top];
}

inline void insert(int pos,int x){
    P t = calc(pos);
    v[t.fi].insert(v[t.fi].begin()+t.se,x);
    if(v[t.fi].size()>15*blo) rebuild();
}

int main(){
    scanf("%d",&n);blo = std::sqrt(n);
    FOR(i,1,n){
        scanf("%d",a+i);
        v[(bel[i] = (i-1)/blo + 1)].push_back(a[i]);
    }
    m = bel[n];
    FOR(i,1,n){
        int opt,l,r,c;
        scanf("%d%d%d%d",&opt,&l,&r,&c);
        if(!opt) insert(l,r);
        else{
            P t = calc(r);
            printf("%d\n",v[t.fi][t.se]);
        }
    }
    return 0;
}