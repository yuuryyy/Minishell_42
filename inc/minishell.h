/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kaafkhar <kaafkhar@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/16 19:09:51 by youssra           #+#    #+#             */
/*   Updated: 2024/11/04 06:12:36 by kaafkhar         ###   ########.fr       */
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
	struct s_token	*next;
}	t_token;

//main struct
typedef struct s_args
{
	t_list		*env;
	char		*line;
	t_token		*tokens;
	bool		env_i;
	t_cmd_tab	*table;
	int			fdin;
	int			fdout;
	bool		heredoc_flag;
}	t_args;

//parse
void		tokenadd_back(t_token	**token, t_token	*new);
void		table_add_back(t_cmd_tab **head, t_cmd_tab *new);
t_token		*handle_tokens(t_token **current, t_list **list);
t_token		*handle_red(t_cmd_tab *new, t_token *current);
void		add_env_node(t_list **env, char *new_content);
void		ft_limadd_back(t_list **lst, t_list *new);
int			words_list(char	*line, t_args *cmd_line);
void		environment(char **envp, t_args *args);
t_token		*new_token(char *content, int type);
t_list		*new_lim(char *content, bool quote);
t_token		*handle_string(t_token *current);
int			process_line(t_args *cmdline);
void		expand_var(t_args **cmd_line);
bool		syntax_check(t_args *cmdline);
int			ft_heredoc(t_cmd_tab **cmds);
void		remove_q(t_token **lst);
int			array_len(char **str);
int			is_seperator(char c);
int			word_len(char *line);
t_cmd_tab	*new_tab(void);

//freeing && errors
void		put_built_err(char *built, char *name, char *err);
void		free_current_cmdline(t_args *cmdline);
void		put_error(char *msg, char *name);
void		command_table(t_args *cmdline);
void		free_struct(t_args *cmd_line);
void		free_table(t_cmd_tab **table);
void		free_tokens(t_token **lst);
void		free_array(char	**str);
void		del(void *content);

//expand
void		expand_quotes(char **word, int index, t_list *env);
char		*expand_string(char *word, t_list *env);
char		*expand(char *word, t_list *env);
int			index_ds(char *str);

// builtins
int			updates(t_cmd_tab *cmd, char *variable, char *f_sign, int i);
int			add_new_env_var(t_args *args, const char *cmd, int append);
int			replace_env_value(t_list *env_node, const char *new_part);
int			update_env_value(t_list *env_node, char *cmd, int append);
int			export_variable(t_args *args, t_cmd_tab *cmd, int flag);
void		print_echo_args(t_cmd_tab *table, int i, bool newline);
int			exec_builtin(t_args *args, t_cmd_tab *cmd, int flag);
char		*ft_strncpy(char *dest, const char *src, size_t n);
int			exec_exit(t_args *args, t_cmd_tab *cmd, int flag);
char		*prepare_new_content(const char *cmd, int append);
int			exec_env(t_cmd_tab *table, t_list *env, int flag);
void		update_oldpwd(t_list **env, char *current_path);
int			handle_cd_command(t_cmd_tab *cmd, t_list *env);
char		*extract_variable(const char *cmd, int append);
int			ft_unset(t_args *args, char **cmd, int flag);
void		remove_env_var(t_args *args, char *argument);
bool		parse_echo_options(t_cmd_tab *table, int *i);
int			pwd(t_cmd_tab *table, char **cmd, int flag);
int			cd(t_cmd_tab *cmd, t_list **env, int flag);
void		update_pwd(t_list **env, char *new_path);
int			change_directory_to_oldpwd(char *oldpwd);
char		*path(t_list *env, const char *var_name);
t_list		*find_env_node2(t_list *env, char *cmd);
int			validate_exit_argument(t_cmd_tab *cmd);
t_list		*find_env_node(t_list *env, char *cmd);
int			perform_exit(t_args *args, int code);
int			change_directory_to_home(char *home);
char		*ft_strcpy(char *s1, const char *s2);
char		*ft_strcat(char *dest, char *src);
int			echo(t_cmd_tab *table, int flag);
void		display_env_vars(t_list *env);
int			get_equal_position(char *cmd);
char		*ft_strdup2(const char *str);
void		ordre_env_vars(t_list **env);
char		**lst_to_array(t_list *lst);
int			is_valid(const char *str);
int			array_len(char **str);

//exec
int			check_files(char *filename, int flag);
int			exec(t_cmd_tab *table, t_list *env);
int			single_cmd(t_cmd_tab *table);
int			exec_pipes(t_cmd_tab *table);
int			execute_cmds(t_args *args);
void		execute(t_cmd_tab *table);

//signals
int			exit_code(int code, int flag);
void		setup_signal_handlers(void);
void		sigquit_handler(int signum);
void		sigint_handler(int signum);

// tools
int			read_line(char *limiter, int *fd, int flag, t_args *cmdline);
int			ft_strcmp(const char *s1, const char *s2);
char		*envgetter(const char *key, t_list *env);
char		*path(t_list *env, const char *var_name);
int			outfile_opn(t_cmd_tab *cmd);
char		**lst_to_array(t_list *lst);
int			infile_opn(t_cmd_tab *cmd);
int			is_num(char *str);

#endif
