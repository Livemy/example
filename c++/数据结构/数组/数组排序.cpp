#include <iostream.h> 
#include <stdlib.h> 
#include <string.h> 
int compare(const void *a,const void *b);
char *list[5]={"cat","car","cab","zap","can"}; //�����õ���ָ��
//ʵ����list[5][4]={"cat","car","cab","zap","can"};
void main() 
{ qsort((void*)list,5,sizeof(list[0]),compare); 
 for(int i=0;i<5;i++) 
     cout<<list[ i ]<<endl; 
} 
int compare (const void* a,const void* b) 
{ return strcmp( * (char * *)a,*(char * *)b);} 
//(char * *)a�Ƕ���ָ�룬(char * )a��һ����Ȼ��һ��
//����ָ��Ĳ�������list[x][y]�е�x���������൱����
//�������ַ�������һ��ָ������yΪ��λ�������ģ�����
//���ǵ������ַ�������һ��С�������˵���������

#include<stdio.h>
#define T "%s,%s\n"
main()
{
	static char *x[]={"abcd","efgh","mnpq"};
	char **y,**z;
	y=x+1;
	z=x+2;
	printf(T,*x,*x+1);
	printf(T,*y,*z);
}