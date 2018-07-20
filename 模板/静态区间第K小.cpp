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

using std::map;
using std::make_pair;

const int MAXN = 200000 + 5;

struct Node{
	int cnt; //记录以该节点为根的树的节点数
	Node *lc,*rc;
}*root[MAXN],pool[MAXN << 5],*frog = pool;
//静态开空间防止TLE

Node *New(){
	Node *ret = ++frog;
	ret->cnt = 0;
	ret->lc = ret->rc = NULL;
	return ret;
}

map<int,int> S; //离散化用
int N,M,a[MAXN],origin[MAXN];

Node *insert(Node *prev,int l,int r,int pos){ //prev表示未插入前的最新版本，l，r表示区间，pos表示单点修改的位置，也是要插入的值离散化后的数
	Node *v = New(); //新建一个版本上的节点
	if(prev){ //特判防止RE
		v->cnt = prev->cnt; 
		v->lc = prev->lc;
		v->rc = prev->rc;
	} //更新新版本的根节点
	if(l == r){ //找到该修改的点了
		v->cnt++; //统计点数量+1
		return v;
	}
	//如果还没有找到，进行折半查找。
	int mid = (l + r) >> 1; //折半
	if(pos <= mid) //去左子树查找
		v->lc = insert(prev ? prev->lc : NULL,l,mid,pos);
	if(pos > mid)
		v->rc = insert(prev ? prev->rc : NULL,mid + 1,r,pos);
	//注意特判NULL情况防止RE
	v->cnt++; //更新大小
	return v;
}

int query(Node *lr,Node *rr,int l,int r,int k){ //lr表示查询时区间左的根，rr表示查询时区间右的根，l，r表示查询区间，k表示将要查询该区间排名为k的树。
	if(l == r) return l; //由于进行了离散化，当查询到最后时，返回该点在线段树内的标号即可。
	int ls = 0; //ls记录左子树的大小
	if(rr->lc) ls = rr->lc->cnt; //统计左子树大小
	if(lr && lr->lc) ls -= lr->lc->cnt; //为了按照排名决定方向而去重
	int mid = (l + r) >> 1; //折半查找
	if(k <= ls)
		return query(lr ? lr->lc : NULL,rr ? rr->lc : NULL,l,mid,k);
	else return query(lr ? lr->rc : NULL,rr ? rr->rc : NULL,mid + 1,r,k-ls);
}

int main(){
	scanf("%d%d",&N,&M);
	S.clear();
	for(int i = 1;i <= N;i++){
		scanf("%d",a + i);
		S.insert(make_pair(a[i],0)); //初始化
	}
	int tN = 0; //离散化后的元素多少（map去重）
	for(map<int,int>::iterator it = S.begin();it != S.end();it++){
		it->second = ++tN; //map类型S中：first表示原来的数字，second表示离散化赋予它的编号
		origin[tN] = it->first; //记录离散化后的数字。
	}
	for(int i = 1;i <= N;i++)
		a[i] = S[a[i]]; //a[i]离散化完成
	for(int i = 0;i < MAXN;i++)
		root[i] = NULL; //初始化root
	for(int i = 1;i <= N;i++)
		root[i] = insert(root[i-1],1,tN,a[i]); //对于每次插入，建立一个新版本。
	while(M--){
		int l,r,k;
		scanf("%d%d%d",&l,&r,&k);
		printf("%d\n",origin[query(root[l-1],root[r],1,tN,k)]);
		//你可以感性理解主席树的历代版本相当于一个前缀和，树是可减的。
	}
	getchar();getchar();
	return 0;
}