/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ychagri <ychagri@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/16 19:09:51 by youssra           #+#    #+#             */
/*   Updated: 2024/09/26 19:43:48 by ychagri          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef MINISHELL_H
# define MINISHELL_H

# include <readline/readline.h>
# include <readline/history.h>
# include "lib/Libft/libft.h"
# include "header.h"
# include <fcntl.h>
# include <stdbool.h>
# include <termios.h>
# include <signal.h>
# include <stdio.h>

extern int	g_errno;

typedef enum s_type
{
	redin = 2,
	redout = 3,
	heredoc = 4,
	append = 1,
	piipe = 5,
	string = 6,
	single_quote = 7,
	double_quote = 8,
}	t_type;


typedef	struct s_lim
{
	char			*content;
	bool			quoted;
	struct s_lim	*next;
}	t_lim;

//command table
typedef struct s_cmd_tab
{
	char				**cmd;
	char				*arg;
	char				*in;
	char				*out;
	bool				heredoc;
	int					red_out;
	int					fd_heredoc;
	char				*append;
	t_lim				*delimiter;
	struct s_cmd_tab	*next;
	struct s_args		*data;
}	t_cmd_tab;

//tokens
typedef struct s_token
{
	void			*content;
	t_type			type;
	bool			space;
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
	int			fdin;
	int			fdout;
}	t_args;

void		environment(char **envp, t_args *args);
int			is_seperator(char c);
int			process_line(t_args *cmdline);
int			ft_heredoc(t_cmd_tab **cmds);

void		free_current_cmdline(t_args *cmdline);
void		command_table(t_args *cmdline);
void		free_struct(t_args *cmd_line);
void		free_array(char	**str);
void		free_tokens(t_token **lst);
void		free_table(t_cmd_tab **table);

void		put_error(t_args *cmd_line, char *msg, char *name);

char		*expand(char *word, t_type type);
char		**lst_to_array(t_list *lst);

int			word_len(char *line);
int			words_list(char	*line, t_args *cmd_line);
void		expand_var(t_args **cmd_line);
void		remove_q(t_token **lst);

bool		syntax_check(t_args *cmdline);

t_cmd_tab	*new_tab(void);
t_lim		*new_lim(char *content, bool quote);
void		table_add_back(t_cmd_tab **head, t_cmd_tab *new);
void	ft_limadd_back(t_lim **lst, t_lim *new);

// builtins
int ft_echo(t_args *args, char **cmd);
int ft_cd(t_args *args, char **cmd);
int ft_pwd(t_args *args, char **cmd);
int ft_export(t_args *args, char **cmd);
int ft_exit(t_args *args, char **cmd);

//exec
int	execute_cmds(t_args *args);
int	single_cmd(t_cmd_tab *table);
int	check_files(t_args *args, char *filename, int flag);

#endif