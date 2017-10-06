// ft2string.c
//      ���������� FreeType 2 �������һ���ı��� TrueType �ֿ���ʾ��
//      һ�� X �����
//

// ��׼ͷ�ļ�
#include <stdio.h>
#include <stdlib.h>
#include <stdarg.h>
#include <string.h>
#include <locale.h>

// X11 ͷ�ļ�
#include <X11/Xlib.h>
#include <X11/Xutil.h>

// FreeType 2 ͷ�ļ�
#include <freetype/freetype.h>

// X ���ڵĿ�Ⱥ͸߶�
#define WINDOW_WIDTH 600
#define WINDOW_HEIGHT 400

// ���ֻ��ʾ 256 ���ַ�
#define MAX_GLYPHS 256

Display *display;
Window win;			// ����ID
GC gc;				// ͼ�λ���
XVisualInfo vis;		// Visual ��Ϣ
XColor rgb[256];

// ���彫���� X ������ʾ������ͼ��ṹ
typedef struct
{
  XImage *img;			// ���ε� X ͼ��
  int left;			// ����ͼ���������
  int top;			// ����ͼ��Ķ������
  int advance_x;		// ���ε�ˮƽ����
  int advance_y;		// ���εĴ�ֱ����
}
Glyph_Image;

Glyph_Image gi[MAX_GLYPHS];	// ��� MAX_GLYPHS ������ X ͼ��

FT_Library library;		// FreeType ��
FT_Face face;			// �������
FT_Error error;			// FreeType �������

char *prog;			// ������
unsigned char *text = "��ӭ���� Linux ���������磡";
					// ����ʾ���ı���ȱʡ�ı�����
wchar_t unicode_text[MAX_GLYPHS];	// �ı��� Unicode ����
int num_glyphs;			// ������Ŀ
int pixel_size = 50;		// ��ʾ�������ش�С��ȱʡΪ 50
int resolution = 72;		// �ֱ��ʣ�ȱʡΪ 72
int grayscale = 0;		// �Ƿ�ʹ�ûҶ���ʾ��ȱʡΪ��ʹ�ûҶ���ʾ
char *font_filename = NULL;	// �ֿ��ļ������û������ṩ

void parse_args ();		// ���������в���
void text_to_unicode ();	// ���ı�ת��Ϊ Unicode ����
void init_display ();		// ��ʼ�� X ����
void render_glyph ();		// ��������ͼ���λͼ����ɫͼ��Ҷ�ͼ��
void render_image ();		// �������ε� X ͼ��XImage��
void draw_image ();		// �� X �����ﻭ���ı�ͼ��
void event_loop ();		// X �¼�ѭ��
void usage ();			// ʹ��˵��
void fatal_error (const char *msg, ...);	// FreeType ����������������


int
main (int argc, char **argv)
{
  int i;

  // ���������в�������ȡ������Ϣ
  //    �ֿ��ļ���
  //    ��ʾ�������ش�С
  //    �ֱ���
  //    �Ƿ�ʹ�ûҶ���ʾ
  //    ����ʾ���ı�
  parse_args (argc, argv);

  // ��ʼ��һ���µ� FreeType ����� library
  error = FT_Init_FreeType (&library);
  if (error)
    fatal_error ("couldn't initialize FreeType library.");

  // Ϊ�ֿ��ļ� font_filename �еĵ�һ�����崴��һ���µ�������� face
  error = FT_New_Face (library, font_filename, 0, &face);
  if (error == FT_Err_Unknown_File_Format)
    fatal_error ("unsupported font format in file '%s'.", font_filename);
  else if (error)
    fatal_error ("unable to open input file '%s'.", font_filename);

  // ѡ��������� face �е� Unicode �ַ����Ϊȱʡ���
  error = FT_Select_Charmap (face, ft_encoding_unicode);
  if (error)
    fatal_error ("couldn't select Unicode charmap.");

  // �������� face ���ַ���Ⱥ͸߶ȶ�Ϊ pixel_size ������
  // ˮƽ�ʹ�ֱ�ֱ��ʶ�Ϊ resolution dpi
  error = FT_Set_Char_Size (face,
			    pixel_size * 64, pixel_size * 64,
			    resolution, resolution);
  if (error)
    fatal_error ("couldn't set character size: pixel size %d, resolution %d.",
		 pixel_size, resolution);

  // �ѽ���ʾ���ı�ת��Ϊ Unicode ����
  text_to_unicode ();

  // ��ʼ�� X ����
  init_display ();

  // ���� Unicode ������ı��������ַ�������һ����
  for (i = 0; i < num_glyphs; i++)
    {
      // ���ɵ� i �� Unicode �ַ�������ͼ���λͼ����ɫͼ��Ҷ�ͼ��
      render_glyph (unicode_text[i], grayscale);

      // ���ɵ� i �����ε� X ͼ��XImage����������������Ϣ��
      //        ����λͼ��������
      //        ����λͼ�Ķ������
      //        ���ε�ˮƽ����
      //        ���εĴ�ֱ����
      render_image (i, face->glyph->bitmap.buffer,
		    face->glyph->bitmap.rows, face->glyph->bitmap.pitch,
		    face->glyph->bitmap_left, face->glyph->bitmap_top,
		    face->glyph->advance.x / 64, face->glyph->advance.y / 64,
		    grayscale);
    }

  // �� X �����У���λ�� x = 0��y = pixel_size * resolution / 72
  // ��ʼ�����ı��������ַ���ͼ��
  draw_image (0, pixel_size * resolution / 72);

  // X �¼�ѭ��
  event_loop ();

  // ����������� face �����������Ӷ���
  FT_Done_Face (face);

  // ���� FreeType ����� library ���������к��
  FT_Done_FreeType (library);

  return 0;
}


