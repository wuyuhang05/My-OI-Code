/*
d = (xa-xb)^2+(ya-yb)^2
01010101
10101010
01010101
10101010
�����̷��飬0Ϊ�׸�1Ϊ�ڸ�
    ͬ��������(xa-xb)����,��ô(ya-yb)��Ϊ����
                 (xa-xb)ż��,��ô(ya-yb)��Ϊż��
                 ���� d ���ض���ż�� 
    ����������(xa-xb)����,��ô(ya-yb)��Ϊż��
                 (xa-xb)ż��,��ô(ya-yb)��Ϊ����
                ���� d ���ض������� 
���һ�β���,�ֳ����ĵ㶼��ͬһ�飬
�ͷ�������ۣ�����������ϵ��(0,0)����(0,-1)Ϊ������ת45�ȣ����ظ��������� 
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
            if(((p[1].first+p[1].second)%2+2)%2==1){//��(0,-1)Ϊ������ת 
                for(int i=1;i<=n;i++){
                    int a = p[i].first - (p[i].second+1);
                    int b = p[i].first + (p[i].second+1);
                    p[i].first = a / 2;
                    p[i].second = b / 2;
                }
            }
            else{//��(0,0)Ϊ������ת  
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

