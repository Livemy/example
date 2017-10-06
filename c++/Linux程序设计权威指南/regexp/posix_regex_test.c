#include <stdio.h>
#include <regex.h>

/* pattern buffer �ĳ�ʼ������ */
void
init_pattern_buffer (pattern_buffer)
     regex_t *pattern_buffer;
{
  pattern_buffer->buffer = NULL;
  pattern_buffer->allocated = 0;
  pattern_buffer->used = 0;
  pattern_buffer->fastmap = NULL;
  pattern_buffer->fastmap_accurate = 0;
  pattern_buffer->translate = NULL;
  pattern_buffer->can_be_null = 0;
  pattern_buffer->re_nsub = 0;
  pattern_buffer->no_sub = 0;
  pattern_buffer->not_bol = 0;
  pattern_buffer->not_eol = 0;
}

int
test_posix (pattern_buffer, regex, text)
     regex_t *pattern_buffer;
     char *regex;
     char *text;
{
  int cflags, eflag;
  int n;
  int id;
  char buf[256];

  /* ���� ������ʽ pattern buffer �ĳ�ʼ�� */
  init_pattern_buffer (pattern_buffer);

  /* �趨 ������ʽ ���﷨���� */
  cflags = REG_NEWLINE | REG_EXTENDED;
  /* ���� ������ʽ */
  id = regcomp (pattern_buffer, regex, cflags);
  /* ����Ƿ��д���ķ��� */
  if (id != 0)
    {
      printf (" error on compiling regex. code = %d\n", id);
      regerror (id, pattern_buffer, buf, sizeof (buf));
      printf (" error : %s\n", buf);
      exit (1);
    }
  /* ���趨ִ�н���Ѱ�ҵ��ر��� */
  eflag = 0;
  /* ���ַ��� text �н���Ѱ�ң����г��䷵��ֵ */
  n = regexec (pattern_buffer, text, 0, 0, eflag);
  if (n == 0)
    {
      printf (" regexec match string = %s\n", text);
    }
  return n;
}

main (argc, argv)
     int argc;
     char **argv;
{
  FILE *fp;
  char line[1024];
  regex_t pattern_buffer;

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

  /* ��ȡ�����ļ��е��ַ��������� POSIX �ӿ� Regex ����Ĳ��� */
  while (fgets (line, 1024, fp) != NULL)
    {
      test_posix (&pattern_buffer, argv[1], line);
    }

  /* �ͷ�������ʽ pattern buffer */
  regfree (&pattern_buffer);
  /* �رղ��Ե��ļ� */
  fclose (fp);
}
