/*��һ�����������������������֣�
<1>��ѭ������
���һ���ڵ��nextָ����NULLֵ
<2>��ѭ��������
���һ���ڵ��nextָ�룬ָ�������е�ĳһ���ڵ�
*/
#include<iostream.h>
typedef struct SomeList
{
//int Some;
SomeList *next;
}SomeList;

bool ListType(SomeList * ListHead)
{
  SomeList *Now;
  SomeList *i;

  Now = ListHead;
  while(Now->next != NULL)
  {
    i = ListHead;
    while(i != Now)
    {
      if(Now->next == i)
        return 1; //&Oacute;&ETH;&Ntilde;&shy;&raquo;��
      i = i->next;
    }
    Now = Now->next;
  }
  return 0; //&Icirc;&THORN;&Ntilde;&shy;&raquo;��
}

void main()
{
SomeList *Head = new SomeList;
Head->next = NULL;
if(ListType(Head))
cout<<"test 1: ��ѭ����\n";
else
cout<<"test 1: ��ѭ����\n";

SomeList *Tail = new SomeList;
Head->next = Tail;
Tail->next = Head;
if(ListType(Head))
cout<<"test 2: ��ѭ����\n";
else
cout<<"test 2: ��ѭ����\n";

SomeList *Middle = new SomeList;
Head->next = Middle;
Middle->next = Tail;
Tail->next = Middle;
if(ListType(Head))
cout<<"test 3: ��ѭ����\n";
else
cout<<"test 3: ��ѭ����\n";

}
