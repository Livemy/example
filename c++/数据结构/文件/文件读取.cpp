#include <iostream.h> 
#include <stdlib.h> 
#include <stdio.h>
#include <fstream.h> 

int main() 
{ 


     short i=1; 
     char buf[100]; 
     ifstream aa("aa.txt"); 

     while (1) { 
            
           cout << i++ << ':' ; 
           aa.seekg(0,ios::beg);//�ڶ���ѭ���������ļ�ͷ����aa.rdbuf������ʾ��������ݣ����Ҳ��ᰴ�д������е����ݡ� 
           while(aa.getline(buf,100)) { 
               cout << buf << endl; 

           } 
           cout << "Please press any key to continue..."; 
           cin.get(); 
     } 

     return 0; 
} 
