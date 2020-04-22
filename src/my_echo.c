#include "shell.h"

int	my_echo(char **usr_cmd)
{
  if (usr_cmd[1] == NULL)
    {
      my_putchar('\n');
      return (1);
    }
  if (echo_error(usr_cmd) == 0)
    {
      aff_echo_doll(usr_cmd);
      my_putchar('\n');
      return (0);
    }
  else
    return (1);
}

void	aff_echo_doll(char **usr_cmd)
{
  int	a;

  a = 1;
  while (usr_cmd[a] != NULL)
    {
      if (usr_cmd[a][0] == '$' && usr_cmd[a][1] != '\0')
	{
	  if (a > 1)
	    my_putchar(' ');
	  echo_mult_doll(usr_cmd[a]);
	}
      else
	{
	  if (a > 1)
	    my_putchar(' ');
	  my_putstr(usr_cmd[a]);
	}
     a++;
    }
}

int	echo_mult_doll(char *usr_cmd)
{
  char	*str;
  int	a;
  int	b;

  a = 1;
  b = 0;
  if ((str = malloc(sizeof(char) * 4096)) == NULL)
    set_brek(NULL, "Malloc failed");
   while (usr_cmd[a] != '\0')
    {
      str[b++] = '$';
      while (usr_cmd[a] != '$' && usr_cmd[a] != '\0')
	{
	  str[b] = usr_cmd[a];
	  b++;
	  a++;
	}
      str[b] = '\0';
      find_in_env(str);
      b = 0;
      if (usr_cmd[a] != '\0')
	a++;
      str = clean_buffer(str);
    }
  return (0);
}

int	echo_error(char **usr_cmd)
{
  int	a;

  a = 1;
  while (usr_cmd[a])
    {
      if (!BUILT(usr_cmd[a][0]))
	{
	  my_puterror("Error: bad syntax\n");
	  return (-1);
	}
      else if (!SEP(usr_cmd[a][0]) || !SPES(usr_cmd[a][0]))
	{
	  my_puterror("Error: bad syntax\n");
	  return (-1);
	}
      else
	a++;
    }
  return (0);
}

int	find_in_env(char *str)
{
  pid_t	pid;
  int	i;

  i = 0;
  pid = getpid();
  if (str[i] == '$' && str[i + 1] == '\0')
    {
      my_put_nbr(pid);
      return (0);
    }
  while (my_env[i] && strncmp(my_env[i], &str[1], strlen(str) - 1) != 0)
    i++;
  if (my_env[i] != NULL)
    my_putstr(&my_env[i][strlen(str)]);
  return (0);
}
