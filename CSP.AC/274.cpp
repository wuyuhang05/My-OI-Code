#include <bits/stdc++.h>

#define fi first
#define se second
#define db double
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

const int MAXN = 1e6 + 5;
int len;
std::map<std::string,int> S;
std::string str;
int n;
int a[MAXN];
std::vector<int> G[MAXN];
int rk[MAXN],deg[MAXN],ts[MAXN];

struct Node{
    int ts,rk,id;
    Node(int ts=0,int rk=0,int id=0) : ts(ts),rk(rk),id(id) {}

    inline bool operator < (const Node &t) const {
        return MP(ts,rk) < MP(t.ts,t.rk);
    }
};

bool vis[MAXN];
int sa[MAXN];

int main(){
  //  freopen("B.in","r",stdin);
    std::ios::sync_with_stdio(false);
    std::cin >> str;
    int tt = 0;
    for(int l = 0,r = 0;str[l] != '/';l = r+1){
        r = l;
        while(str[r] != ';' && str[r] != '/') ++r;
        int p = l;
        while(str[p] != ':') ++p;
        std::string name = str.substr(l,p-l);
        S[name] = ++n;
        while(str[r] != ':') --r;
        ++r;
        while(str[r] != ';' && str[r] != '/') a[n] = a[n]*10+str[r]-'0',++r;
        if(str[r] == '/') break;
    }
    for(int i=1,l = 0,r = 0;str[l] != '/';l = r+1,++i){
        r = l;
        while(str[r] != ';' && str[r] != '/') ++r;
        int p = l;
        while(str[p] != '[') ++p;
        int q = l;
        while(str[q] != ']') ++q;
        for(int ll = p+1,rr = p+1;ll < q;ll = rr+1){
            rr = ll;
            while(str[rr] != ']' && str[rr] != ',') ++rr;
            int to = S[str.substr(ll,rr-ll)];
//            if(i == 89) DEBUG(to),DEBUG(str.substr(ll,rr-ll));
            G[to].pb(i);++deg[i];
            if(str[rr] == ']') break;
        }
        if(str[r] == '/') break;
    }
    int p = 0,lim = 0;
    while(str[p] != '/') ++p;++p;
    while(p < str.length()) lim = lim*10+str[p]-'0',++p;
    p = 1;
    for(auto x:S) rk[x.se] = p++;
    std::set<Node> tba;
    std::set<P> inw;
    FOR(i,1,n) sa[rk[i]] = i;
    FOR(i,1,n){
        if(!deg[sa[i]]){
            vis[sa[i]] = 1;
            if(inw.size() < lim) inw.insert(MP(a[sa[i]],sa[i]));
            else tba.insert(Node(0,rk[sa[i]],sa[i]));
        }
    }
    int ans = 0;
/*    std::vector<P> sfsf;
    FOR(v,1,n){
        for(auto x:G[v]){
            sfsf.pb(MP(rk[v],rk[x]));
        }
    }*/
    while(!inw.empty()){
        int las = -1;
        while(!inw.empty() && (las == -1 || las == inw.begin()->fi)){
            P t = *inw.begin();inw.erase(inw.begin());
            int v = t.se,w = t.fi;ans = std::max(ans,w);
            for(auto x:G[v]){
                --deg[x];
                if(!deg[x]){
                    tba.insert(Node(w,rk[x],x));
                    vis[x] = 1;
                }
            }
            las = w;
        }
        while(!tba.empty() && inw.size() < lim){
            inw.insert(MP(las+a[tba.begin()->id],tba.begin()->id));
            tba.erase(tba.begin());
        }
    }
    std::cout << ans << '\n';
    return 0;
}