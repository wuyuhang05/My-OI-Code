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

#define R register
#define LL long long
#define U unsigned
#define FOR(i,a,b) for(R int i = a;i <= b;++i)
#define RFOR(i,a,b) for(R int i = a;i >= b;--i)
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

const int MAXN = 4000000 + 5;

struct Node{
    int opt,x,pos;
    bool operator <  (const Node &other) const {
        if(x == other.x) return opt < other.opt;
        return x < other.x;
    }
}node[MAXN];

int N,M,cnt,pos[MAXN];
const int ha = 998244353;

inline LL qpow(LL a,LL n){
    LL ret = 1ll;
    while(n){
        if(n & 1) ret = (ret * a) % ha;
        a = (a * a) % ha;
        n >>= 1;
    }
    return ret;
}

int main(){
    read(N);read(M);
    FOR(i,1,N){
        int l,r;
        read(l);read(r);
        node[++cnt] = (Node){1,l,i};
        node[++cnt] = (Node){3,r,i};
    }
    FOR(i,1,M){
        int k;read(k);
        node[++cnt] = (Node){2,k,i};
    }
    std::sort(node + 1,node + cnt + 1);
    LL ans = 0ll;
    LL s = 0,tot = 0,last= 0;
    FOR(i,1,cnt){
        Node *v = &node[i];
        if(v->opt == 1){
            ++s;
            pos[v->pos] = last;
            continue;
        }
        if(v->opt == 3){
            if(pos[v->pos] == last) s--;
            else{
                s--;tot--;
            }
        }
        else{
            ans = (ans + qpow(2,s)%ha - qpow(2,tot)%ha)%ha;
            tot = s;last = i;
        }
    }
    printf("%lld\n",(ans+ha)%ha);
    return 0;
}
