#include<iostream>
#include<windows.h>
using namespace std;

class Queen{
    friend int nQueen(int);
private:
    bool Place(int k);
    void BackTrack(void);
    int n,  //皇后个数
        *x; //当前解
    long sum; //当前已找到的可行方案数
};

bool Queen::Place(int k)
{ //检测两个皇后是否在同一列或者同一斜线上
    for(int j=1; j<k; j++)
        if((abs(k-j)==abs(x[j]-x[k])) || (x[j]==x[k])) return false;
    return true;
}

void Queen::BackTrack(void)
{ //非递归迭代回朔法
    x[1]=0; //初始化
    int k=1;
    while(k>0)
    {
        x[k]+=1;
        while((x[k]<=n)&&!(Place(k))) x[k]+=1;
        if(x[k]<=n)
            if(k==n)sum++;
            else{
                k++;
                x[k]=0;
            }
        else k--;
    }
}

int nQueen(int n)
{
    Queen X; //初始化X
    X.n = n; //n为传入的参数
    X.sum = 0;  //可行的解
    int *p = new int[n+1]; //新建一个n*n的数组，x[0]置空
    for(int i=0; i<=n; i++)
        p[i]=0; //初始化
    X.x=p; //代入类中
    X.BackTrack(); //开始计算
    delete[] p;
    return X.sum; //返回可行解的个数
}

int main()
{
    DWORD start,stop;
    cout<<"请输入要运算N皇后问题的大小N：";
    int n; cin>>n;
        start = GetTickCount();
    int answer;
    answer = nQueen(n);
        stop = GetTickCount();
    cout<<"解的个数为："<<answer<<endl;
    cout<<"运行时间："<<stop-start<<"(ms)\n";
}
