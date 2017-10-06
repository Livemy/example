// File: langinfo.c

// �����ȡÿ�� locale ��Ϣʹ�õ������Ŷ�Ӧ�ĺ�
#include <langinfo.h>

main ()
{
  unsigned char *s;
  int i;

  // ���� locale
  setlocale (LC_ALL, "");

  // ��ӡ��ǰ locale �����������ı�ʾ
  printf ("Morning: %s\n", nl_langinfo (AM_STR));
  printf ("Afternoon: %s\n", nl_langinfo (PM_STR));

  // ��ӡ��ǰ locale ��ÿ��������ı�ʾ
  for (i = 0; i < 7; i++)
    {
      printf ("No.%d day of the week: %s\n", i + 1, nl_langinfo (DAY_1 + i));
    }
}
