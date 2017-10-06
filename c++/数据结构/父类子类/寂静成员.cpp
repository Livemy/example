#include <iostream.h>
#include <iomanip.h>
const int MAX_ELEMS=5;
enum Logical {FALSE,TRUE};

class myArray
{
public:
	myArray(int nNumElems=MAX_ELEMS,int fInitVal=0);
	~myArray()
	{delete []m_pnArray;}
	int& operator[](int nIndex)
	{return m_pnArray[nIndex];}
	//void show(const char* pszMsg=" ",const int nNumElems=MAX_ELEMS);

protected:
	int *m_pnArray;
	int m_nNumElems;
};

class myStack : myArray
{
public:
	myStack(int nMaxHeight=10)//���ù��캯���ṩ�ӿ�
		:myArray(nMaxHeight,0)
	{clear();}
	Logical push(int nNum);
	Logical pop(int& nNum);
	int getHeight()
	{return m_nHeight;}
	void clear()
	{m_nHeight=0;}//��ʼ��m_nHeight

protected:
	int m_nHeight;//�������ı���
};

myArray::myArray(int nNumElems,int fInitVal)
{
    m_nNumElems=(nNumElems>0)?nNumElems:1;
	m_pnArray=new int[m_nNumElems];
	for(int i=0;i<m_nNumElems;i++)
		m_pnArray[i]=fInitVal;
}

/*void myArray::show(const char* pszMsg,const int nNumElems)
{
    cout << pszMsg << endl;
	for(int i=0;i<nNumElems;i++)
		cout << m_pnArray[i] << ' ';
	cout <<"ew" << endl;
}*/

Logical myStack::push(int nNum)//��ջ
{
    if(m_nHeight < m_nNumElems)
	{
	    m_pnArray[m_nHeight++]=nNum;
		return TRUE;//�����߼���
	}

	else
		return FALSE;//�����߼���
}

Logical myStack::pop(int& nNum)//��ջ
{
    if(m_nHeight > 0)
	{
		nNum = m_pnArray[--m_nHeight];
		return TRUE;//�����߼���
	}
	else
		return FALSE;//����������
}

main()
{
    int nArr[MAX_ELEMS]={23,45,89,74,51};
	int nVal;
	//cout << nVal << endl;
	myStack Stack(MAX_ELEMS);
	for(int i=0;i<MAX_ELEMS;i++)//ֻ����ʾ����ͽ�ջ�޹�
	{
	    cout << " Pushing " << nArr[i] << " into the stack\n ";
		if(!Stack.push(nArr[i]))//���ý�ջ�����߼���ʱ��ʾ������ʱ��ջ
			cout << " Stack overflow at i=" << i << endl;
	}

	cout << endl;
	cout << "Stack has " << Stack.getHeight() << " elements\n ";
	cout << endl;

	while(Stack.pop(nVal))//���ó�ջ�����߼���ʱѭ��
		cout << " Popping " << nVal << " off the stack \n ";

	cout << endl;
	cout << " Stack has " << Stack.getHeight() << " elements\n\n";

	return 0;
}