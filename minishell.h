/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ychagri <ychagri@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/16 19:09:51 by youssra           #+#    #+#             */
/*   Updated: 2024/07/25 12:54:02 by ychagri          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef MINISHELL_H
# define MINISHELL_H

# include <stdio.h>
# include <readline/readline.h>
# include <readline/history.h>
# include "lib/Libft/libft.h"
#include <stdbool.h>

# define EXIT_SUCCESS 0
# define EXIT_FAILURE 1
# define BINARY_ERROR 127

int	errno;
// # define 
// # define 
// # define 
// # define 

typedef enum s_type
{
	string = 100,
	piipe = 200,
	redin = 300,
	redout = 400,
	heredoc = 500,
	single_quote = 600,
	double_quote = 700,
	append = 800,
}	t_type;

//command table
typedef struct s_cmd_tab
{
	char	*cmd;
	char	**argv;
	char		*in;
	char		*out;
	char	*delimiter;
	struct s_cmd_tab	*next;
}	t_cmd_tab;

//tokens
typedef struct s_token
{
	void	*content;
	t_type		type;
	bool		space;
	struct s_token	*next;
}	t_token;

//main struct
typedef struct s_args
{
	t_list		*env;
	char		**path;
	char		*line;
	t_token		*tokens;
	t_cmd_tab	*table;
	int			cmd_num;
}	t_args;

void	environment(char **envp, t_args *args);
void	free_struct(t_args *cmd_line);
void	token_list(t_args *cmd_line);
int 	is_seperator(char c);
// int		replace_literal_token(char *line);
void	seperate_tokens(t_args *cmd_line);
char	*remove_quotes(char *line);
void	free_array(char	**str);
void	syntax_error(char *line);
int 	word_len(char *line);
void	words_list(char	*line, t_args *cmd_line);
void	expand_var(t_args **cmd_line);
void	remove_q(t_token **lst);

#endif