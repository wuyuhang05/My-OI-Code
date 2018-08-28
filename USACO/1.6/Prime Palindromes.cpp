/*
ID: wuyuhan5
PROB: pprime
LANG: C++
*/
#include <algorithm>
#include <iostream>
#include <cstring>
#include <climits>
#include <cstdio>
#include <cstdlib>
#include <vector>
#include <cmath>
#include <queue>
#include <stack>
#include <map>
#include <set>
#include <bitset>

#define R register
#define LL long long
#define U unsigned
#define FOR(i,a,b) for(R int i = a;i <= b;++i)
#define RFOR(i,a,b) for(R int i = a;i >= b;--i)
#define CLR(i,a) memset(i,a,sizeof(i))
#define BR printf("--------------------\n")
#define DEBUG(x) std::cerr << #x << '=' << x << std::endl

using namespace std;
bool prime(int x)
{
    bool b=true;
    for(int i=2;i<=sqrt(x);i++)
    {
        if(x%i==0)
            b=false;
    }
    return b;
}//判断质数的函数
int main()
{
    freopen("pprime.in","r",stdin);
    freopen("pprime.out","w",stdout);
    int a,b;
    int c[100000];
    int i=3;
    int d1,d2,d3,d4,d5;
    c[0]=5;c[1]=7;c[2]=11;//2位数和1位数只有这三个是回文质数
    for(d1=1;d1<=9;d1+=2)
        for(d2=0;d2<=9;d2++)
        {
            c[i]=d1*100+d2*10+d1;
            i++;
        }//生成3位回文数
    for(d1=1;d1<=9;d1+=2)
        for(d2=0;d2<=9;d2++)
            for(d3=0;d3<=9;d3++)
            {
                c[i]=d1*10000+d2*1000+d3*100+d2*10+d1;
                i++;
            }//生成5位回文数
    for(d1=1;d1<=9;d1+=2)
        for(d2=0;d2<=9;d2++)
            for(d3=0;d3<=9;d3++)
                for(d4=0;d4<=9;d4++)
                {
                    c[i]=d1*1000000+d2*100000+d3*10000+d4*1000+d3*100+d2*10+d1;
                    i++;
                }//生成7位回文数
    for(d1=1;d1<=9;d1+=2)
        for(d2=0;d2<=9;d2++)
            for(d3=0;d3<=9;d3++)
                for(d4=0;d4<=9;d4++)
                    for(d5=0;d5<=9;d5++)
                    {
                        c[i]=d1*100000000+d2*10000000+d3*1000000+d4*100000+d5*10000+d4*1000+d3*100+d2*10+d1;
                        i++;
                    }//生成9位回文数
    cin>>a>>b;//输入范围
    for(int i=0;i<100000000;i++)
    {
        if(c[i]>=a&&c[i]<=b&&prime(c[i])==true)
        {
            cout<<c[i]<<endl;
        }//判断回文数是否是质数
        if(c[i]>b)
            break;//当超出范围时及时退出循环
    }
}
