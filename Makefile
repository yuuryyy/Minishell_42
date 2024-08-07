# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: ychagri <ychagri@student.42.fr>            +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2024/07/17 00:25:27 by youssra           #+#    #+#              #
#    Updated: 2024/08/08 00:15:21 by ychagri          ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

NAME 		=	minishell
CC			=	cc

CFLAGS		=	-g -Wall -Wextra -Werror -fsanitize=address

LFLAGS 		=	"-L$(shell brew --prefix readline)/lib"

HEADER		=	minishell.h

LIBRARY		=	lib/libft.a

SRCS		=	parse/main.c \
				parse/tools/before_parse.c \
				parse/tools/error.c \
				parse/tools/freeing.c \
				parse/tools/expand.c \
				parse/tools/tokenizer_tools.c \
				parse/lexical_analyzer/create_tokens.c \
				parse/lexical_analyzer/parser.c \
				parse/lexical_analyzer/parsing_process.c \


OBJS		= $(SRCS:.c=.o)

all : $(NAME)

lib :
	make -C lib

$(NAME) : $(OBJS) lib
	$(CC)  $(CFLAGS) $(OBJS) $(LIBRARY) -o $(NAME) -lreadline $(LFLAGS)

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
	git commit -m "parse"
	git push

.PHONY: clean fclean re lib
