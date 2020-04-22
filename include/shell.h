#ifndef SHELL_H_
# define SHELL_H_

#include <errno.h>
#include <sys/types.h>
#include <sys/wait.h>
#include <string.h>
#include <stdlib.h>
#include <unistd.h>
#include <signal.h>
#include <stdio.h>
#include <fcntl.h>

#define BUFF_SIZE	4096
#define BLANK(x)	((x) == 32 || (x) == 9)
#define ALLOWED(x)	((x) >= 32 && (x) <= 126)
#define BUILT(x)	((x) != 34 || (x) == 38 || (x) == 39 || (x) == 40 || (x) == 41)
#define SEP(x)		((x) != 42 || (x) == 92 || (x) == 59 || (x) == 60 || (x) == 62)
#define SPES(x)		((x) != 63 || (x) || 124 || (x) == 126)
#define	EXE(x)		((x) == '.' && (x + 1) == '/') || (x) == '/'
#define PIP(x)		((x) == '|')

typedef struct	s_node
{
  char		*cmd;
  struct s_node	*right;
  struct s_node *left;
}		t_node;

typedef struct	s_re
{
  int		fd;
  int		to_change;
  char		*file;
  struct s_re	*prev;
  struct s_re	*next;
}		t_re;

typedef struct	s_word
{
  int		i;
  int		j;
  int		tok;
  int		len_x;
  int		words;
}		t_word;

typedef t_node	t_tree;
typedef t_node	t_leaf;

extern	char	**environ;
char		**my_path;
char		**my_env;
int		brek;
int		fk;
int		active;

/*		BUILTINS.C						*/
int	check_for_builtins(char **cmd, int *s);
int	my_setenv(char **cmd);
int	my_unsetenv(char **cmd);
int	print_env(char **cmd);
int	my_exit(char **cmd);

/*		CD.C							*/
char	*prepare_str(char *str);
char	*str_null();
char	*old_pwd();

/*		CLEAN_CMD.C						*/
char	**clean_cmd(char **old_cmd);

/*		CMD_TO_RUN.C						*/
void	run_cmd(char **usr_cmd, int sep, int *s);
void	my_exec(char **usr_cmd, t_re *root, int sep, int *s);
void	do_exec(char **usr_cmd, t_re *root, int *s);
void    apply_redirection(t_re *root);
int     exec_son(char **usr_cmd, t_re *root);

/*		DISPLAY_PROMPT.C					*/
void	display_prompt(void);
char	*get_usr_name(void);
char	*get_hostname(void);

/*		D_LEFT_REDIR.C						*/
char    *clean_buffer(char *buffer);
char	*return_line(char *str);
void	possible_error(char *to_find);
int	wait_to_find(char *to_find);

/*		ENV.C							*/
char	**get_env(void);
int	get_long(void);

/*		ERROR_ENV.C						*/
int	check_env(char **cmd);

/*		GET_PATH.C						*/
void	path_to_use(void);
char	*path_from_env(void);
char	*epur_path(char *str);

/*		GET_USR_CMD.C						*/
char	*get_usr_cmd(void);
char	*epur_spaces(char *str);
int	is_empty(char *str);
char	*spaces_in_str(char *str);

/*		GERE_CD.C						*/
void	str_mov(unsigned int *i, int *y, char *tmp);
char	*rm_point(char *str);
int	change_oldpwd(char *tmp, char **cmd);
int	chdir_err(char *str);
int	gere_cd(char **cmd);

/*		INIT_SHELL.C						*/
void	init_shell();
void    prompt(char **sep);
void    simple_cmd(char *usr_cmd);
void	init_btree(char *usr_cmd, char **op);

/*		LIST.C							*/
int	add_redir(t_re *root, char *re, char *file);
void	remove_link(t_re *node);
void	rm_list(t_re *root);
t_re    *init_root();

/*		MY_ECHO.C						*/
int	my_echo(char **usr_cmd);
void	aff_echo_doll(char **usr_cmd);
int	echo_mult_doll(char *usr_cmd);
int	echo_error(char **usr_cmd);
int	find_in_env(char *str);

/*		MY_PUTS.C						*/
void	my_putchar(char c);
void	my_putstr(char *str);
int	my_puterror(char *str);
void	my_put_nbr(int nb);

/*		REDIRECTIONS.C						*/
int	d_right_redir(t_re *node, char *str);
int	left_redir(t_re *node, char *str);
int	d_left_redir(t_re *node, char *str);
int	right_redir(t_re *node, char *str);
int	find_redir(char **usr_cmd, t_re *root);

/*		RUN_CMD.C						*/
void	browse_tree(t_tree *tree);
int	check_for_separators(char *cmd, int *sep);
void	do_cmd(t_tree *tree, int sep, int *s);
void	prepare_for_pipe(t_tree *left, t_tree *right, int sep, int *s);
void	do_pipe(t_tree *left, t_tree *right, int sep, int *s);

/*		SETENV.C						*/
int	add_in_my_env(char *var_env);
int	overwriting(char **cmd);
int	overwriting_singlearg(char **cmd);
char	*strdelim(char **cmd);
char	*cpy_in_str(char *str, char **cmd);

/*		SIGS.C							*/
void	catch_sigs(void);
void	ctrlquit(int sig);
void	ctrlc(int sig);
void	ctrlz(int sig);

/*		STRING.C						*/
char	*my_strcpy(char *src, char *dst);
char	*my_strcat(char *path, char *cmd);
void	set_brek(void *type, char *errstr);
void	free_elem(char **elem);

/*		STR_TO_WORDTAB.C					*/
char	**my_str_to_wordtab(char *str);
char	*put_word_in_tab(char *str, int len_x);
int	cnt_words(char *str);

/*		TREE.C							*/
void	add_elem_to_tree(t_tree **node, char **op, char *str);
void	free_tree(t_tree *tree);
void	check_tree(t_tree *tree);

/*		USR_CMD_SORT.C						*/
int	find_separator(char *str, char **sep);
char	*copy_sep(char *dest, char *src, int i);
char	*clean_str(char *str);
char	*cut_left_str(char *str, int i);
char	*cut_right_str(char *str, int i);

#endif	/* SHELL_H_ */
