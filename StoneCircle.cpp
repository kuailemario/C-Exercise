#include<iostream>
using namespace std;

int stone[101][101]={0};  //记录石子合并的分数
int number[101]; //记录每堆石子的个数

int main()
{
    //由于必须是相邻堆进行合并，所以一定会出现相邻两堆、三堆、四堆……的合并过程。
    //因此只要对三堆、四堆的子问题取最优解，然后根据最优取最优即可。
    //使用二维数组 s[i][j] 作为合并的最优得分，其中i表示从第i堆往后合并，
    //j表示共有几堆合并成了一堆。比如有4堆石子，则s[3][3]为第3、4、1堆石子合并。
    int calc_min(int i,int N);
    int calc_max(int i,int N);
    int total(int i, int j,int N);
    cout<<"请输入石子堆数(1~100)：";
    int N; cin>>N;
    if(N<=0 || N>100) { cerr<<"堆数错误。"<<endl; return 0; }
    cout<<"请输入每堆石子个数：";
    for(int i=1; i<=N; i++)
        cin>>number[i];
    if(N==1)   //一堆的情况
    {
        cout<<"最小值：0"<<endl;
        cout<<"最大值：0"<<endl;
        return 0;
    }
    for(int i=2; i<=N; i++)  //开始计算
    {
        calc_min(i,N);
        if(i==N) //循环结束后，找最后一次合并的最小值
        {
            int result = stone[1][N];
            for(int p=2;p<=N;p++)
                if(stone[p][N]<result) result = stone[p][N];
            cout<<"最小值："<<result<<endl;
        }
    }
    for(int i=2; i<=N; i++)  //开始计算
    {
        calc_max(i,N);
        if(i==N) //循环结束后，找最后一次合并的最小值
        {
            int result = stone[1][N];
            for(int p=2;p<=N;p++)
                if(stone[p][N]>result) result = stone[p][N];
            cout<<"最大值："<<result<<endl;
        }
    }
}

int total(int i, int j,int N)
{
    int sum=0;
    while(j--)
    {
        sum+=number[i];
        i++;
        if(i>N)i-=N;
    }
    return sum;
}

int calc_min(int i,int N)   //i是目前几堆一起合并
{
    //三堆合并 12,21  四堆合并 13,22,31  五堆合并 14,23,32,41……
    //先把i拆分成各种可能的两堆组合
    int j=0, now=i;  //now表示几堆一起合并
    while(--i>0) //比如 N是六堆，now是五堆，就是 4 3 2 1
    {
        ++j; //j 就是 1 2 3 4，这样now就拆分成了两堆i j
        for(int k=1; k<=N; k++)  //k表示从第k堆开始的合并计算
        {
            int temp = stone[k][now]; //先缓存之前的数据
            stone[k][now] = stone[k][i] + stone[k+i>N ? k+i-N:k+i][j] + total(k,now,N);
            // stone[1][5]=stone[1][4]+stone[5][1]+total(1,5);  k=1,i=4,j=1,now=5
            // stone[5][5]=stone[5][2]+stone[1][3]+total(5,5);  k=5,i=2,j=3,now=5
            // 注意由于是圆形堆，要考虑首尾的情况。

            if(temp != 0 && stone[k][now]>temp) stone[k][now] = temp;
            //如果本次的组合分数比之前的大，那就保留之前的
        }
    }
}

int calc_max(int i,int N)   //i是目前几堆一起合并
{
    //三堆合并 12,21  四堆合并 13,22,31  五堆合并 14,23,32,41……
    //先把i拆分成各种可能的两堆组合
    int j=0, now=i;  //now表示几堆一起合并
    while(--i>0) //比如 N是六堆，now是五堆，就是 4 3 2 1
    {
        ++j; //j 就是 1 2 3 4，这样now就拆分成了两堆i j
        for(int k=1; k<=N; k++)  //k表示从第k堆开始的合并计算
        {
            int temp = stone[k][now]; //先缓存之前的数据
            stone[k][now] = stone[k][i] + stone[k+i>N ? k+i-N:k+i][j] + total(k,now,N);
            // stone[1][5]=stone[1][4]+stone[5][1]+total(1,5);  k=1,i=4,j=1,now=5
            // stone[5][5]=stone[5][2]+stone[1][3]+total(5,5);  k=5,i=2,j=3,now=5
            // 注意由于是圆形堆，要考虑首尾的情况。

            if(temp != 0 && stone[k][now]<temp) stone[k][now] = temp;
            //如果本次的组合分数比之前的小，那就保留之前的
        }
    }
}

