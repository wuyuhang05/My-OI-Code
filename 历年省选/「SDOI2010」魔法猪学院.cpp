#include <algorithm>
#include <cstdio>
#include <queue>

const int MAXN = 5000 + 2;

#define INF 0x7f7f7f7f
double dist[MAXN];
bool inQueue[MAXN];
int ans;

struct Node{
    int num;
    struct Edge{
        Node *s,*t;
        double w;
        Edge *next;

        Edge(Node *s,Node *t,double w) : s(s), t(t), w(w), next(s->firstEdge) {}

    };
    Edge *firstEdge;
}node[MAXN],_node[MAXN];

struct data{
    Node *v;
    double h,f;
    bool operator < (const data &a) const {
        if(f > a.f) return 1;
        return 0;
    }
}t1,t2;

void add(int u,int v,double w){
    node[u].firstEdge = new Node::Edge(&node[u],&node[v],w);
    _node[v].firstEdge = new Node::Edge(&_node[v],&_node[u],w);
}

void Read(int &x){
    char ch = getchar();
    int ret = 0,flag = 1;
    while(ch < '0' || ch > '9'){
        if(ch == '-') flag = -1;
        ch = getchar();
    }
    while(ch >= '0' && ch <= '9'){
        ret = (ret << 1) + (ret << 3) + ch - '0';
        ch = getchar();
    }
    x = ret * flag;
}

void init(int N){
    for(int i = 1;i <= N;i++){
        node[i].num = _node[i].num = i;
    }
}

void spfa(int N){
    std::queue<Node *> q;
    for(int i = 1;i < N;i++){
        dist[i] = INF;
        inQueue[i] = false;
    }
    q.push(&_node[N]);
    inQueue[_node[N].num] = true;
    while(!q.empty()){
        Node *v = q.front();q.pop();
        inQueue[v->num] = false;
        for(Node::Edge *e = v->firstEdge;e;e = e->next){
            if(dist[e->t->num] > dist[v->num] + e->w){
                dist[e->t->num] = dist[v->num] + e->w;
                if(!inQueue[e->t->num]){
                    inQueue[e->t->num] = true;
                    q.push(e->t);
                }
            }
        }
    }
}

int tot[MAXN];
void A_star(double &W,int k,int N){
    std::priority_queue<data> q;
    if(dist[1] == INF) return;
    t1.v = &node[1];t1.h = 0;t1.f = 0;
    q.push(t1);
    while(!q.empty()){
        t1 = q.top();
        q.pop();
        if(t1.f > W) return;
        Node *v = t1.v;
        tot[v->num]++;
        if(v->num == N){
            W -= t1.f;ans++;continue;
        }
        if(tot[v->num] > k) continue;
        for(Node::Edge *e = v->firstEdge;e;e = e->next){
            t2.v = e->t;t2.h = t1.h + e->w;t2.f = t2.h + dist[e->t->num];
            q.push(t2);
        }
    }
}

int main(){
    int N,M;double W;
    Read(N);Read(M);
    scanf("%lf",&W);
    init(N);
    for(int i = 1;i <= M;i++){
        int x,y;double z;
        Read(x);Read(y);
        scanf("%lf",&z);
        add(x,y,z);
    }
    spfa(N);
    A_star(W,W/dist[1],N);
    printf("%d",ans);
    return 0;
}
