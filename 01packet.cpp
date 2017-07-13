#include<iostream>
using namespace std;
#define num 5 //物品种类
#define packet 10 //背包大小
int main()
{
    /*           给定一个背包，其容量是10千克，5件物品，
    其重量分别是4，6，3，5，8公斤；其价值分别是：9，3，6，13，15元，
    试根据动态规划算法给出0-1背包问题的最优解以及相应的求解过程。  */

    int weight[num]={4,6,3,5,8};
    int value[num]={9,3,6,13,15};
    int current[num+1][packet+1]; //构建一张价值表。
    for(int i=0;i<=num;i++)
        current[i][0]=0;
    for(int i=0;i<=packet;i++)
        current[0][i]=0; //初始化价值表
    for(int i=1;i<=num;i++) //五种物品
        for(int j=1;j<=packet;j++)  //背包容量为10
        {
            if(j<weight[i]) current[i][j]=current[i-1][j];
            else {
                int a = current[i-1][j];
                int b = current[i-1][j-weight[i]] + value[i];
                current[i][j] = ( a>b ? a : b);
            }
        }
    cout<<"背包最大价值："<<current[num][packet]<<endl;
    int i=num,j=packet;
    while(i>0)
    {
        if(current[i][j]==current[i-1][j]) //价值相等，没装
            i--;
        else if( j-weight[i]>=0 && current[i][j]==current[i-1][j-weight[i]]+value[i] )
        {
            cout<<"第"<<i<<"号物品被装入，价值"<<value[i]<<"，重量"<<weight[i]<<endl;
            i--;
            j-=weight[i];
        }
    }
}
