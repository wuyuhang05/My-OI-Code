#include <iostream>
#include <cstring>
#include <cstdio>
#include <queue>
#include <map>

std::string A,B;

struct BH{
    std::string from,to;
}b[10 + 5];

std::pair<std::string,int> p[1000 + 5];
int cnt,ans;
std::map<std::string,int> vis;

std::string trans(const std::string &str,int i,int j){
    std::string ans = "";
    if (i+b[j].from.length() > str.length())
        return ans;
    
    for (int k=0; k < b[j].from.length();k++)
        if (str[i+k] != b[j].from[k])
            return ans;
    
    ans = str.substr(0,i);
    ans+=b[j].to;
    ans+=str.substr(i+b[j].from.length());
    return ans;
}


void bfs(){
    std::queue<std::pair<std::string,int> > q;
    q.push(std::make_pair(A,0));
    while(!q.empty()){
        std::pair<std::string,int> u = q.front();
        q.pop();
        std::string temp;
        
        if(vis.count(u.first) == 1) continue;
        if(u.first == B){
            ans = u.second;
            return;
        }
        vis[u.first] = 1;
        for(int i = 0;i < u.first.length();i++){
            for(int j = 0;j < cnt;j++){
                temp = trans(u.first,i,j);
                if(temp != ""){
                    std::pair<std::string,int> v;
                    v.first = temp;
                    v.second = u.second + 1;
                    q.push(v);
                }
            }
        }
    }
}

int main(){
    std::cin >> A >> B;
    std::string x,y;
    while(std::cin >> b[cnt].from >> b[cnt].to)cnt++;
    bfs();
    if(ans == 0 || ans > 10){
        printf("%s\n","NO ANSWER!");
    }
    else printf("%d\n",ans);
    return 0;
}

