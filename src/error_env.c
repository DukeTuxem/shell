#include "shell.h"

int	check_env(char **cmd)
{
  char	*name;
  char	*nam;
  int	i;
  int	a;

  name = cmd[1];
  a = strlen(name);
  if ((nam = malloc(sizeof(char) * (a + 2))) == NULL)
    return (-1);
  nam = strcpy(nam, name);
  nam[a] = '=';
  nam[a + 1] = '\0';
  i = -1;
  while (my_env[++i] != NULL)
    if (strncmp(nam, my_env[i], strlen(nam)) == 0)
      return (i);
  return (-1);
}
