#include "shell.h"

char	*prepare_str(char *str)
{
  char	*tmp;
  int	i;

  i = 0;
  while (my_env[i] && strncmp(my_env[i], "HOME=", strlen("HOME=")) != 0)
    i++;
  if (str[0] != '~')
    {
      i = 0;
      while (my_env[i] && strncmp(my_env[i], "PWD=", strlen("PWD=")) != 0)
	i++;
    }
  if (my_env[i] == NULL)
    {
      my_puterror("Can't find the wanted environement variable\n");
      return (NULL);
    }
  if ((tmp = malloc(sizeof(char) * strlen(&my_env[i][5]) + strlen(str)
		    + 10)) == NULL)
       return (NULL);
  if (str[0] != '~')
    tmp = strcat(strcat(strcpy(tmp, &my_env[i][4]), "/"), str);
  else
    tmp = strcat(strcat(strcpy(tmp, &my_env[i][5]), "/"), &str[2]);
  return (tmp);
}

char	*str_null()
{
  int	i;
  char	*str;

  i = 0;
  while (my_env[i] && strncmp(my_env[i], "HOME=", strlen("HOME=")) != 0)
    i++;
  if (my_env[i] == NULL)
    {
      my_puterror("Can't find HOME\n");
      return (NULL);
    }
  str = strdup(&my_env[i][5]);
  return (str);
}

char	*old_pwd()
{
  int	i;
  char	*str;

  i = 0;
  while (my_env[i] && strncmp(my_env[i], "OLDPWD=", strlen("OLDPWD=")) != 0)
    i++;
  if (my_env[i] == NULL)
    {
      my_puterror("Can't find OLDPWD\n");
      return (NULL);
    }
  str = strdup(&my_env[i][7]);
  return (str);
}
