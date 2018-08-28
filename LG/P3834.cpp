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

const int MAXN = 200000 + 5;

using std::map;
using std::make_pair;

int N,M,a[MAXN],origin[MAXN];
map<int,int> S;

struct Node{
	int cnt;
	Node *lc,*rc;
}pool[MAXN << 5],*frog = pool,*root[MAXN];

Node *New(){
	Node *ret = ++frog;
	ret->cnt = 0;
	ret->lc = ret->rc = NULL;
	return ret;
}

Node *insert(Node *prev,int l,int r,int pos){
	Node *v = New();
	if(prev){
		v->cnt = prev->cnt;
		v->lc = prev->lc;
		v->rc = prev->rc;
	}
	if(l == r){
		v->cnt++;
		return v;
	}
	int mid = (l + r) >> 1;
	if(pos <= mid) v->lc = insert(prev ? prev->lc : NULL,l,mid,pos);
	else v->rc = insert(prev ? prev->rc : NULL,mid + 1,r,pos);
	v->cnt++;
	return v;
}

int query(Node *lr,Node *rr,int l,int r,int k){
	if(l == r) return l;
	int ls = 0;
	if(rr && rr->lc) ls = rr->lc->cnt;
	if(lr && lr->lc) ls -= lr->lc->cnt;
	int mid = (l + r) >> 1;
	if(k <= ls) return query(lr ? lr->lc : NULL,rr ? rr->lc : NULL,l,mid,k);
	else return query(lr ? lr->rc : NULL,rr ? rr->rc : NULL,mid + 1,r,k - ls);
}

int main(){
	scanf("%d%d",&N,&M);
	S.clear();
	for(int i = 1;i <= N;i++){
		scanf("%d",a + i);
		S.insert(make_pair(a[i],0));
	}
	int tN = 0;
	for(map<int,int>::iterator it = S.begin();it != S.end();it++){
		it->second = ++tN;
		origin[tN] = it->first;
	}
	for(int i = 1;i <= N;i++)
		a[i] = S[a[i]];
	for(int i = 0;i < MAXN;i++)
		root[i] = NULL;
	for(int i = 1;i <= N;i++)
		root[i] = insert(root[i-1],1,tN,a[i]);
	while(M--){
		int l,r,k;
		scanf("%d%d%d",&l,&r,&k);
		printf("%d\n",origin[query(root[l-1],root[r],1,tN,k)]);
	}
	return 0;
}