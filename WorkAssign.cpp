#include<iostream>
using namespace std;

int **a = NULL;  //初始化二级指针
int bestval = 9999999;  //初始化最佳值

void calc(int x[],int n)
{
    int temp = 0;
    for(int i=1;i<=n;i++)
        temp += a[i][x[i]];
    if(temp<bestval)bestval = temp;
}

void BackTrack(int x[],int t,int n)
{
    if(t>n)
    {
        calc(x,n);
    }
    else for(int i=t; i<=n; i++)
        {
            swap(x[t],x[i]);
            BackTrack(x,t+1,n);
            swap(x[t],x[i]);
        }
}

int main()
{
    //假设4个工作分配给4个人，最佳解一定是1~4的一组排列，如2143。
    //因此，只要通过回朔法搜索排列数，从中取最小值即可。
    cout<<"请输入要给几个人分配工作？"<<endl;
    int num;
    cin>>num;
    int *arrange = new int[num+1]; //建立排列数组
    for(int i=1;i<=num;i++) arrange[i]=i; //初始化排列组合

    //申请空间
    a = new int *[num+1];
    for(int i = 1;i <= num;i++)
        a[i] = new int[num+1];

    for(int i=1; i<=num; i++)
        for(int j=1; j<=num; j++)
            cin>>a[i][j];   //i表示工作，j表示人，a[i][j]是费用
    BackTrack(arrange,1,num);
    cout<<bestval;
}