// ���������в���
void
parse_args (int argc, char **argv)
{
  int i;

  prog = argv[0];
  if (argc == 1)
    usage ();

  for (i = 1; i < argc; i++)
    {
      switch (argv[i][0])
	{
	case '-':
	  switch (argv[i][1])
	    {
	    case 'p':
	      if (i + 1 < argc && argv[i + 1][0] != '-')
		pixel_size = strtol (argv[++i], (char **) NULL, 10);
	      break;
	    case 'r':
	      if (i + 1 < argc && argv[i + 1][0] != '-')
		resolution = strtol (argv[++i], (char **) NULL, 10);
	      break;
	    case 'f':
	      if (i + 1 < argc && argv[i + 1][0] != '-')
		font_filename = argv[++i];
	      break;
	    case 'g':
	      grayscale = 1;
	      break;
	    default:
	      break;
	    }
	  break;
	default:
	  text = argv[i];
	  break;
	}
    }

  if (font_filename == NULL)
    {
      fprintf (stderr,
	       "ERROR: You must provide a TrueType font file name!\n");
      exit (1);
    }

  if (pixel_size == 0 || pixel_size == LONG_MAX)
    {
      fprintf (stderr, "ERROR: Illegal pixel size: %d.\n", pixel_size);
      exit (1);
    }

  if (resolution == 0 || resolution == LONG_MAX)
    {
      fprintf (stderr, "ERROR: Illegal resolution: %d.\n", resolution);
      exit (1);
    }

  // ��ӡ�������в���
  printf ("font_filename: %s\n", font_filename);
  printf ("pixel_size: %d\n", pixel_size);
  printf ("resolution: %d\n", resolution);
  printf ("grayscale: %d\n", grayscale);
  printf ("text: %s\n", text);
}


// ���� locale �� mbstowcs() �������ı�ת��Ϊ Unicode ����
void
text_to_unicode ()
{
  char *old_locale, *saved_locale;
  int length;
  int i;

  // ��ȡ��ǰ locale �� LC_CTYPE ����趨
  old_locale = setlocale (LC_CTYPE, NULL);

  // ���浱ǰ locale �� LC_CTYPE ����趨
  saved_locale = strdup (old_locale);

  // ���� LC_CTYPE Ϊһ�ּ������� locale
  setlocale (LC_CTYPE, "zh_CN");

  length = strlen (text);
  if (length > 256)
    length = 256;

  // �������ı�ת��Ϊ Unicode ����
  // ����ת����� Unicode �ַ�����������Ҫ������������������ֻȡ 256 ��
  num_glyphs = mbstowcs (unicode_text, text, length);

  // ��ӡ��������
  printf ("number of glyphs: %d\n", num_glyphs);

  // ��ӡ�����ַ��� Unicode ����
  printf ("unicode text:");
  for (i = 0; i < num_glyphs; i++)
    {
      printf (" %x", (unsigned int) unicode_text[i]);
    }
  printf ("\n");

  // �ָ��� locale �� LC_CTYPE ������
  setlocale (LC_CTYPE, saved_locale);

  free (saved_locale);
}


