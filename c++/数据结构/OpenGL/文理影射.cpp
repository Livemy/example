#include<windows.h>
#include<GL/gl.h>
#include<GL/glu.h>
#include<GL/glaux.h>

#pragma comment(lib,"opengl32")
#pragma comment(lib,"glu32")
#pragma comment(lib,"glaux")

void Init(void);
void MakeImage(void);
void CALLBACK Resize(GLsizei w,GLsizei h);
void CALLBACK Paint(void);

#define ImageWidth      64
#define ImageHeight     64

GLubyte Image[ImageWidth][ImageHeight][3];

void MakeImage(void)
{
	int i,j,r,g,b;

	for(i=0;i<ImageWidth;i++)
	{
		for(j=0;j<ImageHeight;j++)
		{
			r=(i*j)%255;
			g=(4*i)%255;
			b=(4*i)%255;
			Image[i][j][0]=(GLubyte)r;
			Image[i][j][1]=(GLubyte)g;
			Image[i][j][2]=(GLubyte)b;
		}
	}
}

void Init(void)
{
	glClearColor(0.0,0.0,0.0,0.0);
	glEnable(GL_DEPTH_TEST);
	glDepthFunc(GL_LESS);

	MakeImage();
	glPixelStorei(GL_UNPACK_ALIGNMENT,1);
	glTexImage2D(GL_TEXTURE_2D,0,3,ImageWidth,      //��ά������
		ImageHeight,0,GL_RGB,GL_UNSIGNED_BYTE,&Image[0][0][0]);
	glTexParameterf(GL_TEXTURE_2D,GL_TEXTURE_WRAP_S,GL_CLAMP); //�˲���������GL_TEXTURE_2Dһά���ά��
	glTexParameterf(GL_TEXTURE_2D,GL_TEXTURE_WRAP_T,GL_CLAMP); //GL_TEXTURE_WRAP_S��ʾ�ظ���s��t�������ظ�
	glTexParameterf(GL_TEXTURE_2D,GL_TEXTURE_MAG_FILTER,GL_NEAREST);//GL_TEXTURE_MAG_FILTER MAB�ǷŴ��˲�MIN����С�˲�
	glTexParameterf(GL_TEXTURE_2D,GL_TEXTURE_MIN_FILTER,GL_NEAREST);//GL_NEARESTȡ����ʹͼ������
	glTexEnvf(GL_TEXTURE_2D,GL_TEXTURE_ENV_MODE,GL_DECAL);//����Ӱ�亯��
        //����ڶ���������GL_TEXTURE_ENV_MODE����ô����������������GL_DECAL��GL_MODULATE,GL_GL_BLEND������ֵ��������ɫ�Ĵ���ʽ
        //����ڶ���������GL_TEXTURE_ENV_COLOR,��ô���������������Ǹ���R,G,B,A�����飬�����ڲ���GL_BLEND�������ǲſ���
	glEnable(GL_TEXTURE_2D);
	glShadeModel(GL_FLAT);
}

void CALLBACK Paint(void)
{
	glClear(GL_COLOR_BUFFER_BIT|GL_DEPTH_BUFFER_BIT);
	glBegin(GL_QUADS);
	    glTexCoord2f(0.0,0.0);
		glVertex3f(-2.0,-1.0,0.0);
		glTexCoord2f(0.0,1.0);       //�������꺯�����������Զ��������꺯��
                                             //void glTexGen{if}[v](GLenum coord,GLenum pname,TYPE para);����coord����
                                             //��GL_S,GL_T,GL_R,GL_Q��ָ����������S��T��R��Q�е�һ��Ϊ�Զ����ɵ���������
                                             //����pname������GL_TEXTURE_GEN_MODE,GL_OGJECT_PLANE,GL_EYE_PLANE
                                             //����para���ݲ���pname��������ΪGL_TEXTURE_GEN_MODEʱpara��һ������GL_OBJECT_LINEAR,
                                             //GL_EYE_LINEAR,GL_SPHERE_MAP�����Ǿ����ĸ����������������ꡣpname�������������para��
                                             //ָ����������ָ��
		glVertex3f(-2.0,1.0,0.0);
		glTexCoord2f(1.0,1.0);
		glVertex3f(0.0,1.0,0.0);
		glTexCoord2f(1.0,0.0);
		glVertex3f(0.0,-1.0,0.0);
		glTexCoord2f(0.0,0.0);
		glVertex3f(1.0,-1.0,0.0);
		glTexCoord2f(0.0,1.0);
		glVertex3f(1.0,1.0,0.0);
		glTexCoord2f(1.0,1.0);
		glVertex3f(2.41421,1.0,-1.41421);
		glTexCoord2f(1.0,0.0);
		glVertex3f(2.41421,-1.0,-1.41421);
	glEnd();

	glFlush();
}

void CALLBACK Resize(GLsizei w,GLsizei h)
{
	glViewport(0,0,w,h);
	glMatrixMode(GL_PROJECTION);
	glLoadIdentity();
	gluPerspective(60.0,1.0*(GLfloat)w/(GLfloat)h,1.0,30.0);
	glMatrixMode(GL_MODELVIEW);
	glLoadIdentity();
	glTranslatef(0.0,0.0,-3.6);
}

void main(void)
{
	auxInitDisplayMode(AUX_SINGLE|AUX_RGBA|AUX_DEPTH);
	auxInitPosition(0,0,500,500);
	auxInitWindow("���ɼ�����");
	Init();
	auxReshapeFunc(Resize);
	auxMainLoop(Paint);
}

/*��ά�����庯���ǣ�
  void glTexImage2D(GLenum target,GLint level,GLint components,
  GLsizei width,GLsizei height,GLint border,GLenum format,GLenum type
  ,const GLvoid *pixels)*/