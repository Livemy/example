#define stack_init_size 20
#define stackincrement 5
#include "stdlib.h"
#include "stdio.h"
#include "string.h"
#include "memory.h"

typedef struct 
{
    double *base;
    double *top;
    int    stacksize;
}Sqstack1;

typedef struct 
{
    char *base;
    char *top;
    int stacksize;
}Sqstack2;

Sqstack1 OPND;
Sqstack2 OPTR;
//����һ����ջOPND
int Initstack(Sqstack1 &OPND)
{
    OPND.base = (double*)malloc(stack_init_size*sizeof(double));
    if(!OPND.base)
    return -1;
    OPND.top = OPND.base;
    OPND.stacksize=stack_init_size;
    return 0;
}
//����һ����ջOPTR
int Initstack(Sqstack2 &OPTR)
{
    OPTR.base = (char*)malloc(stack_init_size*sizeof(char));
    if(!OPTR.base)
    return -1;
    OPTR.top = OPTR.base;
    OPTR.stacksize=stack_init_size;
    return 0;
}
//��Ԫ��eѹ��ջOPND
int Push ( Sqstack1 &OPND , double e )
{
    if((OPND.top - OPND.base) >= OPND.stacksize)
      {
    OPND.base=(double* )realloc(OPND.base , (OPND.stacksize + stackincrement)*sizeof(double));
    if(!OPND.base) return -1;
    OPND.top = OPND.base+OPND.stacksize;
    OPND.stacksize += stackincrement;
      }
      *OPND.top++ = e;
  return 1;
}
//��Ԫ��eѹ��ջOPTR
int Push ( Sqstack2 &OPTR , char e )
{
    if((OPTR.top - OPTR.base) >= OPTR.stacksize)
      {
    OPTR.base=( char* )realloc(OPTR.base , (OPTR.stacksize + stackincrement)*sizeof(char));
    if(!OPTR.base) return -1;
    OPTR.top = OPTR.base+OPTR.stacksize;
    OPTR.stacksize += stackincrement;
      }
      *OPTR.top++ = e;
  return 1;
}
//��Ԫ��e��ջOPND����
double Pop ( Sqstack1 &OPND , double &e)
{
    if(OPND.top == OPND.base)return -1;
    e = *--OPND.top;
    return e;
}
//��Ԫ��e��ջOPTR����
char Pop ( Sqstack2 &OPTR , char &e)
{
    if(OPTR.top == OPTR.base)return -1;
    e = *--OPTR.top;
    return e;
}
//��e����OPNDջ��Ԫ�ص�ֵ
double Gettop(Sqstack1 OPND, double &e)
{
if(OPND.top == OPND.base) return -1 ;
    e = *(OPND.top - 1) ;
return e;
}
//��e����OPTRջ��Ԫ�ص�ֵ
char Gettop(Sqstack2 OPTR , char &e)
{
if(OPTR.top == OPTR.base) return -1 ;
    e = *(OPTR.top - 1) ;
return e;
}
//�ж϶�����ǲ����ַ�,�Ƿ���1,�񷵻�0
int Is_op (char op)
{
switch (op)
{
case '+' :
case '-' :
case '*' :
case '/' :
case '(' :
case ')' :
case '=' : return 1; break;
default: return  0 ;
}
}
//�������ջ�е�Ԫ�ؽ��и�ֵ������ֵ����
int isp(char op)
{
switch(op)
{
case '=' : return 0; break;
case '(' : return 1; break;
case '+' :
case '-' : return 3; break;
case '*' :
case '/' : return 5; break;
    case ')' : return 6; break;
default: return  -1 ;
}
}
//�Խ�Ҫ�������������и�ֵ������ֵ����
int icp(char op)
{
switch(op)
{
case '=' : return 0; break;
case ')' : return 1; break;
case '+' :
case '-' : return 2; break;
case '*' :
case '/' : return 4; break;
case '(' : return 6; break;
default: return  -1;
}
}
//����������������һ����������ж�Ԫ���㣬����ֵ�ٴ�ѹ��������ջ
double Operate(double operand1 , char op , double operand2)
{
switch(op)
{
case '+' : return(operand1 + operand2); break;
case '-' : return(operand1 - operand2); break;
case '*' : return(operand1 * operand2); break;
case '/' : return(operand1 / operand2); break;
}
return 0 ;
}
//����������ȼ��Ƚ�
char Precede(char e1 , char e2)
{
if(e1-e2<0)
return '<';
    else if(e1-e2 == 0)
return '=';
    else 
return '>';
}

void main( )
{  
char express[30], num[10], theta, tp , d;//express[30]��������һ�����ʽ
    double a ,b , result, tps;          //num[10]������ű��ʽ�������ŵ������ַ�
int t, i, j;
int position = 0;//���ʽ�����ĵ�ǰ�ַ�
Initstack(OPND); 
Initstack(OPTR); Push(OPTR , '=');
printf("input 'b' to run the calc:\n");
scanf("%c" , &d);
getchar();
while(d == 'b')
{
printf( "��������ʽ( ��ʹ��+��-��*��/��(��)��= ): " ) ;
gets(express);
while(express[position] != '='||Gettop(OPTR , tp) != '=' )
{
if(!Is_op(express[position])) 
{ //������������t��jʵ�ָ������Ķ�ȡ
t = position;j=0;
while(!Is_op(express[position]))
{
position++;
}
for(i = t; i<position ; i++ )
{//�ѱ��ʽ�е�t��position-1���ַ�����num[10]
num[j] = express[i];
j++;
}
Push(OPND , atof(num));
    memset(num,0,sizeof(num));//��num[10]���
}
else
{
switch(Precede(isp(Gettop(OPTR , tp)),icp(express[position])))
{
case '<':
Push(OPTR,express[position]);position++;break;
    case '=':
    Pop(OPTR , tp) ;position++;break; 
    case '>':
{
Pop(OPTR , theta) ;
        Pop(OPND , b) ; 
        Pop(OPND , a) ; 
        result = Operate(a, theta ,b);
        Push(OPND , result);break;  
}//end sase
}//end switch
}//end else
}//end while

printf("%s%8.4f\n",express,Pop(OPND,tps));

    memset(express , 0 , sizeof(express));
    position = 0;
    printf("input 'b' to run the calc again:\n");
    scanf("%c" , &d);
    getchar();
}//end while
}
