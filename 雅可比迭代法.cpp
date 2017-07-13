#include<iostream>
#include <iomanip>
#include <cmath>
#include <fstream>
#define ROW 6  // *** 请在此处输入未知变量个数 ***
using namespace std;
/*-----程序中出现的变量-----
A                   系数矩阵
b                 常数项向量
Xk            当前未知项向量
Xkp         下一步未知项向量
LU                  迭代矩阵
d                   误差精度
---------------------------*/

double Jacobi(double A[ROW][ROW], double b[ROW])
{
    ofstream outfile("save.txt",ios::app); //添加在文件末尾
    //STEP[1] 将系数矩阵分解
    double D[ROW]={0}; //对角矩阵
    double LU[ROW][ROW]={0}; //上下三角
    for(int i=0;i<ROW;i++)
        for(int j=0;j<ROW;j++)
        {
            if(j==i) D[j]+=A[i][j];
            else LU[i][j]-=A[i][j];
        }
    //STEP[2] 计算迭代矩阵和常数
    for(int i=0;i<ROW;i++)
    {
        for(int j=0;j<ROW;j++)
            LU[i][j]/=D[i];
        b[i]/=D[i];
    }
    //STEP[3] 开始迭代过程
    int num = 0;
    double xk[ROW]={0}; //取迭代初值x为0
    double d=1;
    while(d>0.0001)
    {
        d=0;
        double xkp[ROW]={0}; //要计算的近似解
        outfile<<"第"<<num<<"次迭代\n";
        for(int i=0;i<ROW;i++)
        {
            for(int j=0;j<ROW;j++)
                xkp[i] += LU[i][j] * xk[i];
            xkp[i] += b[i];
            outfile<<setw(8)<<xkp[i]<<' ';
        }
        for(int i=0; i<ROW; i++)
        {
            double div = xkp[i]-xk[i];
            div *= div;
            d += div;
            xk[i] = xkp[i];
        }
        d = sqrt(d);
        outfile<<" d = "<<d;
        num++;
        outfile<<endl;
    }
}

int main()
{
    ofstream outfile("save.txt",ios::app); //添加在文件末尾
    double A[ROW][ROW] = {0};
    double b[ROW] = {0};
    cout<<"请按行输入系数矩阵\n";
    for(int i=0;i<ROW;i++)
        for(int j=0;j<ROW;j++)
            cin>>A[i][j];
    cout<<"请输入常数项向量\n";
    for(int i=0;i<ROW;i++)
        cin>>b[i];
    cout<<"开始进行雅可比迭代\n";
    Jacobi(A,b);
    cout<<"结果已经保存在save.txt\n";
    return 0;
}
