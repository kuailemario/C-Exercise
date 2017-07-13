#include <iostream>
#include <iomanip>
#include <cmath>
#define LINE 2 //行数
#define ROW 2 //列数
using namespace std;
int print(double left[][ROW],double right[])
{
    for(int i=0;i<LINE;i++)
    {
        for(int j=0;j<ROW;j++)
        {
            cout.setf(ios::fixed);
            cout<<setw(12)<<setprecision(4)<<left[i][j];
            cout<<' ';
        }
        cout<<"  ]  "<<right[i]<<endl;
    }
    cout<<endl;
}
int main()
{
    double left[LINE][ROW];
    double right[LINE],answer[LINE];
    //读取线性方程组
    cout<<"请按行输入线性方程组，回车执行。"<<endl;
    for(int i=0;i<LINE;i++)
    {
        for(int j=0;j<ROW;j++)
        {
            cin>>left[i][j];
        }
        cin>>right[i];
    }

    //选择消元方式
    cout<<"--------------STEP1------------------"<<endl;
    cout<<"请选择消元方式，【1】高斯，【2】列主元"<<endl;
    cout<<"Enter the number:[___]\r";
    cout<<"Enter the number:[_";
    int aa;    cin>>aa;
    cout<<"                 开始计算。"<<endl;


    for(int source=0; source<LINE-1; source++)
    {
        if(aa==2) //列主元消元法
        {
            double max = -99999;
            int maxl = source;
            for(int line=source; line<LINE; line++)
            {
                if (fabs(left[line][source])>max)
                {  max=left[line][source];  maxl=line; }
            }
            if(maxl!=source)
            {
                double temp,tmp;
                for(int g=0;g<ROW;g++)
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
            print(left,right);
        }
        //高斯消元法
        for(int line=source+1; line<LINE; line++)
        {
            if(left[source][source]==0){
                cerr<<"错误！主元出现0，无法消元！<<endl;";
                return 0;
            }
            double divide = left[line][source]/left[source][source];
            for(int minu = source; minu < ROW; minu++)
                left[line][minu] -= left[source][minu] * divide;
            right[line] -= right[source] * divide;
            print(left,right);
        }
    }

    //回溯
    cout<<"--------------STEP2------------------"<<endl;
    for(int line = LINE-1; line>=0; line--)
    {
        answer[line] = right[line]/left[line][line];
        cout<<"x"<<line<<"  =  "<<answer[line]<<endl;
        for(int i=0; i<line; i++)
        {
            right[i]-=answer[line]*left[i][line];
            left[i][line]=0;
            print(left,right);
        }
    }
    cout<<endl;
    cout<<"+----------------------------------+"<<endl;
    for(int tt=0;tt<LINE;tt++)
    cout<<"|         x"<<tt<<"   =   "<<answer[tt]<<"          |"<<endl;
    cout<<"+----------------------------------+"<<endl;
}
