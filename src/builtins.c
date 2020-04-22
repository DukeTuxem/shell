#include "shell.h"

int	check_for_builtins(char **cmd, int *s)
{
  int	(*ptr[6])(char **);
  char	**builts;
  int	i;

  i = -1;
  ptr[0] = &gere_cd;
  ptr[1] = &my_echo;
  ptr[2] = &my_setenv;
  ptr[3] = &my_unsetenv;
  ptr[4] = &print_env;
  ptr[5] = &my_exit;
  builts = my_str_to_wordtab("cd echo setenv unsetenv env exit");
  while (builts[++i] != NULL)
    if (strcmp(cmd[0], builts[i]) == 0)
      {
	*s = ptr[i](cmd);
	if (*s == 1)
	  *s = 512;
	return (0);
      }
  return (1);
}

int	my_setenv(char **cmd)
{
  int	nb_args;

  nb_args = -1;
  cmd = clean_cmd(cmd);
  while (cmd[++nb_args] != NULL);
  if (nb_args > 3)
    {
      my_puterror("Too many arguments\n");
      return (-1);
    }
  else if (nb_args == 1)
    print_env(my_env);
  else
    {
      if (overwriting(cmd) == 1)
	return (0);
      add_in_my_env(strdelim(cmd));
      my_env = clean_cmd(my_env);
    }
  return (0);
}

int	my_unsetenv(char **cmd)
{
  int	pos;
  int	nb_args;

  nb_args = -1;
  cmd = clean_cmd(cmd);
  while (cmd[++nb_args] != NULL);
  if (nb_args == 1 || nb_args > 2)
    {
      if (nb_args == 1)
	my_puterror("Too few arguments \n");
      else
	my_puterror("Too many arguments \n");
      return (-1);
    }
  pos = check_env(cmd);
  if (pos == -1)
    return (512);
  pos--;
  while (my_env[++pos])
    my_env[pos] = my_env[pos + 1];
  return (0);
}

int	print_env(char **cmd)
{
  int	y;

  if (cmd[1] != NULL)
    {
      my_puterror(cmd[1]);
      return (my_puterror(" : No such file or directory.\n"));
    }
  while (my_env[++y])
    {
      my_putstr(my_env[y]);
      if (my_env[y + 1] != NULL)
	my_putchar('\n');
    }
  my_putchar('\n');
  return (0);
}

int	my_exit(char **usr_cmd)
{
  if (usr_cmd[1] && usr_cmd[2] != NULL)
    return (my_puterror("exit : too many arguments"));
  else
    brek = 1;
  return (0);
}
