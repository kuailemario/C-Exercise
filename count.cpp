#include<iostream>
#include<fstream>
#include<map>
using namespace std;
int main()
{
    //核心思想：利用散列表空间换时间。
    //时间复杂度：Θ(n)，其中n为输入数组中元素个数
    //空间复杂度：Ω(m)，其中m为输入数组中不同的元素

    map<int,int> num_count; //建立散列表 数字-重数键值对
    ifstream infile("count_input.txt",ios::in);
    if(!infile)
        cerr<<"File Open Error!"<<endl;
    int num1;
    while(!infile.eof())
    {
        infile>>num1; //读入infile中的每一个元素
        ++num_count[num1]; //散列表中对应数字的重数加1
    }
    map<int,int>::iterator iter  = num_count.begin();
    iter++; //迭代器指向散列表中的第一个数
    int key = iter->first;  //获取数字
    int cmax = iter->second;  //获取重数
    while(iter != num_count.end())
    {
        if (cmax < iter->second)
        {  //更新重数最大值
            cmax = iter->second;
            key = iter->first;
        }
        ++iter;
    }
    ofstream outfile("count_output.txt",ios::out);
    outfile<<key<<endl<<cmax;  //输出
    return 0;
}
