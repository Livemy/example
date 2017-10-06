#include <stdio.h>
#include <regex.h>

int
test_bsd (regex, text)
     char *regex;
     char *text;
{
  int n;
  const char *id;

  re_syntax_options = RE_SYNTAX_GREP;
  /* ����������ʽ */
  id = (char*) re_comp (regex);
  /* ����Ƿ��д���ķ��� */
  if (id != NULL)
    {
      printf (" error on compiling regex. code = %s\n", id);
      exit (1);
    }

  /* ���ַ��� text �н���Ѱ�ң����г��䷵��ֵ */
  n = re_exec (text);
  if (n == 1)
    {
      printf (" re_exec match string = %s\n", text);
    }
  return n;
}

main (argc, argv)
     int argc;
     char **argv;
{
  FILE *fp;
  char line[1024];

  /* �������ĸ��� */
  if (argc != 3)
    {
      printf ("Usage: %s pattern file\n", argv[0]);
      exit (1);
    }
  /* �򿪲��Ե��ļ� */
  fp = fopen (argv[2], "r");
  if (fp == NULL)
    {
      fprintf (stderr, "Can't open %s.\n", argv[2]);
      exit (1);
    }

  /* ��ȡ�����ļ��е��ַ��������� BSD ���ݽӿ� Regex ����Ĳ��� */
  while (fgets (line, 1024, fp) != NULL)
    {
      test_bsd (argv[1], line);
    }
  /* �رղ��Ե��ļ� */
  fclose (fp);
}
