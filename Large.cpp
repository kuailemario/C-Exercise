#include<iostream>
#include<vector>
using namespace std;
/*------可能用到的一些变量------
X  要最终计算f(x)
n  用n+1个数值做n次差值
x[n] y[n] 每个数的横纵坐标
k  累加大循环
j  累乘小循环
P  累乘小结果
Y  最终的L(x),相当于f(x)
------------------------------*/

int main()
{
    while(1){
    vector<double> x,y;
    cout<<"请输入您要进行的差值次数[n]，n=1即线性插值"<<endl;
    int n;    cin>>n;
    cout<<"请输入已知节点及函数值"<<endl;
    for(int i=0;i<=n;i++)
    {
        double tmp=0;
        cin>>tmp;
        x.push_back(tmp);
        cin>>tmp;
        y.push_back(tmp);
    }
    cout<<"请输入要推算的某点函数值f(x)横坐标[X]"<<endl;
    double X=0;
    cin>>X;
    cout<<"输入结束。请确认各项参数是否有误:"<<endl;
    cout<<"----------------------------------"<<endl;
    cout<<"您要进行的是";
    if(n==1)cout<<"[线性]插值"<<endl;
    else if(n==2)cout<<"[抛物]插值"<<endl;
    else cout<<'['<<n<<"次]拉格朗日插值"<<endl;
    cout<<"已知节点如下："<<endl;
    for(int i=0;i<=n;i++)
    {
        cout<<"f("<<x[i]<<") = "<<y[i]<<endl;
    }
    cout<<"要求 f("<<X<<") 的近似值"<<endl;
    cout<<"----------------------------------"<<endl;
    cout<<"请输入 [Y]确认执行  [N]重新输入"<<endl;
    char cho='Y';    cin>>cho;
    if(cho=='Y' || cho=='y')
    {
        double Y = 0; //y  最终的L(x),相当于f(x)
        for(int k=0;k<=n;k++)
        {
            double P = 1; //P  累乘小结果
            for(int j=0;j<=n;j++)
            {
                if(j!=k) P*=(X-x[j])/(x[k]-x[j]);
            }
            Y+=P*y[k];
        }
        cout<<"计算结果为f("<<X<<") ="<<Y<<endl;
    }
    else continue;
    cout<<"----------------------------------"<<endl;
}}
