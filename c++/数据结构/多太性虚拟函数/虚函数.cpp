#include<iostream.h>

class A
{
public:
	int procA()
	{return procA1()* procA2();}
	//���ﷵ�����������ĳ˷�
	//�����������������4��5
	virtual int procA1()
	//���ȥ��virtual�������20
	//Ҳ�Ͳ�����Խ�����
	//Ҳ��û�ж�̫��
	{return 4;}      
	int procA2()
	{return 5;}
};
class B:public A
{
public:
	 int procA1()
	{return 10;}
	 int procA2()
	 {return 1;}
};

main()
{
	B objB;
	cout << objB.procA();
	//Խ����������50
	return 0;
}