/*�õݹ��㷨�����⡣��һͷСĸţ��
�ӳ�������ĸ���ͷ��ʼÿ����һͷ
ĸţ�����˹��ɵ�n���ж���ͷĸţ*/
#include <iostream.h>
p(int);
int n=1;
void main()
{cin>>n;
  cout<<p(n);
}
p(int n)
{
if (n>3)
return(p(n-1)+n/4);
return(1);

}