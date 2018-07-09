#include <iostream>
#include <cstring>
#include <climits>
#include <cstdio>
#include <queue>
const int MAXN = 3000 + 5;
const int MAXM = 2000 + 5;
int N, K, x, y;
int a[MAXN];
bool flag[100000 + 5];
struct Node;
struct Edge;
Edge *New(Node*, Node*, int);
struct Node {
	Edge *firstEdge;
	int dist;
	bool inQueue;
}node[MAXM];
struct Edge {
	Node *s, *t;
	int w;
	Edge *next;
}pool[MAXM * 2],*frog = pool;
Edge *New(Node *u, Node *v, int w) {
	Edge *ret = ++frog;
	ret->s = u; ret->t = v;
	ret->w = w;
	ret->next = u->firstEdge;
	return ret;
}
inline void add(int u, int v, int w) {
	node[u].firstEdge = New(&node[u], &node[v], w);
	node[v].firstEdge = New(&node[v], &node[u], w);
}
inline void clear() {
	memset(pool, NULL, sizeof(pool));
	memset(node, NULL, sizeof(node));
	frog = pool;
}
inline void Read(int &x) {
	char ch = getchar();
	int flag = 1;
	for (x = 0; !isdigit(ch); ch = getchar())
		if (ch == '-') flag = -1;
	for (; isdigit(ch); ch = getchar())
		x = (x << 1) + (x << 3) + ch - '0';
	x *= flag;
}
int spfa(int S, int T, int N) {
	std::queue<Node *> q;
	for (int i = 1; i <= N; i++) {
		node[i].dist = INT_MAX;
		node[i].inQueue = false;
	}
	node[S].dist = 0;
	node[S].inQueue = true;
	q.push(&node[S]);
	while (!q.empty()) {
		Node *v = q.front();
		q.pop();
		v->inQueue = false;
		for (Edge *e = v->firstEdge; e; e = e->next) {
			if (e->t->dist > v->dist + e->w) {
				e->t->dist = v->dist + e->w;
				if (!e->t->inQueue) {
					e->t->inQueue = true;
					q.push(e->t);
				}
			}
		}
	}
	return node[T].dist;
}
int gcd(int a, int b) {
	return a == 0 ? b : gcd(b % a, a);
}
void getnum(int &ret) {
	clear();
	int N, M, K;
	Read(N); Read(M); Read(K);
	for (int u, v, w, i = 1; i <= M; i++) {
		Read(u); Read(v); Read(w);
		add(u, v, w);
	}
	ret = K - spfa(1, N, N);
}
int main() {
	Read(N); Read(K);
	for (int i = 1; i <= N; i++) {
		getnum(a[i]);
		flag[a[i]] = true;
	}
	for (int i = 1; i <= N; i++)
		for (int j = 1; j <= N; j++)
			for (int k = 1; k <= N; k++)
				if (a[i] + a[j] + a[k] == K) x++;
	y = N * N * N;
	int yf = gcd(x, y);
	printf("%d/%d", x / yf, y / yf);
	return 0;
}
