#include "shell.h"

int	d_right_redir(t_re *node, char *str)
{
  node->fd = open(str, O_RDWR | O_CREAT | O_APPEND, S_IRUSR | S_IWUSR);
  node->to_change = 1;
  if (node->fd == -1)
    {
      my_puterror(str);
      return (my_puterror(" : The selected file can't be openned\n"));
    }
  node->file = NULL;
  return (0);
}

int	left_redir(t_re *node, char *str)
{
  node->fd = open(str, O_RDWR);
  node->to_change = 0;
  if (node->fd == -1)
    {
      my_puterror(str);
      return (my_puterror(" : The selected file can't be openned\n"));
    }
  node->file = NULL;
  return (0);
}

int	d_left_redir(t_re *node, char *str)
{
  node->fd = open(".tmp", O_RDWR | O_TRUNC);
  node->to_change = 0;
  node->file = return_line(str);
  return (0);
}

int	right_redir(t_re *node, char *str)
{
  node->fd = open(str, O_RDWR | O_CREAT | O_TRUNC, S_IRUSR | S_IWUSR);
  node->to_change = 1;
  if (node->fd == -1)
    {
      my_puterror(str);
      return (my_puterror(" : The selected file can't be openned\n"));
    }
  node->file = NULL;
  return (0);
}

int	find_redir(char **usr_cmd, t_re *root)
{
  int	i;
  int	y;
  char	**redirs;

  i = 0;
  redirs = my_str_to_wordtab(">> > < <<");
  while (usr_cmd[i] != NULL)
    {
      y = 0;
      while (redirs[y] != NULL)
	{
	  if (strcmp(redirs[y], usr_cmd[i]) == 0)
	    {
	      if (add_redir(root, usr_cmd[i], usr_cmd[i + 1]) == 1)
		return (-1);
	      usr_cmd[i + 1][0] = '\0';
	      usr_cmd[i][0] = '\0';
	    }
	  y++;
	}
      i++;
    }
  free_elem(redirs);
  return (0);
}
