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

const int MAXN = 3000000+5;
const int MAXM = 26;

struct Node{
	int sum;
	Node *next[26],*fail;
}pool[MAXN],*frog = pool,*root;

Node *New(){
	Node *ret = ++frog;
	ret->sum = 0;ret->fail = NULL;
	FOR(i,0,25) ret->next[i] = NULL;
	return ret;
}

void build(){
	std::queue<Node *> q;
	FOR(i,0,25){
		if(root->next[i]){
			root->next[i]->fail = root;
			q.push(root->next[i]);
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

void insert(char *str){
	Node *v = root;int len = strlen(str+1);
	FOR(i,1,len){
		int x = str[i] - 'a';
		if(!v->next[x]) v->next[x] = New();
		v = v->next[x];
	}
	v->sum++;
}

int query(char *str){
	int len = strlen(str+1),ans=0;
	Node *v = root;
	FOR(i,1,len){
		int x = str[i] - 'a';
		while(!v->next[x] && v != root) v = v->fail;
		v = v->next[x];
		if(!v) v = root;
		Node *t = v;
		while(t != root){
			if(t->sum >= 0){
				ans += t->sum;
				t->sum = -1;
			}
			else break;
			t = t->fail;
		}
	}
	return ans;
}

int N;
char str[MAXN];

int main(){
	root = New();scanf("%d",&N);
	FOR(i,1,N){
		scanf("%s",str+1);
		insert(str);
	}
	build();
	scanf("%s",str+1);
	printf("%d\n",query(str));
	return 0;
}
