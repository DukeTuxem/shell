#include "shell.h"

char	**clean_cmd(char **old_cmd)
{
  char	**new_cmd;
  int	i;
  int	y;

  i = 0;
  y = 0;
  if ((new_cmd = malloc(sizeof(char *) * 1000)) == NULL)
    return (NULL);
  while (old_cmd[i] != NULL)
    {
      if (old_cmd[i][0] != '\0' || old_cmd[i][0] == '\n')
	{
	  new_cmd[y] = strdup(old_cmd[i]);
	  y++;
	}
      i++;
    }
  new_cmd[y] = NULL;
  return (new_cmd);
}
