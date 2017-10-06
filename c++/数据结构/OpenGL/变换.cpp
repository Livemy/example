#include <windows.h>
#include <GL\gl.h>
#include <GL\glu.h>
#include <GL\glaux.h>

#pragma comment(lib,"opengl32")
#pragma comment(lib,"glu32")
#pragma comment(lib,"glaux")

void Init(void);
void CALLBACK Resize(GLsizei w,GLsizei h);
void CALLBACK Paint(void);
void draw_triangle(void);

void Init(void)
{   //��ʼ�����ڻ���
	glShadeModel(GL_FLAT);
}

void CALLBACK Resize(GLsizei w,GLsizei h)
{
	//�������ڳߴ���¼���Ӧ����
	if(!h)return;
	glViewport(0,0,w,h);
	glMatrixMode(GL_PROJECTION);
	glLoadIdentity();
	if(w<=h)glOrtho(-50.0,50.0,-50.0*(GLfloat)h/(GLfloat)w,
		50.0*(GLfloat)h/(GLfloat)w,-1.0,1.0);
	else glOrtho(-50.0*(GLfloat)w/(GLfloat)h,50.*(GLfloat)w
		/(GLfloat)h,-50.,50.,-1.,1.);
	glMatrixMode(GL_MODELVIEW);
}

void CALLBACK Paint(void)
{
	glClearColor(0.0,0.0,0.0,1.0);
	glClear(GL_COLOR_BUFFER_BIT);

	glLoadIdentity();
	glColor3f(1.0,1.0,1.0);
	draw_triangle();             //�������Ǻ���

	glEnable(GL_LINE_STIPPLE);
	glLineStipple(1,0xf0f0);     //��������ģʽ
	glLoadIdentity();
	glTranslatef(-20.0,0.0,0.0); //ƫ��
	draw_triangle();             //�������Ǻ���

	glLineStipple(1,0xf00f);     //��������ģʽ
	glLoadIdentity();
	glScalef(1.5,0.5,1.0);       //�任�ߴ�
	draw_triangle();

	glLineStipple(1,0x8888);      //��������ģʽ
	glLoadIdentity();
	glRotatef(90.0,0.0,0.0,1.0);  //��ת
	draw_triangle();              //�������Ǻ���
	glDisable(GL_LINE_STIPPLE);

	glFlush();
}

void draw_triangle(void)
{
	glBegin(GL_LINE_LOOP);
	    glVertex2f(0.0,25.0);
		glVertex2f(25.0,-25.0);
		glVertex2f(-25.0,-25.0);
	glEnd();
}

int main(int argc,char** argv)
{
	auxInitDisplayMode(AUX_SINGLE|AUX_RGBA);
	auxInitPosition(0,0,500,500);
	auxInitWindow("���Ƽ򵥼���ͼ��");
	Init();
	auxReshapeFunc(Resize);
	auxMainLoop(Paint);
	return(0);
}