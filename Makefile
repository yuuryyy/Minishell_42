
NAME 		=	minishell

CC			=	cc

CFLAGS		=	-g -Wall -Wextra -Werror -I./inc -I$(shell brew --prefix readline)/include  
#-fsanitize=address
#-Werror

LFLAGS 		=	"-L$(shell brew --prefix readline)/lib" -lreadline 

HEADER		=	minishell.h

LIBRARY		=	lib/libft.a

SRCS		=	main.c \
				parse/tools/before_parse.c \
				parse/tools/error.c \
				parse/tools/signals.c \
				parse/tools/freeing.c \
				parse/tools/expand.c \
				parse/tools/expand_tools.c \
				parse/tools/heredoc.c \
				parse/tools/tokenizer_tools.c \
				parse/lexical_analyzer/create_tokens.c \
				parse/lexical_analyzer/parser.c \
				parse/lexical_analyzer/parsing_process.c \
				exec/exec_cmd.c \
				exec/tools.c \
				exec/process_cmds.c \
				exec/builtins.c \
				exec/builtins2.c \
				exec/exuc_built.c \
				exec/pipe_line.c \
				exec/toolsbuilts.c \
				exec/redirections.c \

OBJS		= $(SRCS:.c=.o)

all : $(NAME)

lib :
	make -C lib

$(NAME) : $(OBJS) lib
	@$(CC) $(CFLAGS) $(OBJS) $(LIBRARY) -o $(NAME) $(LFLAGS)

%.o: %.c $(HEADER)
		$(CC)  $(CFLAGS) -c $< -o $@

clean:
	make clean -C lib
	rm -rf $(OBJS)

fclean:	clean
	make fclean -C lib
	rm -rf $(NAME)

re: fclean all


push: fclean
	git add .
	git commit -m "exec done, sig herdc left"
	git push

.PHONY: clean fclean re lib
