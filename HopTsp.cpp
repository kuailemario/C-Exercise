#include <math.h>
#include <time.h>
#include <cstdio>
#include <random>
#include <iostream>
#include <fstream>
#define PI 3.1415926535897
using namespace std;

double VArray[500][500];//神经元输出状态矩阵
int cityDis[500][500];//城市间距离矩阵
int cityNumber;//城市数
int path[500];
double UArray[500][500];//神经元输入状态矩阵
bool is_a_road();
bool conflict(int *path, int i);

int main(int argc, char *argv[])
{
	fstream input;
	input.open("TSP15.TXT", ios::in);

	srand((unsigned)time(NULL));
	input >> cityNumber;

	int result;
	for (int i = 0; i < cityNumber; i++)
	{
		for (int j = 0; j < cityNumber; j++)
		{
			input >> cityDis[i][j];
		}
	}

	{
		double A=15,B=15,D=0.015;
		//double A=50,B=50,C=50,D=0.01;//情况一
		//double A=0.5,B=0.5,C=0.2,D=0.5;//情况二
		//double A=500,B=500,C=200,D=500;//情况三
		//double A = 5, B = 5, C = 5, D = 0.01;//情况四
		double u0 = 0.02;
		double h = 0.5;

		{
			int S = 2;
			int p = 1;
			for (int i = 0; i<cityNumber; i++)
			{
				for (int j = 0; j <= cityNumber; j++)
				{
					if ((i == j) || (i == j + 1))
						VArray[i][j] = 1;
					else
						VArray[i][j] = 0;
				}
			}
			VArray[0][cityNumber - 1] = 1;
			for (int k = 0; k<p; k++)
			{
				int x = rand() % cityNumber;
				int y = rand() % cityNumber;
				if (VArray[x][y] == 0)
					VArray[x][y] = 1;
			}
		}



		{
			double bias;
			int x, y;
			for (int i = 0; i<cityNumber; i++)
				for (int j = 0; j< cityNumber; j++)
				{
					x = rand() % cityNumber / cityNumber;
					y = rand() % cityNumber / cityNumber;
					bias = cos((y - 0.5) / (x - 0.5)*PI + 2 * PI*(j - 1) / cityNumber*sqrt((x - 0.5)*(x - 0.5) + (y - 0.5)*(y - 0.5)));
					UArray[i][j] = -0.007 + bias;
				}
		}
		int tm = 100;
		int r = cityNumber * 10;
		int minvalue;
		int flag = 0; //********
		int minVArray[500][500];
		while (--r>0)
		{
			tm = cityNumber*cityNumber;
			while (--tm > 0)
			{

				{

					for (int x = 0; x<cityNumber; x++)
					{
						for (int i = 0; i<cityNumber; i++)
						{
							double Sum_a = 0, Sum_b = 0, Sum_c = 0, Sum_d = 0;
							for (int j = 0; j<cityNumber; j++)
							{
								/*Sum_a +=VArray[x][j];
								Sum_b +=VArray[j][i];
								Sum_d +=cityDis[x][j]*VArray[j][i+1];*/
								if (j != i)
									Sum_a += VArray[x][j];
								if (j != x)
								{
									Sum_b += VArray[j][i];
									Sum_d += cityDis[x][j] * (VArray[j][i + 1] + VArray[j][i - 1]);
								}
								for (int y = 0; y<cityNumber; y++)
									Sum_c += VArray[j][y];
							}
							UArray[x][i]=UArray[x][i]-h*(A*(Sum_a-1)+B*(Sum_b-1)+D*(Sum_d));
							VArray[x][i] = 0.5*(1.0+tanh(UArray[x][i]/u0));
							//VArray[x][i] = VArray[x][i] - h*(VArray[x][i] + A*(Sum_a)+B*(Sum_b)+D*(Sum_d)+C*(Sum_c - cityNumber));
							//VArray[x][i] = 0.5*(1.0 + tanh(VArray[x][i] / u0));
						}
					}
				}
				if (is_a_road())
				{
					cout << "checked" << endl;
					int tempvalue;
					{
						int value = 0;
						int count = 0;
						int index;
						for (int i = 0; i<cityNumber; i++)
						{
							for (int j = 0; j<cityNumber; j++)
							{
								if (VArray[j][i]>0.99999)
								{
									for (int y = 0; y<cityNumber; y++)
									{
										if ((VArray[y][i + 1]>0.99999) && (i<cityNumber - 1))
											value += cityDis[j][y];
										if (i == cityNumber - 1)
										{
											if (VArray[y][0]>0.99999)
												value += cityDis[j][y];
										}
									}
								}
							}
						}
						tempvalue = value;
					}

					//if(r==1)
					if (flag == 0)
					{
						minvalue = tempvalue;
						for (int x = 0; x<cityNumber; x++)
							for (int i = 0; i<cityNumber; i++)
								minVArray[x][i] = VArray[x][i];
						flag = 1;
					}
					else if (tempvalue < minvalue)
					{
						minvalue = tempvalue;
						for (int x = 0; x<cityNumber; x++)
							for (int i = 0; i<cityNumber; i++)
								minVArray[x][i] = VArray[x][i];
					}
					else
					{
						{
							int x = rand() % cityNumber;
							int y = rand() % cityNumber;
							while (x == y)
								y = rand() % cityNumber;
							if (rand() % cityNumber > cityNumber / 2)
							{
								for (int i = 0; i<cityNumber; i++)
									swap(VArray[i][x], VArray[i][y]);
							}
							else
							{
								for (int i = 0; i<cityNumber; i++)
									swap(VArray[x][i], VArray[y][i]);
							}
						}
						break;
					}
				}
			}//tm

		}//r
		if (minvalue<0)
		{
			//	minvalue=cal_result();//计算最后得到的V，不管合不合格

			{
				int x, a[100], k;//a存放值为1的行位置,k计算有几个1
				for (int i = 0; i<100; i++)
					a[i] = 0;
				for (int i = 0; i<cityNumber; i++) //列
				{
					k = 0;
					fill_n(a, cityNumber, 0);
					for (int j = 0; j<cityNumber; j++) //行
					{
						if (VArray[j][i]>0.99999)
						{
							a[k] = j;
							k = k + 1;
						}
					}
					if (k == 0)
					{
						x = rand() % cityNumber;
						path[i] = x;
						if (i == 0)
							VArray[x][i] = 1;
						else
						{
							while (!conflict(path, i))//第i列,判断放在x位置上是否冲突
							{
								x = rand() % cityNumber;
								path[i] = x;
							}
							VArray[x][i] = 1;
						}
					}
					else if (k == 1)
					{
						x = a[k - 1];
						path[i] = x;
						while (!conflict(path, i))
						{
							x = rand() % cityNumber;
							path[i] = x;
						}
						VArray[x][i] = 1;
					}
					else
					{
						x = a[rand() % k];
						path[i] = x;
						while (!conflict(path, i))
						{
							x = rand() % cityNumber;
							path[i] = x;
						}
						VArray[x][i] = 1;
					}
				}
				//计算修改后的路径
				int value = 0;
				path[cityNumber] = path[0];
				cout << "路径：";
				for (int i = 0; i<cityNumber; i++)
				{
					value += cityDis[path[i]][path[i + 1]];
					cout << " " << path[i];
				}
				cout << " " << path[0] << endl;

				minvalue = value;
			}
		}
		result = minvalue;
	}

	printf("最终结果：%d\n", result);
	cout << "CHNN神经元状态矩阵 :" << endl;
	for (int i = 0; i<cityNumber; i++)
	{
		for (int j = 0; j <= cityNumber; j++)
		{
			cout << VArray[i][j];
			cout << "  ";
			if (VArray[i][j]>0.99)
				path[i] = j;
		}
		cout << endl;
	}
	cout << "城市数:" << cityNumber << endl;
	cout << "旅行路径:";
	for (int m = 0; m < cityNumber; m++)
	{
		cout << path[m];
		if (m != cityNumber - 1)
			cout << "-";
		if (m == cityNumber - 1)
			cout << endl;
	}
	cout << "访问的城市间距离:" << endl;
	for (int m = 0; m<cityNumber; m++)
	{
		cout << path[m] << "-" << path[m + 1] << ":" << cityDis[path[m]][path[m + 1]] << " ";
	}
	cout << endl;
	cout << "路径长度:" << result << endl;
	exit(0);
}


bool conflict(int *path, int i)
{
	for (int j = 0; j<i; j++)
	{
		if ((path[j] - path[i]) == 0)
			return false;
	}
	return true;
}



bool is_a_road()
{
	double Sum_all = 0;
	for (int i = 0; i <cityNumber; i++)
		for (int j = 0; j<cityNumber; j++)
		{
			Sum_all += VArray[i][j];
			if ((VArray[i][j]>0.01) && (VArray[i][j]<0.99))
				return false;
		}
	if (fabs(Sum_all - cityNumber)>1)
		return false;
	for (int i = 0; i<cityNumber; i++)
	{
		double sum_row = 0;
		double sum_col = 0;
		for (int j = 0; j<cityNumber; j++)
		{
			sum_row += VArray[i][j];
			sum_col += VArray[j][i];
		}
		if (fabs(sum_row - 1)>0.01 || fabs(sum_col - 1)>0.01)
			return false;
	}

	return true;

}
