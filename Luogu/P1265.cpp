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

namespace fastIO{ 
    #define BUF_SIZE 100000 
    #define OUT_SIZE 100000 
    #define ll long long 
    bool IOerror=0; 
    inline char nc(){ 
        static char buf[BUF_SIZE],*p1=buf+BUF_SIZE,*pend=buf+BUF_SIZE; 
        if (p1==pend){ 
            p1=buf; pend=buf+fread(buf,1,BUF_SIZE,stdin); 
            if (pend==p1){IOerror=1;return -1;} 
        } 
        return *p1++; 
    } 
    inline bool blank(char ch){return ch==' '||ch=='\n'||ch=='\r'||ch=='\t';} 
    inline void read(int &x){ 
        bool sign=0; char ch=nc(); x=0; 
        for (;blank(ch);ch=nc()); 
        if (IOerror)return; 
        if (ch=='-')sign=1,ch=nc(); 
        for (;ch>='0'&&ch<='9';ch=nc())x=x*10+ch-'0'; 
        if (sign)x=-x; 
    } 
    inline void read(ll &x){ 
        bool sign=0; char ch=nc(); x=0; 
        for (;blank(ch);ch=nc()); 
        if (IOerror)return; 
        if (ch=='-')sign=1,ch=nc(); 
        for (;ch>='0'&&ch<='9';ch=nc())x=x*10+ch-'0'; 
        if (sign)x=-x; 
    } 
    #undef ll 
    #undef OUT_SIZE 
    #undef BUF_SIZE 
}; 
using namespace fastIO;

const int MAXN = 5000 + 5;

struct Node{
    int x,y;
    double dist;bool used;
}p[MAXN];

double cost(Node *a,Node *b){
    return sqrt((double)(a->x - b->x) * (double)(a->x - b->x) + (double)(a->y - b->y) * (double)(a->y - b->y));
}

int N;
#define MP std::make_pair
#define P std::pair<int,Node *>

double prim(){
    FOR(i,1,N){
        p[i].dist = INT_MAX;
        p[i].used = false;
    }
    std::priority_queue<P,std::vector<P>,std::greater<P> > q;
    q.push(MP(0,&p[1]));p[1].dist = 0.0;
    double ret = 0.0;
    while(!q.empty()){
        Node *v = q.top().second;
        q.pop();
        if(v->used) continue;
        v->used = true;
        ret += v->dist;
        FOR(i,1,N){
            Node *vv = &p[i];
            if(v == vv) continue;
            double w = cost(v,vv);
            if(vv->dist > w){
                vv->dist = w;
                q.push(MP(vv->dist,vv));
            }
        }
    }
    return ret;
}

int main(){
    read(N);
    FOR(i,1,N) read(p[i].x),read(p[i].y);
    printf("%.2f\n",prim());
    return 0;
}