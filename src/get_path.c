#include "shell.h"

void		path_to_use(void)
{
  static int	calls = 0;
  char		*path;
  char		*new_path;

  if (calls != 0)
    free_elem(my_path);
  path = path_from_env();
  new_path = epur_path(path);
  my_path = my_str_to_wordtab(new_path);
  free(path);
  calls++;
}

char	*path_from_env(void)
{
  char	*path;
  int	i;
  int	x;
  int	y;

  i = -1;
  x = -1;
  y = -1;
  path = NULL;
  while (my_env[++y])
    if (strncmp(my_env[y], "PATH=", 5) == 0)
      {
	if ((path = malloc(sizeof(char) * strlen(my_env[y]) + 1)) == NULL)
	  return (NULL);
	my_env[y] += 5;
	while (my_env[y][x])
	  path[++i] = my_env[y][++x];
	my_env[y] -= 5;
	path[++i] = '\0';
      }
  return (path);
}

char	*epur_path(char *str)
{
  int	i;

  i = 0;
  while (str[++i])
    if (str[i] == ':' && str[i + 1] != '\0')
      str[i] = 32;
  return (str);
}
