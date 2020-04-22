#include "shell.h"

void		init_shell(void)
{
  char		**sep;

  fk = 0;
  active = 0;
  my_env = get_env();
  sep = my_str_to_wordtab("; || && |");
  while (brek == 0)
    prompt(sep);
  free_elem(sep);
}

void		prompt(char **sep)
{
  char		*usr_cmd;

  catch_sigs();
  path_to_use();
  display_prompt();
  if ((usr_cmd = get_usr_cmd()) != NULL)
    {
      usr_cmd = spaces_in_str(usr_cmd);
      if ((find_separator(usr_cmd, sep)) == -1)
	simple_cmd(usr_cmd);
      else
	init_btree(usr_cmd, sep);
      free(usr_cmd);
    }
}

void		simple_cmd(char *usr_cmd)
{
  char		**cmd;
  int		s;

  s = -1;
  cmd = my_str_to_wordtab(usr_cmd);
  run_cmd(cmd, -1, &s);
  free_elem(cmd);
}

void		init_btree(char *usr_cmd, char **op)
{
  t_leaf	*first;

  add_elem_to_tree(&first, op, usr_cmd);
  check_tree(first);
  if (brek == 1)
    {
      brek = 0;
      free_tree(first);
      return ;
    }
  browse_tree(first);
  free_tree(first);
}
