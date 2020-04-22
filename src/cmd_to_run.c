#include "shell.h"

void	run_cmd(char **usr_cmd, int sep, int *s)
{
  t_re	*root;

  if (usr_cmd[0][0] == '\0')
    return ;
  root = init_root();
  if ((find_redir(usr_cmd, root)) == -1)
    return ;
  usr_cmd = clean_cmd(usr_cmd);
  if (usr_cmd[0] == NULL)
    {
      if (fk == 1)
	kill(getpid(), SIGKILL);
      return ;
    }
  my_exec(usr_cmd, root, sep, s);
}

void	my_exec(char **usr_cmd, t_re *root, int sep, int *s)
{
  if ((sep == 1 && *s == 0) || (sep == 2 && s != 0))
    {
      *s = 0;
      return ;
    }
  if (check_for_builtins(usr_cmd, s) == 0)
    {
      if (fk == 1)
	kill(getpid(), SIGKILL);
      return ;
    }
  if (active == 1)
    return ;
  if (fk == 1)
    {
      exec_son(usr_cmd, root);
      return ;
    }
  do_exec(usr_cmd, root, s);
  return ;
}

void	do_exec(char **usr_cmd, t_re *root, int *s)
{
  pid_t	pid;
  int	status;

  if ((pid = fork()) == 0)
    exec_son(usr_cmd, root);
  if (pid < 0)
    my_puterror("Pid failed\n");
  else if (pid > 0)
    {
      waitpid(pid, &status, 0);
      if (status == 11)
	my_puterror("Segmentation fault ...\n");
      *s = status;
    }
  return ;
}

void	apply_redirection(t_re *root)
{
  t_re	*tmp;

  tmp = root->next;
  while (tmp != root)
    {
      if (tmp->file != NULL)
	wait_to_find(tmp->file);
      if (tmp != root)
	{
	  dup2(tmp->fd, tmp->to_change);
	  if (tmp->to_change == 1)
	    dup2(tmp->fd, 2);
	  close(tmp->fd);
	}
      tmp = tmp->next;
    }
  rm_list(root);
}

int	exec_son(char **usr_cmd, t_re *root)
{
  char	*tmp;
  int	y;

  y = -1;
  apply_redirection(root);
  if ((EXE(usr_cmd[0][0])) && (access(usr_cmd[0], F_OK) == 0))
    execve(usr_cmd[0], usr_cmd, my_env);
  if (usr_cmd[0][0] == '/')
    {
      my_puterror(usr_cmd[0]);
      my_puterror(" : Binary not found\n");
      kill(getpid(), SIGKILL);
    }
  while (my_path[++y])
    {
      tmp = my_strcat(my_path[y], usr_cmd[0]);
      if ((access(tmp, F_OK)) == 0)
	execve(tmp, usr_cmd, my_env);
      free(tmp);
    }
  my_puterror(usr_cmd[0]);
  my_puterror(" : Command not found\n");
  kill(getpid(), SIGKILL);
  return (1);
}
