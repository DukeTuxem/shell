#include "shell.h"

int	add_redir(t_re *root, char *re, char *file)
{
  t_re	*new;

  if ((new = malloc(sizeof(t_re))) == NULL)
    return (-1);
  new->prev = root->prev;
  new->next = root;
  root->prev->next = new;
  root->prev = new;
  if (file == NULL)
    {
      my_puterror("Error not expected sign ");
      my_puterror(re);
      return (my_puterror("\n"));
    }
  if (re[0] == '>' && re[1] == '>')
    return (d_right_redir(new, file));
  else if (re[0] == '>')
    return (right_redir(new, file));
  else if (re[0] == '<' && re[1] == '<')
    return (d_left_redir(new, file));
  else
    return (left_redir(new, file));
}

void	remove_link(t_re *node)
{
  node->prev->next = node->next;
  node->next->prev = node->prev;
  free(node);
}

void	rm_list(t_re *root)
{
  t_re	*tmp;
  t_re	*stock;

  tmp = root->next;
  stock = tmp;
  while (tmp != root)
    {
      stock = stock->next;
      remove_link(tmp);
      tmp = stock;
    }
  free(root);
}

t_re	*init_root()
{
  t_re	*root;

  if ((root = malloc(sizeof(t_re))) == NULL)
    return (NULL);
  root->prev = root;
  root->next = root;
  return (root);
}
