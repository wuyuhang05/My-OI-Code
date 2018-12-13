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
const int MAXM = 4;

struct Node{
	Node *next[MAXM],*fail;
	int val;
}pool[MAXN<<1],*frog = pool,*root;

Node *New(){
	Node *ret = ++frog;
	ret->next[0] = ret->next[1] = ret->next[2] = ret->next[3] = NULL;
	ret->fail = NULL;ret->val = 0;
	return ret;
}

int getnum(char ch){
	return ch == 'A' ? 0 : (ch == 'G' ? 1 : (ch == 'C' ? 2 : 3));
}

void insert(char *str){
	int len = strlen(str+1);
	Node *v = root;
	FOR(i,1,len){
		int x = getnum(str[i]);
		if(!v->next[x]) v->next[x] = New();
		v = v->next[x];
	}
	v->val++;
}

void build(){
	std::queue<Node *> q;
	FOR(i,0,3){
		if(root->next[i]){
			root->next[i]->fail = root;
			q.push(root->next[i]);
		}
		else root->next[i] = root;
	}
	while(!q.empty()){
		Node *v = q.front();q.pop();
		FOR(i,0,3){
			if(v->next[i]){
				v->next[i]->fail = v->fail->next[i];
				v->next[i]->val |= v->fail->next[i]->val;
				q.push(v->next[i]);
			}
			else v->next[i] = v->fail->next[i];
		}
	}
}

void init(){
	frog = pool;
	root = New();
}

int N;
char str[MAXN];
int f[2][MAXN],size,caser;
const int INF = 0x3f3f3f3f;

void work(char *str,int len){
	int now = 0,pre = 1;
	CLR(f,0x3f);f[now][1] = 0;
	FOR(i,1,len){
		now ^= 1;pre ^= 1;
		CLR(f[now],0x3f);
		FOR(j,1,size){
			if(f[pre][j] < INF){
				Node *v = pool+j;
				FOR(k,0,3){
					if(v->next[k]->val) continue;
					int t = v->next[k]-pool;
					int add = getnum(str[i]) == k ? 0 : 1;
					f[now][t] = std::min(f[now][t],f[pre][j]+add);
				}
			}
		}
	}
	int ans = INT_MAX;
	FOR(i,1,size){
		ans = std::min(ans,f[now][i]);
	}
	printf("Case %d: %d\n",++caser,(ans == INF) ? -1 : ans);
}

int main(){
	while(~scanf("%d",&N) && N){
		init();
		FOR(i,1,N){
			scanf("%s",str+1);
			insert(str);
		}
		build();
		size = frog - pool+1;
		scanf("%s",str+1);
		int len = strlen(str+1);
		work(str,len);
	}
	return 0;
}