#include <iostream.h> 
#include <ctype.h> 

//#include "stdafx.h" �����window����vc�Զ����ɵĶ�������ĳ�����dos����
//û�б�Ҫͨ������Ӧ�ó����������������ԭ�ļ��ü��±����Ϊ*.cpp�ļ���
//Ȼ���ڴ��ļ��ϵ����Ҽ��Ӵ򿪷�ʽ��ѡ��vc��vc���������һ����ʾ������
//�Ƿ��������ռ��ļ�������ȷ���Ϳ��Ե����ˡ���ĳ�������ȷ�Ŀ�������

class animalType 
{ 
char breed[40]; 
public: 
void getBreed() 
{ 
cout<<"What is the breed."; 
cin>>breed; 
} 
void prebreed(void) 
{ 
cout<<"\nThe animal's breed is"<<breed; 

} 
}; 
int main(int argc, char* argv[]) 
{ 
animalType * animal[25]; 
int num=0; 
char ans; 
do 
{ 
animal[num]=new animalType; 
animal[num++]->getBreed(); 
cout << "Do you want to enter another animal(Y/N)?"; 
cin >> ans; 
} 
while(toupper(ans)!='N'); 
for(int ctr=0;ctr<num;ctr++) 
{ 
animal[ctr]->prebreed(); 
} 
return 0; 
} 