// ���� Unicode ����Ϊ charcode ���ַ�������ͼ���λͼ����ɫͼ��Ҷ�ͼ��
void
render_glyph (unsigned long charcode, int gray)
{
  int glyph_index;		// �����е�����������

  // �� Unicode ���� charcode ת��Ϊ���� face �ж�Ӧ������������
  glyph_index = FT_Get_Char_Index (face, charcode);

  if (glyph_index != 0)
    {
      int flags;

      // ����ʹ��ȱʡģʽ�������Σ�������Ƕλͼ������������
      // ʸ�����Ǳ����Ų����ϸ��
      flags = FT_LOAD_DEFAULT;

      // ��ʹ�ûҶ���ʾʱ��������������������Ƕ��������λͼ��
      // ����������������ͼ��
      if (gray)
	flags |= FT_LOAD_NO_BITMAP;

      // ������ face �а� flags �趨��ģʽ��������������Ϊ glyph_index
      // ������ͼ��
      error = FT_Load_Glyph (face, glyph_index, flags);
      if (error)
	fatal_error ("couldn't load glyph.");

      // ������ͼ�� face->glyph ת��Ϊ�Ҷ�λͼ��ɫλͼ
      if (gray)
	error = FT_Render_Glyph (face->glyph, ft_render_mode_normal);
      else
	error = FT_Render_Glyph (face->glyph, ft_render_mode_mono);
      if (error)
	fatal_error ("couldn't render glyph.");

    }
}

// ���� Unicode �����ı��е� num ���ַ�λͼ bit_data �� X ͼ��XImage����
// ������������Ϣ��
//      ����λͼ�������� left
//      ����λͼ�Ķ������ top
//      ���ε�ˮƽ���� advance_x
//      ���εĴ�ֱ���� advance_y
void
render_image (int num, unsigned char *bit_data,
	      int rows, int cols,
	      int left, int top, int advance_x, int advance_y, int gray)
{
  int i, j;
  int img_width;		// λͼ���
  int img_size;			// λͼ�ߴ�
  unsigned char *bitmap;	// ���� XImage �е�λͼ

  if (gray)
    img_width = cols;
  else
    img_width = ((cols + 1) & -2) * 8;

  // ��λͼ bitmap �����ڴ�ռ�
  img_size = cols * rows * 2;
  bitmap = (unsigned char *) malloc (img_size);

  // ��λͼ bitmap ��ʼ��Ϊȫ��
  memset (bitmap, 0, img_size);

  // ����λͼ�������������
  gi[num].left = left;
  gi[num].top = top;
  gi[num].advance_x = advance_x;
  gi[num].advance_y = advance_y;

  // ���� XImage
  gi[num].img = XCreateImage (display,
			      vis.visual,
			      gray ? vis.depth : 1,
			      gray ? ZPixmap : XYBitmap,
			      0, bitmap, img_width, rows, 8, 0);

  // �ڵ�ɫλͼ�����У���������������߱�־λ��Most Significant Bit����ʾ
  if (!gray)
    {
      gi[num].img->byte_order = MSBFirst;
      gi[num].img->bitmap_bit_order = MSBFirst;
    }

  // ��������λͼ�� XImage ��ֵ
  for (j = 0; j < rows; j++)
    for (i = 0; i < cols; i++)
      {
	unsigned char c = bit_data[i + j * cols];
	if (gray)
	  gi[num].img->f.put_pixel (gi[num].img, i, j, rgb[c].pixel);
	else
	  bitmap[i + j * img_width / 8] = c;
      }
}


// �� X �����У���λ�� x = start_x��y = start_y ��ʼ�����ı��������ַ���ͼ��
void
draw_image (int start_x, int start_y)
{
  int i;
  for (i = 0; i < num_glyphs; i++)
    {
      // �����Ҫ���ﴰ���ұ߽磬������һ�С���ʼ��д
      if (start_x + gi[i].img->width >= WINDOW_WIDTH)
	{
	  start_x = 0;
	  start_y += pixel_size * resolution / 72;
	}

      // ������ǰ������ͼ�󣬸�������������Ͷ�������������ͼ���λ��
      XPutImage (display, win, gc, gi[i].img, 0, 0,
		 start_x + gi[i].left, start_y - gi[i].top,
		 gi[i].img->width, gi[i].img->height);

      // ���ݵ�ǰ���εĲ�����������һ������ͼ�����ʼλ��
      start_x += gi[i].advance_x;
      start_y += gi[i].advance_y;
    }
}


