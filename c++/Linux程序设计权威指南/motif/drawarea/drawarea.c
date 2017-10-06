
	/* File: drawarea.c */
	#include <locale.h>
	#include <Xm/Xm.h>
	#include <Xm/DrawingA.h>

	Widget 	drawarea;
	GC	gcXor, gcCopy;
	int	x1, y1, x2, y2;

	void prepare()
	{
		int n;
		Arg args[10];
		XGCValues gcv;
		Colormap cmap;
		XColor col, unused;

		cmap = DefaultColormapOfScreen(XtScreen(drawarea));

		//����ǰ���ͱ���
		if(!XAllocNamedColor(XtDisplay(drawarea), cmap, "red", 
			&col, &unused)){
			printf("Cannot allocate color.\n");
			return;
		}

		//����GC
		gcv.foreground = col.pixel;
		gcCopy = XtGetGC(drawarea, GCForeground, &gcv);
		XSetLineAttributes(XtDisplay(drawarea), gcCopy, 3,
			LineSolid, CapRound, JoinRound);

		gcv.foreground = col.pixel;
		gcv.function = GXxor;
		gcXor = XtGetGC(drawarea, GCForeground | GCFunction, &gcv);
		XSetLineAttributes(XtDisplay(drawarea), gcXor, 3,
			LineSolid, CapRound, JoinRound);
        }

	void button_pressed(Widget w, XtPointer client_data, XEvent *event)
	{
		x1 = x2 = event->xbutton.x;
		y1 = y2 = event->xbutton.y;
		XDrawLine(XtDisplay(w), XtWindow(w), gcXor, x1, y1, x2, y2);
	}

	void button_released(Widget w, XtPointer client_data, XEvent *event)
	{
		x2 = event->xbutton.x;
		y2 = event->xbutton.y;
		XDrawLine(XtDisplay(w), XtWindow(w), gcCopy, x1, y1, x2, y2);
	}

	void button_motion(Widget w, XtPointer client_data, XEvent *event)
	{
		//����ԭ������
		XDrawLine(XtDisplay(w), XtWindow(w), gcXor, x1, y1, x2, y2);
		x2 = event->xbutton.x;
		y2 = event->xbutton.y;
		XDrawLine(XtDisplay(w), XtWindow(w), gcXor, x1, y1, x2, y2);
	}

	int main(int argc, char *argv[])
	{
		int i, n;
		Arg args[10];
		XtAppContext app;
		Widget toplevel;
		XmString str_months[12];

		setlocale(LC_ALL, "");

		XtSetLanguageProc(NULL, NULL, NULL);

		//������������
		toplevel = XtVaAppInitialize(&app, "DrawArea", NULL, 0,
			&argc, argv, NULL, NULL);

		//����drawarea
		n = 0;
		XtSetArg(args[n], XmNwidth, 500 ); 			n++;
		XtSetArg(args[n], XmNheight, 500 ); 			n++;
		drawarea  = XmCreateDrawingArea(toplevel, "drawarea", args, n);
		XtManageChild(drawarea);

		//������ͼ���õ�GC
		prepare();

		XtAddEventHandler(drawarea, ButtonPressMask, FALSE,
			(XtEventHandler)button_pressed, NULL);
		XtAddEventHandler(drawarea, ButtonReleaseMask, FALSE,
			(XtEventHandler)button_released, NULL);
		XtAddEventHandler(drawarea, ButtonMotionMask, FALSE,
			(XtEventHandler)button_motion, NULL);

		//��ʾ����
		XtRealizeWidget(toplevel);

		//�����¼�ѭ��
		XtAppMainLoop(app);

	}

