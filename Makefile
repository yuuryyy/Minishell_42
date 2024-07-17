# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: youssra <youssra@student.42.fr>            +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2024/07/17 00:25:27 by youssra           #+#    #+#              #
#    Updated: 2024/07/17 00:53:54 by youssra          ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

NAME 		:=	minishell

COMPILE		:=	cc -Wall -Wextra -Werror

HEADER		:=	minishell.h

LIBRARY		:=	lib/libft.a

SRCS		:=	parse/main.c \
				parse/env_setups.c \

OBJS		:= $(SRCS:.c=.o)

all : $(NAME)

lib :
	make -C lib

$(NAME) : $(OBJS) lib
	$(COMPILE) $(OBJS) $(LIBRARY) -o $(NAME)

%.o: %.c $(HEADER)
		$(COMPILE) -c $< -o $@

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
