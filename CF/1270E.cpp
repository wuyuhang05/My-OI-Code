/*
d = (xa-xb)^2+(ya-yb)^2
01010101
10101010
01010101
10101010
按棋盘分组，0为白格，1为黑格
    同组的情况：(xa-xb)奇数,那么(ya-yb)必为奇数
                 (xa-xb)偶数,那么(ya-yb)必为偶数
                 所以 d 最后必定是偶数 
    异组的情况：(xa-xb)奇数,那么(ya-yb)必为偶数
                 (xa-xb)偶数,那么(ya-yb)必为奇数
                所以 d 最后必定是奇数 
如果一次不够,分出来的点都在同一组，
就分情况讨论，将整个坐标系以(0,0)或者(0,-1)为中心旋转45度，再重复上述过程 
*/

#include<bits/stdc++.h>
using namespace std;
#define N 2005
#define ll long long

pair<ll,ll>p[N];
set<ll> s[2],t[2];

int main(){
    int n;cin>>n;
    for(int i=1;i<=n;i++){
        cin>>p[i].first>>p[i].second;
    }
    if(n==2){
        puts("1");
        puts("1");
        return 0;
    }
    
    
    while(1){ 
        for(int i=1;i<=n;i++)
            s[((p[i].first+p[i].second)%2+2)%2].insert(i);
        for(int i = 1;i <= n;++i) printf("%d %d\n",p[i].first%2,p[i].second%2);
        if(s[0].size() && s[1].size())break;
        else {
            if(((p[1].first+p[1].second)%2+2)%2==1){//以(0,-1)为中心旋转 
                for(int i=1;i<=n;i++){
                    int a = p[i].first - (p[i].second+1);
                    int b = p[i].first + (p[i].second+1);
                    p[i].first = a / 2;
                    p[i].second = b / 2;
                }
            }
            else{//以(0,0)为中心旋转  
                for(int i=1;i<=n;i++){
                    int a = p[i].first + p[i].second;
                    int b = p[i].first - p[i].second;
                    p[i].first = a / 2;
                    p[i].second = b / 2;
                } 
            } 
        }
        s[0].clear();
        s[1].clear();
    } 
        
    cout<<s[1].size();
    puts("");
    for(auto x:s[1])cout<<x<<" ";
    
}

