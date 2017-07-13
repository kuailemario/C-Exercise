#include<iostream>
#include<vector>
#define num 5
#define packet 10
using namespace std;
/*----------------------------
给定一个背包，其容量是10千克，5件物品，其重量分别是4，6，3，5，8公斤；
其价值分别是：9，3，6，13，15元，试根据贪心算法给出散装背包问题的最优解以及相应的求解过程。
------------------------------*/
int main()
{
    int weight[num]={4,6,3,5,8};
    int value[num]={9,3,6,13,15};
    double pervalue[num]; //计算单位价值(2.25, 0.5, 2, 2.6, 1.875)
    vector<int> pos; //对物品价值进行排序(3 2 0 4 1)
    pos.push_back(0);
    for(int i=0;i<num;i++)
    {
        pervalue[i]=value[i]*1.0/weight[i];
        //使用插入排序。
        vector<int>::iterator it=pos.begin();
        for(int j=0;j<i;j++)   // 0.5<2.25
            if (pervalue[i]>pervalue[pos[j]])
            { //pos价值从大到小
                pos.insert(it+j,i);
                break;
            }
            else if(j==i-1) pos.push_back(i);
    }
    cout<<"物品价值排序：";
    for(int i=0;i<num;i++)
        cout<<pos[i]+1<<"  ";
    cout<<endl;
    //开始装背包
    int tw = 0, tv = 0;
    for(int i=0;i<num;i++)
    {
        if ( tw + weight[pos[i]] < packet )
        {
            cout<<"物品 "<<pos[i]+1<<" 装满了背包\n";
            tv += value[pos[i]];
            tw += weight[pos[i]];
        }
        else
        {
            double deci = packet - tw;
            cout<<"物品 "<<pos[i]+1<<" 装了 "<<deci*1.0<<" 单位\n";
            tv += value[pos[i]] * deci * 1.0 / weight[pos[i]];
            break;
        }
    }
    cout<<"背包总价值："<<tv<<endl;
}
