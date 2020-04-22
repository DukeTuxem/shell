#include "shell.h"

char	**get_env(void)
{
  int	size;
  int	y;

  y = 0;
  size = 0;
  while (environ[++size] != NULL);
  if ((my_env = malloc(sizeof(char *) * (size + 1))) == NULL)
    set_brek(NULL, "Malloc failed");
  if (brek == 1)
    return (NULL);
  while (environ[y])
    {
      if ((my_env[y] = malloc(sizeof(char)
			      * (strlen(environ[y]) + 1))) == NULL)
        set_brek(NULL, "Malloc failed");
      if (brek == 1)
        return (NULL);
      my_env[y] = strcpy(my_env[y], environ[y]);
      y++;
    }
  my_env[y] = NULL;
  return (my_env);
}

int	get_long(void)
{
  int	cnt;

  cnt = -1;
  while (my_env[++cnt] != NULL);
  return (cnt);
}
