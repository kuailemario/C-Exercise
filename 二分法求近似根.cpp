#include <iostream>
#include <cmath>
#include <fstream>
using namespace std;

//二分法求近似 e^x+10x-2=0 误差不超过0.5*10^-3

int main()
{
    ofstream outfile("save.txt",ios::app); //添加在文件末尾
	double low=0,high=1,med=0.5;
	double answer=0;

	for(;;)
	{
		answer=exp(med)+10*med-2;
		outfile<<med<<"   "<<answer<<endl;
		if(abs(answer)<0.0005)break;
		if(answer>0)high=med;
		else low=med;
		med=(low+high)/2;
	}
	return 0;
}

