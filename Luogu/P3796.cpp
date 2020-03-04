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
#define ROF(i,a,b) for(Re int i = a;i >= b;--i)
#define CLR(i,a) memset(i,a,sizeof(i))
#define BR printf("--------------------\n")
#define DEBUG(x) std::cerr << #x << '=' << x << std::endl

const int MAXN = 100000+5;
const int MAXM = 26;

struct Node{
	int val;
	Node *next[MAXM],*fail;
}pool[MAXN],*frog = pool,*root;

Node *New(){
	Node *ret = ++frog;
	ret->val = 0;ret->fail = NULL;
	FOR(i,0,25) ret->next[i] = NULL;
	return ret;
}

void insert(char *str,int val){
	int len = strlen(str+1);
	Node *v = root;
	FOR(i,1,len){
		int x = str[i] - 'a';
		if(!v->next[x]) v->next[x] = New();
		v = v->next[x];
	}
	v->val = val;
}

void build(){
	std::queue<Node *> q;
	FOR(i,0,25){
		if(root->next[i]){
			q.push(root->next[i]);
			root->next[i]->fail = root;
		}
	}
	while(!q.empty()){
		Node *v = q.front();q.pop();
		FOR(i,0,25){
			if(v->next[i]){
				Node *t = v->fail;
				while(t){
					if(t->next[i]){
						v->next[i]->fail = t->next[i];
						break;
					}
					t = t->fail;
				}
				if(!t) v->next[i]->fail = root;
				q.push(v->next[i]);
			}
		}
	}
}

std::pair<int,int> ans[MAXN];

void query(char *str){
	int len = strlen(str+1);
	Node *v = root;
	FOR(i,1,len){
		int x = str[i] - 'a';
		while(!v->next[x] && v != root) v = v->fail;
		v = v->next[x];
		if(!v) v = root;
		Node *t = v;
		while(t != root){
			// if(t->val > 0) ans[t->val].first++;
			// else break;
			ans[t->val].first++;
			t = t->fail;
		}
	}
}

int N;
char str[2000][220];
char q[1000000+5];

bool cmp(const std::pair<int,int> &a,const std::pair<int,int> &b){
	return a.first == b.first ? a.second < b.second : a.first > b.first;
}

inline void init(){
	CLR(pool,0);frog = pool;
	root = New();CLR(ans,0);
	//CLR(q,0);CLR(str,0);
}
int cnt=0;
int main(){
	//freopen("testdata.in","r",stdin);
	//freopen("testdata.out","w",stdout);
	while(19260817){
		scanf("%d",&N);if(!N) break;
		init();
		FOR(i,1,N){
			scanf("%s",str[i]+1);
			ans[i] = std::make_pair(0,i);
			insert(str[i],i);
		}
		build();
		scanf("%s",q+1);
		query(q);
		std::sort(ans+1,ans+N+1,cmp);
		printf("%d\n",ans[1].first);
		printf("%s\n",str[ans[1].second]+1);
		FOR(i,2,N){
			if(ans[i].first == ans[i-1].first){
				printf("%s\n",str[ans[i].second]+1);
			}
			else break;
		}
	}
	return 0;
}
/*
10
qabqks
vimbirqy
cflwvxtp
klljfj
ab
nkeiid
fkypjfev
yvgp
evdhs
xaizql
qabqksatffqpjomzstjabfklljfjqevdhsqabqkscflwvxtpeevdhsmzonkeiid
*/
