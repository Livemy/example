#include <windows.h>
#include <GL\gl.h>
#include <GL\glaux.h>

#pragma comment(lib,"opengl32")
#pragma comment(lib,"glu32")
#pragma comment(lib,"glaux")

void Init(void);
void CALLBACK Resize(GLsizei w,GLsizei h);
void CALLBACK Paint(void);
void DrawObject(void);

void Init(void)
{   //��ʼ�����ڻ���
	glClearColor(0.,0.,0.,0.);
	glClear(GL_COLOR_BUFFER_BIT);
	glShadeModel(GL_FLAT);
}

void CALLBACK Resize(GLsizei w,GLsizei h)
{
	//�������ڳߴ���¼���Ӧ����
	glViewport(0,0,w,h);
	glMatrixMode(GL_PROJECTION);
	glLoadIdentity();
	if(w>h)glOrtho(-20.*(GLfloat)h/(GLfloat)w,20.*(GLfloat)h/(GLfloat)w
		,-20.,20.,-50.,50.);
	else glOrtho(-20.,20.,-20.*(GLfloat)h/(GLfloat)w,20.*(GLfloat)h
		/(GLfloat)w,-50.,50.);
	glMatrixMode(GL_MODELVIEW);
	glLoadIdentity();
}

void CALLBACK Paint(void)
{
	//���ƴ���
	glColor3f(1.,0.,1.);//������ɫ��ɫ
	DrawObject();
	glFlush();
}

void DrawObject(void)
{
auxWireCube(16.0);//�߳�Ϊ16�Ļ���������
}

void main(void)
{
	auxInitDisplayMode(AUX_SINGLE|AUX_RGBA);
	auxInitPosition(0,0,500,500);
	auxInitWindow("���Ƽ򵥼���ͼ��");
	Init();
	auxReshapeFunc(Resize);
	auxMainLoop(Paint);
}