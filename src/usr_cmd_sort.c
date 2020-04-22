#include "shell.h"

int	find_separator(char *str, char **sep)
{
  int	i;
  int	y;

  i = 0;
  while (sep[i] != NULL)
    {
      y = strlen(str) -1;
      while (y >= 0)
        {
          if ((strlen(sep[i]) == 2 &&
               (sep[i][0] == str[y] && sep[i][1] == str[y + 1])) ||
              (strlen(sep[i]) == 1 && sep[i][0] == str[y]))
            return (y + strlen(sep[i]) - 1);
          y--;
        }
      i++;
    }
  return (-1);
}

char	*copy_sep(char *dest, char *src, int i)
{
  int	y;

  y = 0;
  dest[y] = src[i];
  y++;
  if (src[i - 1] == src[i])
    {
      dest[y] = src[i];
      y++;
    }
  dest[y] = '\0';
  return (dest);
}

char	*clean_str(char *str)
{
  int	i;
  int	y;

  i = 0;
  y = 0;
  while (str[i] == '|' || str[i] == ';' || str[i] == '&')
    i++;
  while (str[i] != '\0')
    {
      str[y] = str[i];
      y++;
      i++;
    }
  str[y] = '\0';
  return (str);
}

char	*cut_left_str(char *str, int i)
{
  char	*left_cmd;
  int	y;

  if ((left_cmd = malloc(sizeof(char) * i + 1)) == NULL)
    return (NULL);
  y = 0;
  while (y < i)
    {
      left_cmd[y] = str[y];
      y++;
    }
  if (left_cmd[y - 1] == '|' || left_cmd[y - 1] == '&')
    y--;
  left_cmd[y] = '\0';
  epur_spaces(left_cmd);
  left_cmd = clean_str(left_cmd);
  return (left_cmd);
}

char	*cut_right_str(char *str, int i)
{
  char	*right_cmd;
  int	y;

  if ((right_cmd = malloc(sizeof(char) * strlen(str) - i + 1)) == NULL)
    return (NULL);
  y = 0;
  while (str[i] != '\0')
    {
      right_cmd[y] = str[i];
      i++;
      y++;
    }
  right_cmd[y] = '\0';
  right_cmd = epur_spaces(right_cmd);
  right_cmd = clean_str(right_cmd);
  right_cmd = epur_spaces(right_cmd);
  return (right_cmd);
}
