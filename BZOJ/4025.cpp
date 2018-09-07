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
#define RFOR(i,a,b) for(Re int i = a;i >= b;--i)
#define CLR(i,a) memset(i,a,sizeof(i))
#define BR printf("--------------------\n")
#define DEBUG(x) std::cerr << #x << '=' << x << std::endl

const int MAXN = 100000 + 5;

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

struct Edge{
    int u,v,st,ed;
};

int f[MAXN],dist[MAXN],c[MAXN],S[MAXN*4],top;

int find(int x){
    return x == f[x] ? x : find(f[x]);
}

int dis(int x){
    if(f[x] == x || !f[x]) return 0;
    return c[x]^dis(f[x]);
}

inline void Union(int x,int y,int w){
    if(dist[x] > dist[y]) std::swap(x,y);
    if(dist[x] == dist[y]){
        S[++top] = -y;dist[y]++;
    }
    S[++top] = x;f[x] = y;c[x] = w;
}

inline void erase(int x){
    while(top > x){
        if(S[top] < 0) dist[-S[top]]--;
        else{
            f[S[top]] = S[top];
            c[S[top]] = 0;
        }
        top--;
    }
}

void query(int l,int r,std::vector<Edge> &E){
    int pre = top;
    int mid = (l + r) >> 1;
    std::vector<Edge> L,R;
    int sz = E.size();
    FOR(i,0,sz-1){
        if(E[i].st == l && E[i].ed == r){
            int x = E[i].u,y = E[i].v;
            int fx = find(x),fy = find(y);
            if(fx != fy){
                int w = dis(x)^dis(y)^1;
                Union(fx,fy,w);
            }
            else{
                int w = dis(x)^dis(y);
                if(!(w&1)){
                    FOR(j,l,r)
                        puts("No");
                    erase(pre);
                    return;
                }
            }
        }
        else{
            if(E[i].ed <= mid) L.push_back(E[i]);
            else if(E[i].st > mid) R.push_back(E[i]);
            else{
                L.push_back((Edge){E[i].u,E[i].v,E[i].st,mid});
                R.push_back((Edge){E[i].u,E[i].v,mid + 1,E[i].ed});
            }
        }
    }
    if(l == r){
        puts("Yes");
        erase(pre);
        return;
    }
    query(l,mid,L);query(mid + 1,r,R);
    erase(pre);
}

int N,M,T;

int main(){
    read(N);read(M);read(T);
    FOR(i,1,N){
        f[i] = i;
        dist[i] = 0;
    }
    std::vector<Edge> E;
    FOR(i,1,M){
        int a,b,c,d;
        read(a);read(b);read(c);read(d);c++;
        if(c <= d)
            E.push_back((Edge){a,b,c,d});
    }
    query(1,T,E);
    return 0;
}
