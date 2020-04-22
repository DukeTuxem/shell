#include "shell.h"

char		**my_str_to_wordtab(char *str)
{
  char		**wordtab;
  t_word	s;

  s.i = 0;
  s.j = 0;
  s.tok = 0;
  s.len_x = 0;
  s.words = cnt_words(str);
  if ((wordtab = malloc(sizeof(char *) * (s.words + 1))) == NULL)
    return (NULL);
  wordtab[s.words] = NULL;
  while (s.words != 0)
    {
      while (!BLANK(str[s.i]) && str[s.i] != 0)
	s.i++;
      s.i++;
      s.len_x = s.i - s.tok;
      s.tok = s.i;
      wordtab[s.j++] = put_word_in_tab(str, s.len_x);
      s.words--;
    }
  wordtab[s.j] = 0;
  return (wordtab);
}

char		*put_word_in_tab(char *str, int len_x)
{
  static int	i = 0;
  int		j;
  char		*s;

  j = 0;
  if ((s = malloc(sizeof(char) * (len_x + 1))) == NULL)
    return (NULL);
  while (str[i] != 0 && !BLANK(str[i]))
    {
      s[j] = str[i];
      i++;
      j++;
    }
  s[j] = 0;
  if (str[i] != 0)
    i++;
  else
    i = 0;
  return (s);
}

int		cnt_words(char *str)
{
  int		i;
  int		words;

  i = -1;
  words = 0;
  while (str[++i])
    if (BLANK(str[i]))
      words++;
  return (words + 1);
}
