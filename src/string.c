#include "shell.h"

char	*my_strcpy(char *src, char *dst)
{
  int	i;
  int	y;

  i = -1;
  y = -1;
  if (src == NULL || dst == NULL)
    return (NULL);
  while (src[++i])
    dst[++y] = src[i];
  dst[++y] = 0;
  return (dst);
}

char	*my_strcat(char *path, char *cmd)
{
  char	*tmp;
  int	len_p;
  int	len_c;
  int	i;
  int	j;

  i = -1;
  j = 0;
  len_p = strlen(path);
  len_c = strlen(cmd);
  if ((tmp = malloc(sizeof(char) * ((len_p + len_c) + 2))) == NULL)
    return (NULL);
  while (path[++i] != '\0')
    {
      tmp[j++] = path[i];
      if (path[i + 1] == 0 && path[i] != '/')
        tmp[j++] = '/';
    }
  i = -1;
  while (cmd[++i] != '\0')
    tmp[j++] = cmd[i];
  tmp[j] = '\0';
  return (tmp);
}

void	set_brek(void *type, char *errstr)
{
  brek = 1;
  if (errstr)
    {
      my_puterror(errstr);
      my_puterror("\n");
    }
  if (type)
    free(type);
  free_elem(my_env);
  free_elem(my_path);
}

void	free_elem(char **elem)
{
  int	y;

  y = -1;
  while (elem[++y])
    free(elem[y]);
  free(elem);
}
