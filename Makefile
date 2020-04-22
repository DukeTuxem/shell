CC	=	gcc

CFLAGS	+=	-W -Wall -Werror -I./include

NAME	=	42sh

SRCS	=	src/display_prompt.c	\
		src/cmd_to_run.c	\
		src/list.c		\
		src/redirections.c	\
		src/d_left_redir.c	\
		src/gere_cd.c		\
		src/cd.c		\
		src/my_echo.c		\
		src/clean_cmd.c		\
		src/str_to_wordtab.c	\
		src/usr_cmd_sort.c	\
		src/get_usr_cmd.c	\
		src/init_shell.c	\
		src/get_path.c		\
		src/builtins.c		\
		src/my_puts.c		\
		src/run_cmd.c		\
		src/string.c		\
		src/setenv.c		\
		src/tree.c		\
		src/sigs.c		\
		src/error_env.c		\
		src/env.c		\
		src/main.c

OBJS	=	$(SRCS:.c=.o)


all:		$(NAME)

$(NAME):	$(OBJS)
		$(CC) $(OBJS) -o $(NAME)
clean:
		$(RM) $(OBJS)

fclean:		clean
		$(RM) $(NAME)

re:		fclean all

.PHONY:		all clean fclean re
