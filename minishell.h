/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ychagri <ychagri@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/16 19:09:51 by youssra           #+#    #+#             */
/*   Updated: 2024/07/23 06:20:46 by ychagri          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef MINISHELL_H
# define MINISHELL_H

# include <stdio.h>
# include <readline/readline.h>
# include <readline/history.h>
# include "lib/Libft/libft.h"

# define EXIT_SUCCESS 0
# define EXIT_FAILURE 1
# define BINARY_ERROR 127
// # define 
// # define 
// # define 
// # define 


// tokens
# define CMD 1
# define LITERAL 2
# define PIPEE 3
# define REDIN 4
# define REDOUT 5
# define HEREDOC 6
# define ARGV 7
# define LIM 8
// # define

//separators
# define PIPE -1
# define OUT -2
# define IN -3
# define DS -4
# define SQ -5
# define DQ -6
# define SPACE -7


//command table
typedef struct s_cmd_tab
{
	char	*cmd;
	char	**argv;
	char		*in;
	char		*out;
	char	*delimiter;
	struct s_cmd	*next;
}	t_cmd_tab;

//tokens
typedef struct s_token
{
	void	*content;
	int		token;
	struct s_token	*next;
	struct s_token	*previous;
}	t_token;

//main struct
typedef struct s_args
{
	t_list		*env;
	char		**path;
	char		*line;
	t_token		*tokens;
	int			token_num;
	t_cmd_tab	*table;
	int			cmd_num;
}	t_args;

void	environment(char **envp, t_args *args);
void	free_struct(t_args *cmd_line);
void	token_list(t_args *cmd_line);
int 	is_seperator(char c);
int		replace_literal_token(char *line);
void	seperate_tokens(t_args *cmd_line);
char	*remove_quotes(char *line);
void	free_array(char	**str);

#endif