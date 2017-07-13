#include <iostream>
#include <cmath>
#include <fstream>
using namespace std;
//迭代法，初值0，求近似 x_k+1=(2-e^x_k)/10
//误差不超过0.5*10^-3

int main()
{
    ofstream outfile("save2.txt",ios::app); //添加在文件末尾
    double answer=0;
    double x=0;
    for(;;)
    {
        answer=(2-exp(x))/10;
        outfile<<x<<"   "<<answer<<endl;
        if(abs(answer-x)<0.0005)break;
        x=answer;
    }
}
