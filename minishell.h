/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ychagri <ychagri@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/16 19:09:51 by youssra           #+#    #+#             */
/*   Updated: 2024/07/23 05:20:14 by ychagri          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef MINISHELL_H
# define MINISHELL_H

# include <stdio.h>
# include <readline/readline.h>
# include <readline/history.h>
# include "lib/Libft/libft.h"

# define CMD 1
# define LITERAL 2
# define PIPEE 3
# define REDIN 4
# define REDOUT 5
# define HEREDOC 6
# define ARGV 7
# define LIM 8
// # define



# define PIPE -1
# define OUT -2
# define IN -3
# define DS -4
# define SQ -5
# define DQ -6
# define SPACE -7


// typedef struct ÷
typedef struct s_cmd_tab
{
	char	*cmd;
	char	**argv;
	char		*in;
	char		**options;
	char		*out;
	int		here_doc;
	char	*delimiter;
	struct s_cmd	*next;
}	t_cmd_tab;

typedef struct s_token
{
	void	*content;
	int		token;
	struct s_token	*next;
	struct s_token	*previous;
}	t_token;

typedef struct s_args
{
	char		*line;
	t_token		*tokens;
	int			token_num;
	t_cmd_tab	*commands_parsed;
	int			cmd_num;
	char		**path;
	t_list		*env;
}	t_args;

void	environment(char **envp, t_args *args);
void	free_struct(t_args *cmd_line);
void	token_list(t_args *cmd_line);
int is_seperator(char c);
int	replace_literal_token(char *line);
void	seperate_tokens(t_args *cmd_line);
void	open_chars(t_args *cmd_line);
char	*remove_quotes(char *line);
void	free_array(char	**str);

#endif