/*
* Author: RainAir
* File Name: P5540.cpp
* Date: 2020-03-01 17:33:23
* Last Modified time: 2020-03-01 19:44:17
*/
#include <algorithm>
#include <iostream>
#include <cstring>
#include <climits>
#include <cstdlib>
#include <cstdio>
#include <bitset>
#include <vector>
#include <cmath>
#include <ctime>
#include <queue>
#include <stack>
#include <map>
#include <set>

#define fi first
#define se second
#define U unsigned
#define P std::pair
#define LL long long
#define pb push_back
#define MP std::make_pair
#define all(x) x.begin(),x.end()
#define CLR(i,a) memset(i,a,sizeof(i))
#define FOR(i,a,b) for(int i = a;i <= b;++i)
#define ROF(i,a,b) for(int i = a;i >= b;--i)
#define DEBUG(x) std::cerr << #x << '=' << x << std::endl

inline char nc(){
    #define SIZE 1000000+3
    static char buf[SIZE],*p1 = buf+SIZE,*p2 = buf+SIZE;
    if(p1 == p2){
        p1 = buf;p2 = buf+fread(buf,1,SIZE,stdin);
        if(p1 == p2) return -1;
    }
    return *p1++;
    #undef SIZE
}

template <typename T>
inline void read(T &x){
    x = 0;int flag = 0;char ch = nc();
    while(!isdigit(ch)){
        if(ch == '-') flag = 1;
        ch = nc();
    }
    while(isdigit(ch)){
        x = (x<<1) + (x<<3) + (ch^'0');
        ch = nc();
    }
    if(flag) x = -x;
}


const int MAXN = 1e4 + 5;
int f[205];
inline int find(int x){
	return x == f[x] ? x : f[x] = find(f[x]);
}

struct Edge{
	int u,v;LL w;int id;
	bool use;
	Edge(int u=0,int v=0,LL w=0,int id=0,int use=0) : u(u),v(v),w(w),id(id),use(use) {}
	bool operator < (const Edge &t) const {
		return w < t.w;
	}
}e[MAXN];
int n,m;
struct Node{
	int u,v,a,b;
}A[MAXN];

inline void Kruskal(){
	std::sort(e+1,e+m+1);FOR(i,1,n) f[i] = i;
	int cnt = 0;
	FOR(i,1,m){
		int fu = find(e[i].u),fv = find(e[i].v);
		if(fu == fv) continue;
		f[fv] = fu;e[i].use = 1;
		if(++cnt == n-1) break;
	}
}
LL mn = 1e18;
LL ansx,ansy;

inline void update(LL a,LL b){
	if(a*b < mn){
		mn = a*b;
		ansx = a;ansy = b;
		return;
	}
	if(a*b == mn && a < ansx){
		ansx = a;ansy = b;
		return;
	}
}
inline void work(LL xA,LL yA,LL xB,LL yB){
	update(xA,yA);update(xB,yB);
	LL now = xA*(yB-yA)-yA*(xB-xA);
	FOR(i,1,m) e[i] = Edge(A[i].u,A[i].v,(xB-xA)*A[i].b-(yB-yA)*A[i].a,i);
	Kruskal();
	FOR(i,1,m) if(e[i].use) now += e[i].w;
	if(now >= 0) return;
	LL xC = 0,yC = 0;
	FOR(i,1,m) if(e[i].use) xC += A[e[i].id].a,yC += A[e[i].id].b;
	work(xA,yA,xC,yC);work(xC,yC,xB,yB); // 这里顺序很有关系！必须保证 xAyA  第一维小
}
/*
(B-A)*(C-A) >= 0
(xB-xA,yB-yA)*(xC-xA,yC-yA) >= 0
(xB-xA)(yC-yA)-(yB-yA)(xC-xA) >= 0
yC(xB-xA)-xC(yB-yA)
*/

signed main(){
    read(n);read(m);
	FOR(i,1,m){
        read(A[i].u);read(A[i].v);read(A[i].a);read(A[i].b);
		++A[i].u;++A[i].v;
	}
	FOR(i,1,m) e[i] = Edge(A[i].u,A[i].v,A[i].a,i);
	Kruskal();
	LL xA = 0,yA = 0;
	FOR(i,1,m) if(e[i].use) xA += A[e[i].id].a,yA += A[e[i].id].b;
	FOR(i,1,m) e[i] = Edge(A[i].u,A[i].v,A[i].b,i);
	Kruskal();
	LL xB = 0,yB = 0;
	FOR(i,1,m) if(e[i].use) xB += A[e[i].id].a,yB += A[e[i].id].b;
	work(xA,yA,xB,yB);
	printf("%lld %lld\n",ansx,ansy);
	return 0;
}
