#include "shell.h"

void		str_mov(unsigned int *i, int *y, char *tmp)
{
  *i += 2;
  if ((*y -= 2) < 0)
    *y = 0;
  while (*y > 0 && tmp[*y] != '/')
    *y = *y - 1;
}

char		*rm_point(char *str)
{
  unsigned int	i;
  int		y;
  char		*tmp;

  if ((tmp = malloc(sizeof(char) * strlen(str) + 100)) == NULL)
    return (NULL);
  i = 0;
  y = 0;
  while (str[i])
    {
      if (str[i] == '.' && (str[i + 1] == '/' || str[i + 1] == '\0'))
	i++;
      if (str[i] == '.' && str[i + 1] == '.')
	str_mov(&i, &y, tmp);
      if (str[i] != '\0')
	  tmp[y++] = str[i++];
    }
  while (y > 1 && tmp[y - 1] == '/')
    y--;
  tmp[y] = '\0';
  free(str);
  return (tmp);
}

int		change_oldpwd(char *tmp, char **cmd)
{
  int		y;
  int		i;
  char		*new_pwd;

  y = 0;
  i = 0;
  if ((new_pwd = malloc(sizeof(char) * strlen(tmp) + 10)) == NULL)
    return (my_puterror("Malloc failed"));
  while (strncmp(my_env[i], "PWD=", strlen("PWD=")) != 0)
    i++;
  while (my_env[y] && strncmp(my_env[y], "OLDPWD=", strlen("OLDPWD=")) != 0)
    y++;
  if (my_env[y] == NULL)
    return (my_puterror("Can't find OLDPWD\n"));
  free(my_env[y]);
  if ((my_env[y] = malloc(sizeof(char) * strlen(my_env[i]) + 15)) == NULL)
    return (my_puterror("Malloc failed"));
  my_env[y] = strcpy(my_env[y], "OLDPWD=/");
  strcat(my_env[y], &my_env[i][5]);
  new_pwd = strcat(strcpy(new_pwd, "PWD="), tmp);
  free(my_env[i]);
  my_env[i] = new_pwd;
  if (cmd[1] != NULL && cmd[1][0] == '-')
    puts(&new_pwd[4]);
  return (0);
}

int		chdir_err(char *str)
{
  my_puterror(str);
  my_puterror(" : ");
  if (errno == ENOENT)
    return (my_puterror("Directory name not found\n"));
  else if (errno == EACCES)
    return (my_puterror("Permission denied\n"));
  else if (errno == ENOTDIR)
    return (my_puterror("The file is not a directory\n"));
  else
    return (my_puterror("Directory not accessible\n"));
}

int		gere_cd(char **cmd)
{
  char		*tmp;

  errno = 0;
  if (cmd[1] == NULL)
    tmp = str_null();
  else if (cmd[1][0] == '-')
    tmp = old_pwd();
  else if (cmd[1][0] == '/')
    tmp = cmd[1];
  else
    tmp = prepare_str(cmd[1]);
  if (tmp == NULL)
    return (1);
  if (chdir(tmp) == -1)
    return (chdir_err(cmd[1]));
  tmp = rm_point(tmp);
  if (change_oldpwd(tmp, cmd) == 1)
    return (1);
  return (0);
}
