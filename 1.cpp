#include<iostream>    
#include<stdlib.h>    
#include<math.h>   
#include<stdio.h>
#include<time.h> 
#include<random> 
#include<fstream>
#include<Windows.h>
#define Max_student_numbers 100
using namespace std;



int User_No = 0;

typedef struct Student{//学生的结构体 
	string name;	//姓名 
	int grade;	//成绩
}student;

Student studentList[Max_student_numbers];//学生合集 

typedef struct Question{ //问题的结构体 
	int operater;//运算符号  +or- 1:+;0:-; 
	int num1;	//第一个数 
	int num2;	//第二个数 
	int result;	//该问题的正确答案 
	int answer;	//用户的答案 
	int trytimes;//错误次数，0是直接做对，十分。1为错误一次，七分。2为错误两次，五分。错了三次，不得分。 
	int mark;//该问题的得分 
}question;

question queList[11];//问题的合集10个 


string changeaddsub(int op)// 加减法转换器 
{
	if(op==1)return "+";
	else return "-";
	
}

int Random_number()//随机数生成器 
{
	
    //std::default_random_engine srand(time(NULL));
    /*
	std::random_device rd;//random_device来产生一个随机数当作种子 windows下爱咋整咋整,谁叫windows的random_device是调用rand_s)
	std::minstd_rand mt(rd());//随机数引擎接受一个整形参数当作种子,不提供的话,会使用默认值
	number = (mt() % (b-a+1))+ a;//要取得[a,b]的随机整数，使用(rand() % (b-a+1))+ a;
	*/
	int a = 0,b=50;
	return (rand() % (b-a+1))+ a;
}



int Question_generate(question &que)  //问题产生器 
{   
    int num_1 = 0;
	int num_2 = 0;
	int op = 0;
	int re = 0;
	
    do    
    {    
        num_1 = Random_number();    
        num_2 = Random_number();
        op = Random_number()%2;
        if(op==1){
        	re = num_1+num_2;
		}else{
			re = num_1-num_2;
		}       
    }while(!((re>=0)&&(re<=50)));    
    que.num1 = num_1;
	que.num2 = num_2;
	que.result = re;//该问题的正确答案 
	que.operater = op;
	que.answer = 0;//用户的答案 
	que.trytimes = 0;
	que.mark = 0;
    return 0;    
}   

void InitQuestion()//初始化问题 
{
	srand(time(NULL));
	for(int i=0;i<=10;i++)
	{
		Question_generate(queList[i]);
	}
}

void EachQuestionTest(question &que,int t)//每一个问题的单独测试过程 
{
	int User_input= 0;//用户输入 
	int cnt=0;
	system("cls");
	cout<<"当前是第"<<t<<"个题目:"<<endl;
	cout<<que.num1<<changeaddsub(que.operater)<<que.num2<<"=___"<<endl<<"请输入你的答案:";
	cin>>User_input;
	que.answer = User_input;
	if(que.answer==que.result){
		que.mark+=10;
		return;
	}
	else{
		que.trytimes++;
		system("cls");
		cout<<"你输错了一次,请重新尝试"<<endl;
		cout<<que.num1<<changeaddsub(que.operater)<<que.num2<<"=___"<<endl<<"请输入你的答案:";
		cin>>User_input;
		que.answer = User_input;
		if(que.answer==que.result){
			que.mark+=7;
			return;
		}
		else{
			que.trytimes++;
			system("cls");
			cout<<"你输错了两次,请重新尝试"<<endl;
			cout<<que.num1<<changeaddsub(que.operater)<<que.num2<<"=___"<<endl<<"请输入你的答案:";
			cin>>User_input;
			que.answer = User_input;
			if(que.answer==que.result){
				que.mark+=5;
				return;
			}
			else{
				que.trytimes++;
				system("cls");
				cout<<"你输错了三次,答案是"<<que.result<<endl<<"输入任意键进入下一题";
				getchar();getchar();return; 
			}
		}
	}
}


void ShowRank(int mark)//显示成绩的等级 
{
	cout<<"你的得分是"<<mark<<"被评为:"<<endl; 
	if(mark>90)cout<<"SMART"<<endl;
	else if(mark>80)cout<<"GOOD"<<endl;
	else if(mark>60)cout<<"Pass"<<endl;
	else cout<<"TRY AGAIN"<<endl; 
	
	getchar();getchar();
}


void Test(){	// 测试方法 

	int User_grade = 0; 
	//int User_no = 0;
	string User_name = "";
	system("cls");
	cout<<"请输入你的姓名"<<endl; 
	cin>>User_name;
	Student student;
	student.name = User_name; 
	
	InitQuestion();//初始化问题
	for(int i=1;i<=10;i++)//开始测验 
	{
		EachQuestionTest(queList[i],i);
		User_grade+=queList[i].mark;
	}
	student.grade = User_grade;
	
	studentList[User_No] = student;
	User_No++;	
	ShowRank(student.grade);

}

void ShowAllGrades(){  //展示学生得分统计 
	system("cls");
	cout<<"共"<<User_No<<"个用户"<<endl; 
	for(int i=0;i<User_No;i++)
	{
		cout<<"----------------------"<<endl;
		cout<<"|"<<"                    "<<"|"<<endl;
		cout<<"|"<<" "<<"用户"<<studentList[i].name<<"的成绩是 "<<studentList[i].grade<<endl;
		cout<<"|"<<"                    "<<"|"<<endl;
		
	}
	cout<<"----------------------"<<endl;
	getchar();getchar();
}

void Welcome()//欢迎界面 
{
	cout<<"****************************欢迎使用小学生测验系统-****************************"<<endl; 
	cout<<endl<<endl<<endl<<endl<<endl<<endl<<endl<<"                          欢迎使用本公司产品   奥利给！                "<<endl; 
	cout<<endl<<endl<<endl<<endl<<endl<<endl<<endl<<endl;
	cout<<"#################################回车键进入使用#################################"<<endl;
	getchar();
}

int Menu()//主要的交互界面 
{
	system("cls");
	cout<<"请选择功能:"<<endl;
	cout<<"1.进入测试"<<endl;
	cout<<"2.显示其他所有人的的成绩"<<endl;
	cout<<"3.退出"<<endl;
	int mode;
	do{
		cin>>mode;
		if(mode<1||mode>3){
				cout << "请重新输入" << endl;
				Sleep(1*1000); 
				break;
			}
	}while(mode>3||mode<1);
	return mode;
	 
 } 

int main()//主调用函数 
 {
	Welcome();
	
	while(1)//选择功能 
	{
		int mode=Menu();
		switch(mode)
		{
			case 1:Test();break;
			case 2:ShowAllGrades();break;
			case 3:exit(1);
	
		}
	}	 
 }


