/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ychagri <ychagri@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/16 19:09:51 by youssra           #+#    #+#             */
/*   Updated: 2024/11/02 22:12:13 by ychagri          ###   ########.fr       */
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
# include "limits.h"
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
	t_list				*arg;
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
	char			*content;
	t_type			type;
	bool			space;
	// bool			flag;
	struct s_token	*next;
}	t_token;

//main struct
typedef struct s_args
{
	t_list		*env;
	// char		**path; // dynamic
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
int			array_len(char **str);

void		free_current_cmdline(t_args *cmdline);
void		command_table(t_args *cmdline);
void		free_struct(t_args *cmd_line);
void		free_array(char	**str);
void		free_tokens(t_token **lst);
void		free_table(t_cmd_tab **table);
void		del(void *content);
void		put_error(char *msg, char *name);
void		put_built_err(char *built, char *name, char *err);

char		*expand(char *word, t_list *env);
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
void	handle_red(t_cmd_tab *new, t_token *current);
t_token	*handle_limiters(t_token **current, t_list **limiter);
t_token	*handle_tokens(t_token **current, t_list **list);
t_token	*handle_string(t_token *current);
t_list		*new_lim(char *content, bool quote);
t_token	*new_token(char *content, int type);
void	tokenadd_back(t_token	**token, t_token	*new);
void		table_add_back(t_cmd_tab **head, t_cmd_tab *new);
void		ft_limadd_back(t_list **lst, t_list *new);
char	*envgetter(const char *key, t_list *env);

// builtins
int			exec_builtin(t_args *args, t_cmd_tab *cmd, int flag);
int			echo(t_cmd_tab *table, int flag);
int			cd(t_cmd_tab *cmd, t_list **env, int flag);
t_list		*find_env_node2(t_list *env, char *cmd);
int			exec_exit(t_args *cmdline, t_cmd_tab *cmd_table, int flag);
int			export_variable(t_args *args, t_cmd_tab *cmd);
void		ordre_alpha(t_list **env);
t_list		*find_env_node(t_list *env, char *cmd);
int			update_env_value(t_list *env_node, char *cmd, int append);
int			ft_unset(t_args *args, char **cmd, int flag);
int			exec_env(t_cmd_tab *table, t_list *env, int flag);
void		add_env_node(t_list **env, char *new_content);
int			is_valid_identifier(const char *str);
int			change_directory_to_oldpwd(char *oldpwd);
int			pwd(t_cmd_tab *table, char **cmd, int flag);


//exec
int			exec(t_cmd_tab *table, t_list *env);
int			exec_pipes(t_cmd_tab *table);
void		execute(t_cmd_tab *table);
int			execute_cmds(t_args *args);
int			single_cmd(t_cmd_tab *table);
int			check_files(char *filename, int flag);
//signals
int			exit_code(int code, int flag);
void		heredc_sig(int signal);
void		sigint_handler(int signum);
void		setup_signal_handlers(void);
// tools
int			outfile_opn(t_cmd_tab *cmd);
int			infile_opn(t_cmd_tab *cmd);
int			read_line(char *limiter, int *fd, int flag, t_args *cmdline);
int			ft_strcmp(const char *s1, const char *s2);
int			is_num(char *str);
char		*path(t_list *env, const char *var_name);

#endif
