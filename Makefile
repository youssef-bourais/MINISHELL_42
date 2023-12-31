NAME = minishell

VAR_LIBFT = Libft/libft.a
SRCS = minishell.c parssing/lexer.c parssing/lexer_2.c parssing/lexer_tools.c parssing/check_syntax.c parssing/parss_red.c\
					parssing/parssing.c parssing/parssing_tools.c parssing/tools.c parssing/tools_2.c parssing/expand_var.c parssing/expand_var_tools.c\
					builtin/cd.c builtin/echo.c builtin/env.c builtin/exit.c builtin/export.c builtin/pwd.c builtin/unset.c builtin/export_tools.c\
					exucution/exucution.c exucution/exucution_utils.c exucution/pipes.c exucution/pipes_utils.c exucution/exucution_2.c\
					exucution/redirection.c exucution/red_utils.c minishell_tool.c

CC = cc

<<<<<<< HEAD
CFLAGS = -Wall -Werror -Wextra -g -I/goinfre/ybourais/brew/opt/readline/include
=======
CFLAGS = -Wall -Werror -Wextra -g -I/goinfre/bgannoun/brew/opt/readline/include #-fsanitize=address 
>>>>>>> de50f55b4e6e55a5ecb788d6702b1e3a496376b2

OBJS = $(SRCS:.c=.o)

all : $(NAME)

$(NAME) : $(OBJS) $(VAR_LIBFT) Makefile
<<<<<<< HEAD
		$(CC) $(CFLAGS) $(VAR_LIBFT) $(OBJS) -L/goinfre/ybourais/brew/opt/readline/lib -o $(NAME) -lreadline -ltermcap
=======
		$(CC) $(CFLAGS) $(VAR_LIBFT) $(OBJS) -L/goinfre/bgannoun/brew/opt/readline/lib -o $(NAME) -lreadline -ltermcap
>>>>>>> de50f55b4e6e55a5ecb788d6702b1e3a496376b2

clean :
	rm -rf $(OBJS)
	make clean -C Libft

$(VAR_LIBFT) :
	make -C Libft

fclean : clean
	rm -rf $(NAME)
	make fclean -C Libft

re : fclean all
	make re -C Libft