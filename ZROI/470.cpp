/*
MDZZ 线段树被出题人 艹 死 
*/
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
const int MAXN = 300000 +5;
int ans = 0;
int N;

//struct SegmentTree *New(int ,int ,SegmentTree *,SegmentTree *);
//
//struct SegmentTree{
//	int l,r,min,sum,tag;
//	SegmentTree *lc,*rc;
//	
//	static SegmentTree *build(int l,int r){
//		int mid = (l + r) >> 1;
//		return (l == r) ? New(l,r,NULL,NULL) : New(l,r,build(l,mid),build(mid+1,r));
//	}
//	
//	void pushup(){
//		sum = lc->sum + rc->sum;
//		min = std::min(lc->min,rc->min);
//	}
//	
//	void cover(int delta){
//		sum += (r-l+1)*delta;
//		min += delta;
//		tag += delta;
//	}
//	
//	void pushdown(){
//		if(tag){
//			lc->cover(tag);
//			rc->cover(tag);
//			tag = 0;
//		}
//	}
//	
//	inline int calc(int pos){
//		if(l == r) return sum;
//		pushdown();
//		int mid = (l + r) >> 1;
//		if(pos <= mid) return lc->calc(pos);
//		return rc->calc(pos);
//	}
//	
//	void modify(int L,int R,int delta){
//		if(L == l && R == r){
//			cover(delta);
//			return;
//		}
//		pushdown();
//		int mid = (l + r) >> 1;
//		if(R <= mid) lc->modify(L,R,delta);
//		else if(L > mid) rc->modify(L,R,delta);
//		else lc->modify(L,mid,delta),rc->modify(mid+1,R,delta);
//		pushup();
//	}
//}pool[MAXN<<2],*frog = pool,*segt;
//
//SegmentTree *New(int l,int r,SegmentTree *lc,SegmentTree *rc){
//	SegmentTree *ret = ++frog;
//	ret->l = l;ret->r = r;ret->lc = lc;ret->rc = rc;
//	ret->sum = ret->min = ret->tag = 0;
//	return ret; 
//}

struct BIT{
	static const int SIZE = 600000 + 5;
	#define lowbit(x) x&-x
	int tree[SIZE];
	void add(int pos,int val){
		while(pos <= SIZE){
			tree[pos] += val;
			pos += lowbit(pos);
		}
	}
	
	int calc(int pos){
		int ret = 0;
		while(pos){
			ret += tree[pos];
			pos -= lowbit(pos);
		}
		return ret;
	} 
}bit;

inline bool check(int L,int R){
//	int x = segt->calc(L);
	int x = bit.calc(L);
	return R-L+1-x <= 0;
}

std::vector<int> q[MAXN];
int x,y;
 
int main(){
	//freopen("in.txt","r",stdin);
	read(N);
	FOR(i,1,N){
		read(x);read(y);
		q[y].push_back(x);
	}
	//segt = SegmentTree::build(1,N);
	int cnt = N;
	ROF(R,N,1){
		if(q[R].size()){
			FOR(i,0,(int)q[R].size()-1){
				//segt->modify(q[R][i],R,1);
				bit.add(q[R][i],1);
			}
		}
		int l = 1,r = R,L=1;
		while(l <= r){
			int mid = (l + r) >> 1;
			if(check(mid,R)) r=mid-1,L=mid;
			else l=mid+1; 
		}
		ans = std::max(ans,std::min(R-L+1,bit.calc(L)));
		ans = std::max(ans,std::min(R-L+1,bit.calc(L-1)));
	}
	printf("%d\n",ans);
	return 0;
}
/*
20
13 16
3 17
1 6
16 20
3 13
10 13
5 19
3 20
5 7
15 16
10 16
9 20
1 13
14 16
6 11
3 4
3 11
1 14
10 11
10 13

*/ 
/*
5
3 5
2 5
1 5
1 5
4 5

*/

