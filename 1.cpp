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

typedef struct Student{//ѧ���Ľṹ�� 
	string name;	//���� 
	int grade;	//�ɼ�
}student;

Student studentList[Max_student_numbers];//ѧ���ϼ� 

typedef struct Question{ //����Ľṹ�� 
	int operater;//�������  +or- 1:+;0:-; 
	int num1;	//��һ���� 
	int num2;	//�ڶ����� 
	int result;	//���������ȷ�� 
	int answer;	//�û��Ĵ� 
	int trytimes;//���������0��ֱ�����ԣ�ʮ�֡�1Ϊ����һ�Σ��߷֡�2Ϊ�������Σ���֡��������Σ����÷֡� 
	int mark;//������ĵ÷� 
}question;

question queList[11];//����ĺϼ�10�� 


string changeaddsub(int op)// �Ӽ���ת���� 
{
	if(op==1)return "+";
	else return "-";
	
}

int Random_number()//����������� 
{
	
    //std::default_random_engine srand(time(NULL));
    /*
	std::random_device rd;//random_device������һ��������������� windows�°�զ��զ��,˭��windows��random_device�ǵ���rand_s)
	std::minstd_rand mt(rd());//������������һ�����β�����������,���ṩ�Ļ�,��ʹ��Ĭ��ֵ
	number = (mt() % (b-a+1))+ a;//Ҫȡ��[a,b]�����������ʹ��(rand() % (b-a+1))+ a;
	*/
	int a = 0,b=50;
	return (rand() % (b-a+1))+ a;
}



int Question_generate(question &que)  //��������� 
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
	que.result = re;//���������ȷ�� 
	que.operater = op;
	que.answer = 0;//�û��Ĵ� 
	que.trytimes = 0;
	que.mark = 0;
    return 0;    
}   

void InitQuestion()//��ʼ������ 
{
	srand(time(NULL));
	for(int i=0;i<=10;i++)
	{
		Question_generate(queList[i]);
	}
}

void EachQuestionTest(question &que,int t)//ÿһ������ĵ������Թ��� 
{
	int User_input= 0;//�û����� 
	int cnt=0;
	system("cls");
	cout<<"��ǰ�ǵ�"<<t<<"����Ŀ:"<<endl;
	cout<<que.num1<<changeaddsub(que.operater)<<que.num2<<"=___"<<endl<<"��������Ĵ�:";
	cin>>User_input;
	que.answer = User_input;
	if(que.answer==que.result){
		que.mark+=10;
		return;
	}
	else{
		que.trytimes++;
		system("cls");
		cout<<"�������һ��,�����³���"<<endl;
		cout<<que.num1<<changeaddsub(que.operater)<<que.num2<<"=___"<<endl<<"��������Ĵ�:";
		cin>>User_input;
		que.answer = User_input;
		if(que.answer==que.result){
			que.mark+=7;
			return;
		}
		else{
			que.trytimes++;
			system("cls");
			cout<<"�����������,�����³���"<<endl;
			cout<<que.num1<<changeaddsub(que.operater)<<que.num2<<"=___"<<endl<<"��������Ĵ�:";
			cin>>User_input;
			que.answer = User_input;
			if(que.answer==que.result){
				que.mark+=5;
				return;
			}
			else{
				que.trytimes++;
				system("cls");
				cout<<"�����������,����"<<que.result<<endl<<"���������������һ��";
				getchar();getchar();return; 
			}
		}
	}
}


void ShowRank(int mark)//��ʾ�ɼ��ĵȼ� 
{
	cout<<"��ĵ÷���"<<mark<<"����Ϊ:"<<endl; 
	if(mark>90)cout<<"SMART"<<endl;
	else if(mark>80)cout<<"GOOD"<<endl;
	else if(mark>60)cout<<"Pass"<<endl;
	else cout<<"TRY AGAIN"<<endl; 
	
	getchar();getchar();
}


void Test(){	// ���Է��� 

	int User_grade = 0; 
	//int User_no = 0;
	string User_name = "";
	system("cls");
	cout<<"�������������"<<endl; 
	cin>>User_name;
	Student student;
	student.name = User_name; 
	
	InitQuestion();//��ʼ������
	for(int i=1;i<=10;i++)//��ʼ���� 
	{
		EachQuestionTest(queList[i],i);
		User_grade+=queList[i].mark;
	}
	student.grade = User_grade;
	
	studentList[User_No] = student;
	User_No++;	
	ShowRank(student.grade);

}

void ShowAllGrades(){  //չʾѧ���÷�ͳ�� 
	system("cls");
	cout<<"��"<<User_No<<"���û�"<<endl; 
	for(int i=0;i<User_No;i++)
	{
		cout<<"----------------------"<<endl;
		cout<<"|"<<"                    "<<"|"<<endl;
		cout<<"|"<<" "<<"�û�"<<studentList[i].name<<"�ĳɼ��� "<<studentList[i].grade<<endl;
		cout<<"|"<<"                    "<<"|"<<endl;
		
	}
	cout<<"----------------------"<<endl;
	getchar();getchar();
}

void Welcome()//��ӭ���� 
{
	cout<<"****************************��ӭʹ��Сѧ������ϵͳ-****************************"<<endl; 
	cout<<endl<<endl<<endl<<endl<<endl<<endl<<endl<<"                          ��ӭʹ�ñ���˾��Ʒ   ��������                "<<endl; 
	cout<<endl<<endl<<endl<<endl<<endl<<endl<<endl<<endl;
	cout<<"#################################�س�������ʹ��#################################"<<endl;
	getchar();
}

int Menu()//��Ҫ�Ľ������� 
{
	system("cls");
	cout<<"��ѡ����:"<<endl;
	cout<<"1.�������"<<endl;
	cout<<"2.��ʾ���������˵ĵĳɼ�"<<endl;
	cout<<"3.�˳�"<<endl;
	int mode;
	do{
		cin>>mode;
		if(mode<1||mode>3){
				cout << "����������" << endl;
				Sleep(1*1000); 
				break;
			}
	}while(mode>3||mode<1);
	return mode;
	 
 } 

int main()//�����ú��� 
 {
	Welcome();
	
	while(1)//ѡ���� 
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


