#include <iomanip.h> 
#include <stdlib.h> 
#include <fstream.h> 
void fun1(void) 
{ 
char* file1; 
file1="a.txt";//��������֮ͬ�� 
ifstream f1(file1,ios::in|ios::nocreate); 
if(!f1) 
{ 
cerr<<file1<<" file not open!"<<endl; 
exit(1); 
} 
char ch; 
while(f1.get(ch)) 
{ 
cout<<ch; 
} 
} 


void fun2(void) 
{ 
char file2[30]; 
cout<<"�������ļ�������"<<'\t';//��������֮ͬ�� 
cin>>file2;//��������֮ͬ�� 
ifstream f2(file2,ios::in|ios::nocreate); 
if(!f2) 
{ 
cerr<<file2<<" file not open!"<<endl; 
exit(1); 
} 
char ch; 
while(f2.get(ch)) 
{ 
cout<<ch; 
} 
} 


void main(void) 
{ 
int i; 
cout<<"������1��2ȥѡ��ִ��fun1��fun2����"; 
cin>>i; 
if (1==i) 
fun1(); 
else 
fun2(); 
char a; 
cin>>a; 
} 