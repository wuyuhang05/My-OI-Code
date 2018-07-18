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

const int MAXN = 100000 + 5;
LL N,M,ha;

inline void Read(LL &x){
	x = 0;LL flag = 1;
	char ch = getchar();
	for(;!isdigit(ch);ch = getchar())
		if(ch == '-') flag = -1;
	for(;isdigit(ch);ch = getchar())
		x = (x << 1) + (x << 3) + ch - '0';
	x *= flag;
}

struct SegmentTree;
SegmentTree *New(LL ,LL ,SegmentTree *,SegmentTree *);

struct SegmentTree{
	LL l,r,sum,tag1,tag2; //tag1:+;tag2:*;
	SegmentTree *lc,*rc;

	static SegmentTree *build(LL l,LL r){
		LL mid = (l + r) >> 1;
		return (l == r) ? New(l,r,NULL,NULL) : New(l,r,build(l,mid),build(mid + 1,r));
	}

	void pushup(){
		sum = (lc->sum + rc->sum) % ha;
	}

	void cover1(LL delta){
		tag1 = (tag1 + delta) % ha;
		sum = (sum + (r - l + 1) * delta) % ha;
	}

	void cover2(LL delta){
		sum = (sum * delta) % ha;
		tag1 = (tag1 * delta) % ha;
		tag2 = (tag2 * delta) % ha;
	}

	void pushdown(){
		lc->cover2(tag2);lc->cover1(tag1);
		rc->cover2(tag2);rc->cover1(tag1);
		tag1 = 0;tag2 = 1;
	}

	void modify1(LL left,LL right,LL delta){
		if(l == left && r == right){
			cover1(delta);return;
		}
		pushdown();
		LL mid = (l + r) >> 1;
		if(right <= mid) lc->modify1(left,right,delta);
		else if(left > mid) rc->modify1(left,right,delta);
		else{
			lc->modify1(left,mid,delta);
			rc->modify1(mid + 1,right,delta);
		}
		pushup();
	}

	void modify2(LL left,LL right,LL delta){
		if(l == left && right == r){
			cover2(delta);return;
		}
		pushdown();
		LL mid = (l + r) >> 1;
		if(right <= mid) lc->modify2(left,right,delta);
		else if(left > mid) rc->modify2(left,right,delta);
		else{
			lc->modify2(left,mid,delta);
			rc->modify2(mid + 1,right,delta);
		}
		pushup();
	}

	LL query(LL left,LL right){
		if(l == left && r == right)
			return sum;
		pushdown();
		LL mid = (l + r) >> 1;
		if(right <= mid) return lc->query(left,right);
		else if(left > mid) return rc->query(left,right);
		else
			return (lc->query(left,mid) + rc->query(mid + 1,right)) % ha;
	}
}pool[MAXN * 4],*frog = pool,*segt;

SegmentTree *New(LL l,LL r,SegmentTree *lc,SegmentTree *rc){
	SegmentTree *ret = ++frog;
	ret->l = l;ret->r = r;
	ret->lc = lc;ret->rc = rc;
	ret->sum = ret->tag1 = 0;
	ret->tag2 = 1;
	return ret;
}

inline void DEBUG(){
	printf("DEBUG MESSAGE:  ");
	for(int i = 1;i <= N;i++)
		printf("%lld%c",segt->query(i,i),(i == N) ? '\n' : ' ');
}

int main(){
	Read(N);Read(ha);
	segt = SegmentTree::build(1,N);
	for(LL x,i = 1;i <= N;i++){
		Read(x);segt->modify1(i,i,x);
	}
	Read(M);
	for(LL delta,opt,x,y,i = 1;i <= M;i++){
		//DEBUG();
		Read(opt);Read(x);Read(y);
		if(opt == 1){
			Read(delta);
			segt->modify2(x,y,delta);
		}
		if(opt == 2){
			Read(delta);
			segt->modify1(x,y,delta);
		}
		if(opt == 3){
			printf("%lld\n",segt->query(x,y));
		}
	}
	getchar();getchar();
	return 0;
}