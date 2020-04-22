#include "shell.h"

char	*get_usr_cmd(void)
{
  char	*usr_cmd;
  int	red_size;

  usr_cmd = NULL;
  if ((usr_cmd = malloc(sizeof(char) * BUFF_SIZE + 1)) == NULL)
    set_brek(NULL, "Malloc failed");
  red_size = read(0, usr_cmd, BUFF_SIZE);
  if (red_size == -1)
    set_brek(usr_cmd, "Read failed");
  if (red_size == 0)
    set_brek(usr_cmd, "\0");
  if (brek == 1)
    return (NULL);
  if (red_size > 1)
    usr_cmd[red_size - 1] = '\0';
  else if (red_size == 1 || is_empty(usr_cmd) == 1)
    usr_cmd[0] = '\0';
  if (usr_cmd[0] != 0)
    usr_cmd = epur_spaces(usr_cmd);
  return (usr_cmd);
}

char	*epur_spaces(char *str)
{
  int	i;
  int	y;

  i = 0;
  y = 0;
  while (str[i] && BLANK(str[i]))
    i++;
  while (str[i] != '\0')
    {
      while (BLANK(str[i]))
        {
	  if ((str[i + 1] != ' ' && str[i + 1] != '\t') && str[i + 1] != '\0')
            str[y++] = ' ';
          i++;
        }
      while (str[i] != '\0' && !BLANK(str[i]))
	str[y++] = str[i++];
    }
  if (str[y - 1] == ' ')
    str[y - 1] = '\0';
  str[y] ='\0';
  return (str);
}

int	is_empty(char *str)
{
  int	i;
  int	len;
  int	spaces;

  i = -1;
  spaces = 0;
  len = strlen(str);
  while (str[++i])
    if (BLANK(str[i]))
      spaces++;
  if (spaces == len)
    return (1);
  if ((BLANK(str[0]) && str[1] == 0) || str[0] == 0)
    return (1);
  return (0);
}

char	*spaces_in_str(char *str)
{
  char	*tmp;
  int	i;
  int	y;

  i = 0;
  y = 0;
  if ((tmp = malloc(sizeof(char) * strlen(str) + 100)) == NULL)
    return (NULL);
  while (str[i])
    {
      if (str[i] == '>' || str[i] == '<')
	{
	  if (i > 1 && (str[i - 1] != ' ' && str[i - 1] != '\t'))
	      tmp[y++] = ' ';
	  tmp[y++] = str[i++];
	  if (str[i] == str[i - 1])
	    tmp[y++] = str[i++];
	  if (str[i] && (str[i] != ' ' && str[i] != '\t'))
	    tmp[y++] = ' ';
	}
      if (str[i])
	tmp[y++] = str[i++];
    }
  tmp[y] = '\0';
  return (tmp);
}
