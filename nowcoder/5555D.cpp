#include<bits/stdc++.h>

#define fi first
#define se second
#define U unsigned
#define P std::pair<int,int>
#define LL long long
#define pb push_back
#define MP std::make_pair
#define all(x) x.begin(),x.end()
#define CLR(i,a) memset(i,a,sizeof(i))
#define FOR(i,a,b) for(int i = a;i <= b;++i)
#define ROF(i,a,b) for(int i = a;i >= b;--i)
#define DEBUG(x) std::cerr << #x << '=' << x << std::endl

const int MAXN = 1e5 + 5;

struct Node{
    int l,r,id;
    Node(int l=0,int r=-1,int id=-1) : l(l),r(r),id(id) {}
    bool operator < (const Node &t) const {
        return l < t.l;
    }
};
std::set<Node> S,G[MAXN];
int p[MAXN];

inline void cover(int l,int r,int id){
    auto it = S.upper_bound(Node(l,r,id));--it;
    if(it->l != l){
        Node t = *it;S.erase(it);
        G[t.id].erase(t);
        G[t.id].insert(Node(t.l,l-1,t.id));
        G[t.id].insert(Node(l,t.r,t.id));
        S.insert(Node(t.l,l-1,t.id));
        it = S.insert(Node(l,t.r,t.id)).fi;
    }
    while(it != S.end() && it->l <= r){
        if(it->r <= r){
            G[it->id].erase(*it);
            it = S.erase(it);
        }
        else if(it->l <= r){
            Node t = *it;G[t.id].erase(t);S.erase(it);
            G[t.id].insert(Node(r+1,t.r,t.id));S.insert(Node(r+1,t.r,t.id));
            break;
        }
        else break;
    }
    G[id].insert(Node(l,r,id));S.insert(Node(l,r,id));
}

inline bool merge(int x,int y){
    if(x == y) return 0;
    bool flag = 0;
    if(G[x].size() < G[y].size()) std::swap(x,y),flag = 1;
    for(auto it:G[y]){
        S.erase(it);it.id = x;
        G[x].insert(it);S.insert(it);
    }
    G[y].clear();
    return flag;
}

inline int qry(int i,int r,int id){
    if(G[id].empty()) return -1;
    int ans = -1;
    auto it = G[id].lower_bound(Node(i-r));
    if(it != G[id].end() && it->l <= i+r) ans = std::max(ans,std::abs(i-it->l));
    if(it != G[id].begin()){
        --it;if(it->r >= i-r) ans = r;
    }
    it = G[id].lower_bound(Node(i+r));
    if(it != G[id].end() && it->l == i+r) ans = r;
    else if(it != G[id].begin()){
        --it;
        if(it->r >= i+r) ans = r;
        else if(it->r >= i-r) ans = std::max(ans,std::abs(i-it->r));
    }
    return ans;
}

int main(){
    int n,q;scanf("%d%d",&n,&q);
    FOR(i,1,n) S.insert(Node(i,i,i)),G[i].insert(Node(i,i,i)),p[i] = i;
    FOR(i,1,q){
        char str[23];scanf("%s",str);
        if(str[0] == 'f'){
            int ps,r,id;scanf("%d%d%d",&ps,&r,&id);
            printf("%d\n",qry(ps,r,p[id]));
        }
        if(str[0] == 'r'){
            int x,y;scanf("%d%d",&x,&y);
            if(merge(p[x],p[y])) std::swap(p[x],p[y]);
        }
        if(str[0] == 'c'){
            int x,y,d;scanf("%d%d%d",&x,&y,&d);
            cover(x,y,p[d]);
        }
    }
    return 0;
}
