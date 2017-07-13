#include<iostream>
#include<cmath>
#define a 0
#define b 48 //这里来确定积分范围
using namespace std;
int main()
{
    int flag=0; //为了避免假收敛，设置第三次达到精度要求就中止。
    double n=1;
    while(n<=2048)
    {
    double h=(b-a)/(2*n);
    double x=a;
    double fun(double y);
    double S=fun(x)-fun(b);
    for(int k=1;k<=n;k++)
    {
        x+=h;
        S+=4*fun(x);
        x+=h;
        S+=2*fun(x);
    }
    S=S*h/3;
    double Sprev;
    cout<<"当分隔区间 n 为 "<<n<<" 时积分近似值 S 为 "<<S<<endl;
    if(n>2 && abs(Sprev-S)/15<0.0001){flag++; if(flag>2)break;}
    Sprev = S;
    n*=2;
    }
}
double fun(double x)
{
    double y=sqrt(1+cos(x)*cos(x));
    return (y);
}
