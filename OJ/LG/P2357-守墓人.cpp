#include <algorithm>
#include <iostream>
#include <cstring>
#include <climits>
#include <cstdlib>
#include <cstdio>
#include <cmath>
#include <queue>
#include <stack>
#include <map>
#include <set>
#define LL long long
#define DEBUG(x) std::cerr << #x << '=' << x << std::endl

LL N,F;
const int MAXN = 200000 + 10;

inline void Read(LL &x){
	x = 0;char ch = getchar();
	int flag = 1;
	for(;!isdigit(ch);ch = getchar())
		if(ch == '-') flag = -1;
	for(;isdigit(ch);ch = getchar())
		x = x * 10 + (ch ^ 48);
	x *= flag;
}

struct SegmentTree;

SegmentTree *New(LL,LL,SegmentTree*,SegmentTree*);

struct SegmentTree{
	LL l,r,sum,tag;
	SegmentTree *lc,*rc;

	static SegmentTree *build(LL l,LL r){
		LL mid = (l + r) >> 1;
		return (l == r) ? New(l,r,NULL,NULL) : New(l,r,build(l,mid),build(mid + 1,r));
	}

	void cover(LL delta){
		sum += (r - l + 1) * delta;
		tag += delta;
	}

	void pushup(){
		sum = lc->sum + rc->sum;
	}

	void pushdown(){
		if(tag){
			lc->cover(tag);
			rc->cover(tag);
			tag = 0;
		}
	}

	void update(LL pos,LL x){
		if(l == r){
			sum = x;tag = 0;
			return;
		}
		pushdown();
		LL mid = (l + r) >> 1;
		if(pos <= mid) lc->update(pos,x);
		else rc->update(pos,x);
		pushup();
	}

	void modify(LL left,LL right,LL delta){
		if(l == left && r == right){
			cover(delta);return;
		}
		pushdown();
		LL mid = (l + r) >> 1;
		if(right <= mid) lc->modify(left,right,delta);
		else if(left > mid) rc->modify(left,right,delta);
		else{
			lc->modify(left,mid,delta);
			rc->modify(mid + 1,right,delta);
		}
		pushup();
	}

	LL query(LL left,LL right){
		if(l == left && r == right){
			return sum;
		}
		pushdown();
		LL mid = (l + r) >> 1;
		if(right <= mid) return lc->query(left,right);
		else if(left > mid) return rc->query(left,right);
		else return lc->query(left,mid) + rc->query(mid + 1,right);
	}
}pool[MAXN * 4],*frog = pool,*segt;

SegmentTree *New(LL l,LL r,SegmentTree *lc,SegmentTree *rc){
	SegmentTree *ret = ++frog;
	ret->l = l;ret->r = r;
	ret->sum = 0;ret->tag = 0;
	ret->lc = lc;ret->rc = rc;
	return ret;
}

inline void show(){
	for(LL i = 1;i <= N;i++)
		printf("%d%c",segt->query(i,i),(i == N) ? '\n' : ' ');
}

int main(){
	Read(N);Read(F);
	//DEBUG(N);DEBUG(F);
	segt = SegmentTree::build(1,N);
	//show();
	for(int i = 1;i <= N;i++){
		LL x;
		Read(x);
		segt->update(i,x);
	}
	//show();
	for(int i = 1;i <= F;i++){
		LL opt;Read(opt);
		if(opt == 1){
			LL l,r,x;
			Read(l);Read(r);Read(x);
			segt->modify(l,r,x);
		}
		if(opt == 2){
			LL k;Read(k);
			segt->modify(1,1,k);
		}
		if(opt == 3){
			LL k;Read(k);
			segt->modify(1,1,-k);
		}
		if(opt == 4){
			LL l,r;Read(l);Read(r);
			printf("%lld\n",segt->query(l,r));
		}
		if(opt == 5){
			printf("%lld\n",segt->query(1,1));
		}
		//show();
	}
	getchar();getchar();
	return 0;
}