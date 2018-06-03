#include<cstdio>
#include<cstring>
#include<algorithm>
using namespace std;
const int N = 10003;
const int M = 50003;
void read(int &k) {
    k = 0; int fh = 1; char c = getchar();
    for(; c < '0' || c > '9'; c = getchar())
        if (c == '-') fh = -1;
    for(; c >= '0' && c <= '9'; c = getchar())
        k = (k << 1) + (k << 3) + c - '0';
    k = k * fh;
}

bool vis[N], inst[N];
struct node {int from, nxt, to;} E[M];
int DFN[N], low[N], point[N], cnt = 0, col[N], color = 0, st[N], top = 0, n, m, out[N], sum[N];
void tarjan(int x) {
    DFN[x] = low[x] = ++cnt;
    st[++top] = x; vis[x] = inst[x] = 1;
    for(int tmp = point[x]; tmp; tmp = E[tmp].nxt)
        if (!vis[E[tmp].to]) tarjan(E[tmp].to), low[x] = min(low[x], low[E[tmp].to]);
        else if (inst[E[tmp].to]) low[x] = min(low[x], DFN[E[tmp].to]);
    if (low[x] == DFN[x]) {
        int u = 0; ++color;
        while (u != x) {
            u = st[top--];
            col[u] = color;
            inst[u] = 0;
            ++sum[color];
        }
    }
}
void ins(int x, int y) {E[++cnt] = (node) {x, point[x], y}; point[x] = cnt;}
int main() {
    read(n); read(m);
    int u, v;
    for(int i = 1; i <= m; ++i) read(u), read(v), ins(u, v);
    cnt = 0;
    for(int i = 1; i <= n; ++i) if (!vis[i]) tarjan(i);
    for(int i = 1; i <= m; ++i) {
        u = col[E[i].from]; v = col[E[i].to];
        if (u != v) ++out[u];
    }
    int ans = 0, tmp = 0;
    for(int i = 1; i <= color; ++i) if (sum[i] > 1) ++tmp;
    for(int i = 1; i <= color; ++i) {
        if (out[i] == 0) {
            if (ans != 0 || sum[i] == 1) {ans = 0; break;}
            else ans = i;
        }
    }
    printf("%d\n", tmp);
    if (ans == 0) puts("-1");
    else {
        for(int i = 1; i <= n; ++i)
            if (col[i] == ans)
                printf("%d ", i);
    }
    return 0;
}
