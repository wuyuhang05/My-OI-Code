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
#define int long long
const int MAXN = 100000000 + 5;

int dis[MAXN];
bool vis[MAXN];

std::queue<int> q;

int S,T;

inline void calc(int v,int u,int val){
	if(dis[v] > dis[u] + val){
		dis[v] = dis[u] + val;
		if(!vis[v]) q.push(v),vis[v] = true;
	}
}

inline void spfa(){
	while(!q.empty()){
		int v = q.front();q.pop();
		if(v < T) calc(v+1,v,1);
		if(v > 0){
			calc(v-1,v,1);
			for(int i = 1;v*i <= T;i++){
				if(v*(i+1) > T) calc(T,v,2*i+4+v*(i+1)-T);
				else calc(v*(i+1),v,2*i+4);
			}
		}
		vis[v] = false;
	}
}

signed main(){
	read(S);read(T);
	FOR(i,0,T) dis[i] = INT_MAX;
	if(S > T){
		dis[0] = 3;dis[T] = S-T;
		vis[S] = vis[T] = vis[0] = true;
		q.push(0);q.push(T); 
	}
	else{
		dis[S] = 0;vis[S] = 1;
		q.push(S);
	}
	spfa();
	printf("%d\n",dis[T]);
	return 0;
}

