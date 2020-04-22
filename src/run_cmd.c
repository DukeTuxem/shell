#include "shell.h"

void		browse_tree(t_tree *tree)
{
  static int	sep;
  static int	stat;

  if (tree)
    {
      if (tree->left)
	{
	  check_for_separators(tree->cmd, &sep);
	  if (sep != 3)
	    {
	      sep = 0;
	      browse_tree(tree->left);
	    }
	  else
	    prepare_for_pipe(tree->left, tree->right, sep, &stat);
	}
      if (check_for_separators(tree->cmd, &sep) != 1)
	do_cmd(tree, sep, &stat);
      if (tree->right)
        browse_tree(tree->right);
    }
  sep = 0;
  active = 0;
}

int		check_for_separators(char *cmd, int *sep)
{
  if (cmd[0] == ';')
    {
      *sep = 0;
      return (1);
    }
  else if (cmd[0] == '|' && cmd[1] == '|')
    {
      *sep = 1;
      return (1);
    }
  else if (cmd[0] == '&' && cmd[1] == '&')
    {
      *sep = 2;
      return (1);
    }
  else if (cmd[0] == '|')
    {
      *sep = 3;
      return (1);
    }
  return (0);
}

void		do_cmd(t_tree *tree, int sep, int *s)
{
  char		**cmd;

  fk = 0;
  cmd = my_str_to_wordtab(tree->cmd);
  run_cmd(cmd, sep, s);
  free_elem(cmd);
  return ;
}

void		prepare_for_pipe(t_tree *left, t_tree *right, int sep, int *s)
{
  pid_t		pid;

  if ((pid = fork()) == 0)
    do_pipe(left, right, sep, s);
  else if (pid == -1)
    my_puterror("Fork error\n");
  else
    {
      waitpid(pid, s, 0);
      active = 1;
    }
  return ;
}

void		do_pipe(t_tree *left, t_tree *right, int sep, int *s)
{
  int		pipefd[2];
  pid_t		pid;

  pipe(pipefd);
  fk = 1;
  active = 0;
  if ((pid = fork()) == 0)
    {
      close(pipefd[0]);
      dup2(pipefd[1], 1);
      if (left->cmd[0] == '|')
	do_pipe(left->left, left->right, sep, s);
      else
	run_cmd(my_str_to_wordtab(left->cmd), sep, s);
    }
  else
    {
      waitpid(pid, s, 0);
      close(pipefd[1]);
      dup2(pipefd[0], 0);
      run_cmd(my_str_to_wordtab(right->cmd), sep, s);
    }
  return ;
}
