/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ychagri <ychagri@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/16 19:09:51 by youssra           #+#    #+#             */
/*   Updated: 2024/07/21 04:37:55 by ychagri          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef MINISHELL_H
# define MINISHELL_H

# include <stdio.h>
# include <readline/readline.h>
# include <readline/history.h>
# include "lib/Libft/libft.h"

# define PIPE -1
# define OUT -2
# define IN -3
# define DS -4
# define SQ -5
# define DQ -6



typedef struct s_cmd
{
	char	**cmd_table;
	int		in;
	int		out;
	struct t_cmd	*next;
}	t_cmd;

typedef struct s_args
{
	char	*line;
	t_cmd	*commands;
	int		cmd_num;
	char	**path;
	t_list	*env;
	int		exit_code;
}	t_args;

void	environment(char **envp, t_args *args);
void	free_struct(t_args *cmd_line);
int	count_word(char *line);
int	replace_literal_token(t_args *cmd_line, char *line);
void	open_chars(t_args *cmd_line);
char	*remove_quotes(char *line);

#endif