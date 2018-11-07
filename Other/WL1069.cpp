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

const int MAXN = 300000+5;

struct SegmentTree *New(int ,int ,SegmentTree *,SegmentTree *);

struct SegmentTree{
	int l,r,sum,tag;
	SegmentTree *lc,*rc;
	
	static SegmentTree *build(int l,int r){
		int mid = (l + r) >> 1;
		return (l == r) ? New(l,r,NULL,NULL) : New(l,r,build(l,mid),build(mid+1,r));
	}
	
	inline void pushup(){
		sum = lc->sum + rc->sum; 
	}
	
	inline void clear(){
		sum = 0;tag = 1;
	}
	
	inline void pushdown(){
		if(tag){
			lc->clear();
			rc->clear();
			tag = 0;
		}
	}
	
	void modify(int L,int R){
		if(L == l && R == r){
			clear();
			return;
		} 
		pushdown();
		int mid = (l + r) >> 1;
		if(R <= mid) lc->modify(L,R);
		else if(L > mid) rc->modify(L,R);
		else lc->modify(L,mid),rc->modify(mid+1,R);
		pushup(); 
	} 
	
	void update(int pos){
		if(l == r){
			sum = 1;return;
		}
		int mid = (l + r) >> 1;
		if(pos <= mid) lc->update(pos);
		else rc->update(pos);
		pushup();
	}
}pool[MAXN<<1],*frog = pool,*segt;

SegmentTree *New(int l,int r,SegmentTree *lc,SegmentTree *rc){
	SegmentTree *ret = ++frog;
	ret->l = l;ret->r = r;ret->lc = lc;ret->rc = rc;
	ret->sum = ret->tag = 0;
	return ret; 
}

int N,Q,cnt;
std::vector<int> p[MAXN];

int main(){
	read(N);read(Q);
	segt = SegmentTree::build(1,Q);
	while(Q--){
		int opt,x;read(opt);read(x);
		if(!(opt-1)){ // 1
			p[x].push_back(++cnt);
			segt->update(cnt);
		}
		else if(opt&1){ // 3
			segt->modify(1,x);
		}
		else{ // 2
			FOR(i,0,(int)p[x].size()-1){
				//DEBUG(p[x][i]);
				segt->modify(p[x][i],p[x][i]);
			}
			p[x].clear();
		}
		printf("%d\n",segt->sum);
	}
	return 0;
}

