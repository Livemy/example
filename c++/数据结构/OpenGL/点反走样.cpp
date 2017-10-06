#include<windows.h>

#include<GL/gl.h>
#include<GL/glu.h>
#include<GL/glaux.h>

#define RAMPSIZE 16
#define RAMPSTART 32

#pragma comment(lib,"opengl32")
#pragma comment(lib,"glu32")
#pragma comment(lib,"glaux")

void Init(void);
void CALLBACK Resize(GLsizei w,GLsizei h);
void CALLBACK Paint(void);

void Init(void) //�򵥷�����
{
	glEnable(GL_POINT_SMOOTH);//ƽ������
	glEnable(GL_BLEND);       //�ںϹ���
	glBlendFunc(GL_SRC_ALPHA,  //�ںϲ��� Դ
	GL_ONE_MINUS_SRC_ALPHA);   //Ŀ��
	glHint(GL_POINT_SMOOTH_HINT,GL_DONT_CARE);
	glPointSize(3.0);

	glClearColor(1.0,1.0,1.0,0.0);//��ɫ����
}

/*void Init(void)//����������
{
	int i;

	for(i=0;i<RAMPSIZE;i++)
	{
		GLfloat shade;
		shade=(GLfloat)i/(GLfloat)RAMPSIZE;
		auxSetOneColor(RAMPSTART+(GLint)i,shade,shade,shade);
	}
	glEnable(GL_POINT_SMOOTH);  //ƽ������
	glHint(GL_POINT_SMOOTH_HINT,GL_FASTEST);
	glPointSize(3.0);
	glClearIndex((GLfloat)RAMPSTART);//����
}*/

void CALLBACK Paint(void)
{
	int i;

	glClear(GL_COLOR_BUFFER_BIT);
	glColor4f(0.0,0.0,0.0,1.0);
	glBegin(GL_POINTS);
	    for(i=1;i<10;i++)
			glVertex2f((GLfloat)i*10.0,(GLfloat)i*10.0);
	glEnd();
	glFlush();
}

void CALLBACK Resize(GLsizei w, GLsizei h)
{
	if(!h)return;

	glViewport(0,0,w,h);
	glMatrixMode(GL_PROJECTION);
	glLoadIdentity();

	if(w<h)
		glOrtho(0.0,100.0,
		0.0,100*(GLfloat)h/(GLfloat)w,-1.0,1.0);
	else
		glOrtho(0.0,100.0*(GLfloat)w/(GLfloat)h,
		0.0,100.0,-1.0,1.0);
	glMatrixMode(GL_MODELVIEW);
	glLoadIdentity();
}

int main(int argc,char **argv)
{
	auxInitDisplayMode(AUX_SINGLE|AUX_RGB);
	//auxInitDisplayMode(AUX_SINGLE|AUX_INDEX);//����
	auxInitPosition(0,0,100,100);
	auxInitWindow("��ķ�����");

	Init();

	auxReshapeFunc(Resize);
	auxMainLoop(Paint);

	return(0);
}