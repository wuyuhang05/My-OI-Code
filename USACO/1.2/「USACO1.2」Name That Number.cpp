/*
ID:wuyuhan5
LANG:C++
TASK:namenum
*/
#include<cstdio>
#include<cstring>
//#include<map>
using namespace std;
//map<string,bool>vis;
char s[15],test[15];
char str[531441][13],now[15];
char dic[9][4]={"ABC","DEF","GHI","JKL","MNO","PRS","TUV","WXY"};
int cnt=0,n,m=0;

bool find()
{
    int l=0,r=m-1;
    while(l<=r)
    {
        int mid=l+(r-l)/2;
        int temp=strcmp(str[mid],test);
        if(temp<0)l=mid+1;
        else if(temp>0)r=mid-1;
        else if(temp==0)
        {
            cnt=1;
            return true;
        }
    }
    return false;
}

void dfs(int step)
{
    if(step>=n)
    {
        now[step]='\0';
        strcpy(str[m++],now);
        //printf("%s\n",str[m-1]);
    }else {
        for(int i=0;i<3;i++)
        {
            now[step]=dic[s[step]-'2'][i];
            dfs(step+1);
        }
    }


}
int main()
{

    freopen("namenum.in","r",stdin);
    freopen("namenum.out","w",stdout);
    scanf("%s",s);

    n=strlen(s);
        dfs(0);
    freopen("dict.txt","r",stdin);
    while(scanf("%s",test)!=EOF){
        if(find())printf("%s\n",test);
    }
    if(cnt==0)printf("NONE\n");
    return 0;
}
