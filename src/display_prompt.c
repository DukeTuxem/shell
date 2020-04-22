#include "shell.h"

void		display_prompt(void)
{
  static int	cnt = -1;
  char		*name;
  char		*host;

  name = get_usr_name();
  my_putstr(name);
  my_putstr("@");
  if ((host = get_hostname()) == NULL)
    my_putstr("PC");
  else
    my_putstr(host);
  if (getuid() == 0)
    my_putstr("# ");
  else
    my_putstr("$ ");
  my_put_nbr(++cnt);
  my_putstr(" > ");
  free(name);
  if (host)
    free(host);
}

char		*get_usr_name(void)
{
  char		*name;
  int		x;
  int		y;
  int		n_cnt;

  n_cnt = -1;
  x = -1;
  y = -1;
  name = NULL;
  while (my_env[++y] != NULL)
    if (strncmp(my_env[y], "USER=", 5) == 0)
      {
	my_env[y] += 5;
	if ((name = malloc(sizeof(char) * (strlen(my_env[y]) + 1))) == NULL)
	  return (NULL);
	while (my_env[y][++x] != 0)
	  name[++n_cnt] = my_env[y][x];
	name[++n_cnt] = 0;
	my_env[y] -= 5;
      }
  return (name);
}

char		*get_hostname(void)
{
  char		*host;
  int		x;
  int		y;
  int		i;

  i = -1;
  x = -1;
  y = -1;
  host = NULL;
  while (my_env[++y] != NULL)
    if (strncmp(my_env[y], "HOSTNAME=", 9) == 0)
      {
	my_env[y] += 9;
	if ((host = malloc(sizeof(char) * (strlen(my_env[y]) + 1))) == NULL)
	  return (NULL);
	while (my_env[y][++x] != 0)
	  host[++i] = my_env[y][x];
	host[++i] = 0;
	my_env[y] -= 9;
      }
  return (host);
}
