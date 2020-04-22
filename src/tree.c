#include "shell.h"

void	add_elem_to_tree(t_tree **node, char **sep, char *str)
{
  int	i;

  if ((*node = malloc(sizeof(t_tree))) == NULL)
    return ;
  i = find_separator(str, sep);
  if (i != -1)
    {
      if (((*node)->cmd = malloc(sizeof(char) * 3)) == NULL)
	return ;
      (*node)->cmd = copy_sep((*node)->cmd, str, i);
      add_elem_to_tree(&(*node)->left, sep, cut_left_str(str, i));
      add_elem_to_tree(&(*node)->right, sep, cut_right_str(str, i));
    }
  else
    {
      if (((*node)->cmd = malloc(sizeof(char) * strlen(str) + 1)) == NULL)
	return ;
      (*node)->cmd = strcpy((*node)->cmd, str);
      (*node)->left = NULL;
      (*node)->right = NULL;
    }
}

void	free_tree(t_tree *tree)
{
  if (tree)
    {
      free_tree(tree->left);
      free_tree(tree->right);
      free(tree);
    }
}

void	check_tree(t_tree *tree)
{
  if (!tree)
    return ;
  if (tree->left)
    check_tree(tree->left);
  if ((tree->left && tree->left->cmd[0] == '\0')
      || (tree->right && tree->right->cmd[0] == '\0'))
    {
      if (brek == 0)
	{
	  my_puterror("Syntax error near unexpected token `");
	  my_puterror(tree->cmd);
	  my_puterror("'\n");
	  brek = 1;
	}
    }
  if (tree->right)
    check_tree(tree->right);
}
