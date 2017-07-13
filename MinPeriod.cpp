#include<iostream>
using namespace std;
int main()
{
    string s;
    cout<<"请输入字符串"<<endl;
    cin>>s;
    for(int i=1;i<=s.length();i++){
        if(s.length()%i==0){  //周期长度不能整除
            bool flag=true;
            for(int j=i;j<s.length();j++){
                if(s[j]!=s[j%i]){  //不是这个周期
                    flag=false;
                    break;
                }
            }
            if(flag){
                cout<<i<<endl;
                break;
            }
        }
    }
    return 0;
}
