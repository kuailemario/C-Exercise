//************************************
//*八数码问题
//************************************
#include<iostream>
#include<cstdio>
#include<map>
#include<queue>
#include<algorithm>
#include<time.h>
#include<string>
using namespace std;

struct P{
	int d;	//深度g(n)
	int w;	//不在位数h(n)
	int re; //逆序数
	int id;	//记录该节点的id，用于输出时找到该节点
	string s;	//状态
	friend bool operator <(const P &a,const P &b){//按f(n)=g(n)+h(n)大小排序
		return a.d+a.w+a.re>b.d+b.w+b.re;  //【这里是使用了不在位数 + 逆序数的估价函数】
	}
}p;
const int N=3;	//棋盘大小
//const string t="123456780";
const string t="123804765"; //目标状态
string stack[1000000];		//记录搜索中的节点
string record[1000000];		//从起点开始记录解路径
int father[10000000];		//记录该节点的父节点
int top=0;					//stack的指针
priority_queue<P> pq;		//open表
map<string,bool> mp;		//记录该状态是否已经访问过：1访问过，0没有
int a1 = -1;                //记录生成节点数之一

int Rever(string s){        //计算逆序数
    int Rev = 0;
    for(int i=0;i<9;i++){
        for(int j=0;j<i;j++)
            if(s[j]>s[i]&&s[i]!='0')
                Rev++;
    }
    return Rev;
}

int calw(string s)//计算该状态的不在位数h(n)
{
	int re=0;
	for(int i=0;i<9;i++) if(s[i]!=t[i] && s[i]!='0') re++;
	return re;
}
int solve()	//搜索过程
{
	P cur;
	a1++;  //生成节点
	while(!pq.empty()){
		cur=pq.top(); //open表
		pq.pop();
		if(cur.s==t) return cur.id;	//达到目标状态，返回当前节点的id
		int x,y;
		int ops=0;
		while(cur.s[ops]!='0') ops++;
		x=ops/3,y=ops%3;  //空格所在位置
		int r=cur.id;
		if(x>0){          //空格向上移
			p.s=cur.s;
			swap(p.s[ops],p.s[ops-3]);
			if(!mp[p.s]){
				p.d=cur.d+1,p.w=calw(p.s),p.re=Rever(p.s),p.id=top+1;
				pq.push(p);
				stack[++top]=p.s;
				father[top]=r;
				mp[p.s]=1;
			}
		}
		if(x<2){    //空格向下移
			p.s=cur.s;
			swap(p.s[ops],p.s[ops+3]);
			if(!mp[p.s]){
				p.d=cur.d+1,p.w=calw(p.s),p.re=Rever(p.s),p.id=top+1;
				pq.push(p);
				stack[++top]=p.s;
				father[top]=r;
				mp[p.s]=1;
			}
		}
		if(y>0){    //空格向左移
			p.s=cur.s;
			swap(p.s[ops],p.s[ops-1]);
			if(!mp[p.s]){
				p.d=cur.d+1,p.w=calw(p.s),p.re=Rever(p.s),p.id=top+1;
				pq.push(p);
				stack[++top]=p.s;
				father[top]=r;
				mp[p.s]=1;
			}
		}
		if(y<2){   //空格向右移
			p.s=cur.s;
			swap(p.s[ops],p.s[ops+1]);
			if(!mp[p.s]){
				p.d=cur.d+1,p.w=calw(p.s),p.re=Rever(p.s),p.id=top+1;
				pq.push(p);
				stack[++top]=p.s;
				father[top]=r;
				mp[p.s]=1;
			}
		}
	}
	return -1;	//搜索失败
}

void print(int x)////从record表中输出当前搜索的节点
{
	int k=0;
	for(int i=0;i<N;i++){
		for(int j=0;j<N;j++){
			if(record[x][k]=='0')
				printf("  ");
			else printf("%c ",record[x][k]);
			k++;
		}
		printf("\n");
	}
	printf("\n");
}
int main()
{
//	freopen("a.txt","r",stdin);
	int tt;	//测试的组数
	cout<<"请输入测试的组数:";
	cin>>tt;
	for(int k=1;k<=tt;k++){
		cout<<"Case "<<k<<":\n";
		int i,j;
		char a;
		p.s="";
		for(i=0;i<N;i++){
			for(j=0;j<N;j++){
				cin>>a;  //输入0～8数码
				p.s+=a;
			}
		}
		if(Rever(p.s)%2 != Rever(t)%2) cerr<<"逆序对数奇偶不同。\n";
		clock_t start_time;
		start_time=clock();


		p.d=0,p.w=calw(p.s),p.re=Rever(p.s),p.id=0;
		father[0]=-1;
		mp[p.s]=1;
		stack[0]=p.s;
		pq.push(p);	//往open表中加入初始状态节点
		int id=solve();//调用搜索过程
		if(id==-1){
			cout<<"无解！\n";
		}else{
			int c=-1;
			while(id>=0){	//把stack中存的节点按次序放入到record中
				record[++c]=stack[id];
				id=father[id];
			}
			cout<<"原图："<<endl;
			print(c); //输出初始节点
			cout<<"移动过程: \n\n";
			int num=0;
			for(i=c-1;i>=0;i--){
				cout<<"Step "<<c-i<<":\n";//输出当前搜索步骤
				print(i);//输出当前搜索的节点
				num++;
			}
			cout<<"移动结束！\n";
			int a2=pq.size();
			cout<<"生成节点数为："<<a1+a2<<endl;
			cout<<"扩展节点数为："<<num<<endl;
		}
		mp.clear();
		while(!pq.empty()) pq.pop();
		top=0;
		clock_t end_time=clock();
		double durTime = double(end_time - start_time);
		cout<<"运行时间="<<durTime<<endl;

		cout<<endl;
	}
	system("pause\n");
	return 0;
}
