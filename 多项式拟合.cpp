#include <iostream>
#include <cstdio>
#include <iomanip>
#include <cmath>
#define DATA 100 //最多可存储100组数据
#define POW 6 //最多可进行6-1=5次多项式拟合
using namespace std;
int print(double left[][POW],double right[],int k);
//多项式拟合，使用列主元消元法求解。

int main()
{
    // STEP[1] 输入数据
    double x[DATA],y[DATA];
    cout<<"请输入实验数据的个数"<<endl;
    int m;
    cin>>m;
    if(m>DATA)cerr<<"超出存储，Error!"<<endl;
    cout<<"请逐个输入实验数据xi,yi"<<endl;
    for(int i=0; i<m; i++)
        cin>>x[i]>>y[i];
    cout<<"请输入要进行几次多项式拟合"<<endl;
    int k;
    cin>>k;
    double left[POW][POW],right[POW]= {0}; //最多可进行5次多项式拟合
    if(k>POW)cerr<<"超出存储，Error!"<<endl;
    double xtemp[POW*2]= {0}; //用来计算累加

    // STEP[2] 建立法方程组
    for(int i=0; i<k*2; i++)
    {
        if(i<=k) for(int j=0; j<m; j++)
        {
            xtemp[i] += pow(x[j],i+1);
            right[i] += y[j] * pow(x[j],i);
        }
        else for(int j=0; j<m; j++)
            xtemp[i] += pow(x[j],i+1);
    }
    for(int i=0; i<=k; i++)
        for(int j=0; j<=k; j++)
        {
            if(i+j!=0)left[i][j] = xtemp[i+j-1];
        }
    left[0][0] = m;

    double answer[POW];
    //STEP[3] 使用列主元消元法求解
    for(int source=0; source<k; source++)
    {
        double max = -99999;
        int maxl = source;
        for(int line=source; line<k+1; line++)
        {
            if (fabs(left[line][source])>max)
            {  max=left[line][source];  maxl=line; }
        }
        if(maxl!=source)
        {
            double temp,tmp;
            for(int g=0;g<k+1;g++)
            {
                temp = left[maxl][g];
                left[maxl][g] = left[source][g];
                left[source][g] = temp;
            }
            tmp=right[maxl];
            right[maxl]=right[source];
            right[source]=tmp;
        }
        cout<<"       列主元更新中。"<<endl;
        print(left,right,k);
        for(int line=source+1; line<k+1; line++)
        {
            if(left[source][source]==0){
                cerr<<"错误！主元出现0，无法消元！<<endl;";
                return 0;
            }
            double divide = left[line][source]/left[source][source];
            for(int minu = source; minu < k+1; minu++)
                left[line][minu] -= left[source][minu] * divide;
            right[line] -= right[source] * divide;
            print(left,right,k);
        }
    }
    //回溯
    cout<<"--------------STEP2------------------"<<endl;
    for(int line = k; line>=0; line--)
    {
        answer[line] = right[line]/left[line][line];
        cout<<"x"<<line<<"  =  "<<answer[line]<<endl;
        for(int i=0; i<line; i++)
        {
            right[i]-=answer[line]*left[i][line];
            left[i][line]=0;
            print(left,right,k);
        }
    }
    cout<<endl;

    //这里只写了到三次的输出。
    if(k==3)
        printf(" Y = %.4f + %.4f X + %.4f X^2 + %.4f X^3 ",
               answer[0],answer[1],answer[2],answer[3]);
    else if(k==2)
        printf(" Y = %.4f + %.4f X + %.4f X^2  ",
               answer[0],answer[1],answer[2]);
    else if(k==1)
        printf(" Y = %.4f + %.4f X ",
               answer[0],answer[1]);
}

int print(double left[][POW],double right[],int k)
{
    for(int i=0; i<k+1; i++)
    {
        for(int j=0; j<k+1; j++)
        {
            cout.setf(ios::fixed);
            cout<<setw(12)<<setprecision(4)<<left[i][j];
            cout<<' ';
        }
        cout<<"  ]  "<<right[i]<<endl;
    }
    cout<<endl;
}
