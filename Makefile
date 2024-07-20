# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: ychagri <ychagri@student.42.fr>            +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2024/07/17 00:25:27 by youssra           #+#    #+#              #
#    Updated: 2024/07/20 02:51:50 by ychagri          ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

NAME 		=	minishell
CC			=	cc

CFLAGS		=	-Wall -Wextra  -Werror
#-fsanitize=address
LFLAGS 		=	"-L$(shell brew --prefix readline)/lib"

HEADER		=	minishell.h

LIBRARY		=	lib/libft.a

SRCS		=	parse/main.c \
				parse/tools.c \

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
