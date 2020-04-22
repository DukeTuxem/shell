#include "shell.h"

int	add_in_my_env(char *var_env)
{
  int	lon;

  lon = get_long();
  if ((my_env = realloc(my_env, sizeof(char *) * (lon + 2))) == NULL)
    return (0);
  if ((my_env[lon] = malloc(sizeof(char) * (strlen(var_env) + 1))) == NULL)
    return (0);
  my_env[lon] = var_env;
  my_env[lon + 1] = NULL;
  return (0);
}

int	overwriting(char **cmd)
{
  char	*nam;
  int	i;
  int	a;

  a = strlen(cmd[1]);
  if (cmd[2] == NULL)
    return (overwriting_singlearg(cmd));
  if ((nam = malloc(sizeof(char) * (a + 2))) == NULL)
    return (-1);
  strcpy(nam, cmd[1]);
  nam[a] = '=';
  nam[a + 1] = '\0';
  i = -1;
  while (my_env[++i] != NULL)
    {
      if (strncmp(nam, my_env[i], a + 1) == 0)
	{
	  my_env[i] = realloc(my_env[i], sizeof(char)
			      * (strlen(nam) + strlen(cmd[2]) + 1));
	  my_env[i] = strcat(nam, cmd[2]);
	  return (1);
	}
    }
  return (0);
}

int     overwriting_singlearg(char **cmd)
{
  char  *nam;
  int   i;
  int   a;

  a = strlen(cmd[1]);
  if ((nam = malloc(sizeof(char) * (a + 2))) == NULL)
    return (-1);
  strcpy(nam, cmd[1]);
  nam[a] = '=';
  nam[a + 1] = '\0';
  i = -1;
  while (my_env[++i] != NULL)
    {
      if (strncmp(nam, my_env[i], a + 1) == 0)
        {
          my_env[i] = realloc(my_env[i], sizeof(char) * strlen(nam) + 1);
	  my_env[i] = nam;
	  return (1);
        }
    }
  return (0);
}

char    *strdelim(char **cmd)
{
  int   len1;
  int   len2;
  char  *str;

  len1 = strlen(cmd[1]);
  len2 = 0;
  if (cmd[2] == NULL)
    {
      if ((str = malloc(sizeof(char) * (len1 + 2))) == NULL)
	return (0);
    }
  else
    {
      len2 = strlen(cmd[2]);
      if ((str = malloc(sizeof(char) * (len1 + len2 + 2))) == NULL)
	return (NULL);
    }
  return (cpy_in_str(str, cmd));
}

char	*cpy_in_str(char *str, char **cmd)
{
  int	i;
  int	y;

  i = -1;
  y = -1;
  while (cmd[1][++i] != 0)
    str[i] = cmd[1][i];
  str[i] = '=';
  if (cmd[2] == NULL)
    {
      str[i + 1] = 0;
      return (str);
    }
  while (cmd[2][++y] != 0)
    str[++i] = cmd[2][y];
  str[++i] = 0;
  return (str);
}
