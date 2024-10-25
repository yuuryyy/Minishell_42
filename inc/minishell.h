/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ychagri <ychagri@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/16 19:09:51 by youssra           #+#    #+#             */
/*   Updated: 2024/10/24 19:47:46 by ychagri          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef MINISHELL_H
# define MINISHELL_H

# include <readline/rltypedefs.h>
# include "../lib/Libft/libft.h"
# include <readline/readline.h>
# include <readline/history.h>
# include <sys/types.h>
# include <sys/wait.h>
# include <sys/stat.h>
# include <termios.h>
# include <stdbool.h>
# include <signal.h>
# include <stdlib.h>
# include <string.h>
# include "header.h"
# include <fcntl.h>
# include <stdio.h>

extern int	g_errno;

typedef enum s_type
{
	append = 1,
	redin = 2,
	redout = 3,
	heredoc = 4,
	piipe = 5,
	string = 6,
	single_quote = 7,
	double_quote = 8,
}	t_type;

//command table
typedef struct s_cmd_tab
{
	char				**cmd;
	char				*arg;
	t_list				*in;
	t_list				*out;
	bool				heredoc;
	int					red_out;
	int					fd_heredoc;
	t_list				*append;
	t_list				*delimiter;
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
	int			fdin;
	int			fdout;
	bool		heredoc_flag;
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
void		del(void *content);
void		put_error(t_args *cmd_line, char *msg, char *name);

char		*expand(char *word, t_type type, t_list *env);
void		expand_quotes(char **word, int index, t_list *env);
int			index_ds(char *str);
char		**lst_to_array(t_list *lst);
char		*expand_string(char *word, t_list *env);

int			word_len(char *line);
int			words_list(char	*line, t_args *cmd_line);
void		expand_var(t_args **cmd_line);
void		remove_q(t_token **lst);

bool		syntax_check(t_args *cmdline);

t_cmd_tab	*new_tab(void);
t_list		*new_lim(char *content, bool quote);
void		table_add_back(t_cmd_tab **head, t_cmd_tab *new);
void		ft_limadd_back(t_list **lst, t_list *new);

// builtins
int			exec_builtin(t_args *args, t_cmd_tab *cmd);
void		echo(t_args *args, t_cmd_tab *cmd);
int			cd(t_cmd_tab *cmd, t_list *env);
int			pwd(t_args *arg, char **cmd);
int			export_variable(t_args *args, t_cmd_tab *cmd);
void		ordre_alpha(t_list **env);
t_list		*find_env_node(t_list *env, char *cmd);
void		update_env_value(t_list *env_node, char *cmd);
void		add_env_node(t_list **env, char *cmd);
int			ft_unset(t_args *args, char **cmd);
void		exec_exit(t_args *args, t_cmd_tab *cmd);
void		exec_env(t_cmd_tab *cmd, t_list *env);
//exec
int			exec_pipes(t_cmd_tab *table);
int			execute(t_cmd_tab *table);
int			execute_cmds(t_args *args);
int			single_cmd(t_cmd_tab *table);
int			check_files(t_args *args, char *filename, int flag);
//signals
void		sigint_handler(int signum);
void		sigquit_handler(int signum);
void		setup_signal_handlers(void);
// tools
int			outfile_opn(t_cmd_tab *cmd);
int			infile_opn(t_cmd_tab *cmd);
int			read_line(char *limiter, int *fd, int flag, t_args *cmdline);
int			own_strchr(char *str, char c);
int			ft_strcmp(const char *s1, const char *s2);
int			is_num(char *str);
char		*path(t_list *env, const char *var_name);

#endif