// ��ʼ�� X ����
void
init_display ()
{
  int i;
  int screen_num;
  unsigned int win_width, win_height;	// ���ڳߴ�
  unsigned int border_width = 4;	// �߽�հ�
  char *display_name = NULL;
  Colormap default_cmap;	// ��ɫ��
  XVisualInfo *vlist;		// Visual ��Ϣ
  int depth;			// ������ɫ���
  int match;			// �����ϵ� Visual �ṹ

  // �� X ����������
  if ((display = XOpenDisplay (display_name)) == NULL)
    {
      printf ("Cannot connect to X server %s\n", XDisplayName (display_name));
      exit (-1);
    }

  // ���ȱʡ�� screen_num
  screen_num = DefaultScreen (display);

  // ����ͼ�λ���
  gc = DefaultGC (display, screen_num);

  // �����ɫ���
  depth = DefaultDepthOfScreen (DefaultScreenOfDisplay (display));

  // ��ȡȱʡ����ɫ��
  default_cmap = DefaultColormap (display, screen_num);

  // ���Visual��Ϣ
  vis.screen = screen_num;
  vlist = XGetVisualInfo (display, VisualScreenMask,	// ����
			  &vis,	// ����visual
			  &match);	// �����ϵ�Visual�ṹ
  if (!vlist)
    {
      printf ("No matched visuals\n");
      exit (1);
    }
  vis = vlist[0];
  XFree (vlist);

  // ���ûҶȼ���ɫ��
  for (i = 0; i < 256; i++)
    {
      rgb[i].red = rgb[i].green = rgb[i].blue = 65535 - (i * 65535) / 256;
      rgb[i].flags = DoRed | DoGreen | DoBlue;
      XAllocColor (display, default_cmap, &rgb[i]);
    }

  win_width = WINDOW_WIDTH;	// ���ڿ��
  win_height = WINDOW_HEIGHT;	// ���ڸ߶�

  // ��������
  win = XCreateSimpleWindow (display, RootWindow (display, screen_num),	//������
			     0, 0, win_width, win_height,	//λ�úʹ�С
			     border_width,	//�߽���
			     BlackPixel (display, screen_num),	//ǰ��ɫ
			     WhitePixel (display, screen_num));	//����ɫ

  // ѡ�񴰿ڸ���Ȥ���¼�����
  XSelectInput (display, win, ExposureMask | KeyPressMask | ButtonPressMask);

  // ��ʾ����
  XMapWindow (display, win);
}


// X �¼�ѭ��
void
event_loop ()
{
  int i;
  int is_exit = 0;		// �˳���־

  XEvent report;

  // �����¼�ѭ��
  while (!is_exit)
    {
      // ȡ�ö����е��¼�
      XNextEvent (display, &report);

      switch (report.type)
	{

	  // �ع��¼�, ����Ӧ�ػ�
	case Expose:
	  // ȡ�����һ���ع��¼�
	  if (report.xexpose.count != 0)
	    break;

	  // �ػ�ͼ��
	  draw_image (0, pixel_size * resolution / 72);
	  break;

	  // ��������а���, �ͷ���Դ�󷵻�������
	case ButtonPress:
	case KeyPress:
	  for (i = 0; i < num_glyphs; i++)
	    XDestroyImage (gi[i].img);
	  XFreeGC (display, gc);
	  is_exit = 1;

	default:
	  break;
	}
    }
}


// FreeType ����������������
void
fatal_error (const char *msg, ...)
{
  va_list ap;

  va_start (ap, msg);
  fprintf (stderr, "%s: error code 0x%04lx: ", prog, (long unsigned) error);
  vfprintf (stderr, msg, ap);
  fprintf (stderr, "\n");
  va_end (ap);

  exit (-1);
}


// ʹ��˵��
void
usage ()
{
  fprintf (stderr, "\n");
  fprintf (stderr, "Usage:\n");
  fprintf (stderr, "\n");
  fprintf (stderr,
	   "%s -f font_filename [-p pixel_size] [-r resolution] [-g] [text_to_display]\n",
	   prog);
  fprintf (stderr, "\n");
  fprintf (stderr, "\t-g\tUse grayscale to render text.\n");
  fprintf (stderr, "\n");
  fprintf (stderr, "\tDefault pixel size is 50.\n");
  fprintf (stderr, "\tDefault resolution is 72.\n");
  fprintf (stderr, "\tDefault is not using grayscale.\n");
  fprintf (stderr, "\tDefault text string is \"%s\"\n", text);
  fprintf (stderr, "\n");
  exit (1);
}

// ���� ft2string.c �����һ�С�This is the end of ft2string.c.
