/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exec_cmd.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ychagri <ychagri@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/25 18:52:56 by ychagri           #+#    #+#             */
/*   Updated: 2024/11/04 04:59:30 by ychagri          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	exec(t_cmd_tab *table, t_list *env)
{
	int		i;
	char	*path;
	char	**bin;
	char	**envp;
	int		err;

	i = 0;
	path = envgetter("PATH", env);
	envp = lst_to_array(env);
	if (!path)
		err = execve(table->cmd[0], table->cmd, envp);
	else
	{
		bin = ft_split(path, ':');
		free(path);
		err = 0;
		while (bin[i])
		{
			path = ft_strjoin(bin[i++], "/");
			path = ft_strjoin2(path, table->cmd[0]);
			err = execve(path, table->cmd, envp);
			free(path);
		}
	}
	return (err);
}

void	exec_bin(t_cmd_tab *table, char **env)
{
	int			err;
	struct stat	status;

	err = execve(table->cmd[0], table->cmd, env);
	if (err == -1)
	{
		if (execve(table->cmd[0], table->cmd, env) == -1)
		{
			if (stat(table->cmd[0], &status) == 0)
			{
				if (S_ISDIR(status.st_mode))
					return (put_error(ISDIR, table->cmd[0]),
						free_array(env), exit(EXIT_ESDIR));
				if (!(S_IXUSR & status.st_mode))
					return (put_error(PERMISSION, table->cmd[0]),
						free_array(env), exit(EXIT_ESDIR));
			}
			return (put_error(INTROUVABLE_FILE, table->cmd[0]),
				free_array(env), exit(BINARY_ERROR));
		}
	}
}

void	execute(t_cmd_tab *table)
{
	char			**env;
	int				err;
	int				built;

	if (infile_opn(table) || outfile_opn(table))
		exit(EXIT_FAILURE);
	if (table->cmd)
	{
		built = exec_builtin(table->data, table, MULTI);
		if (built == NOT_BUITIN)
		{
			env = lst_to_array(table->data->env);
			err = 0;
			if (ft_strchr(table->cmd[0], '/'))
				exec_bin(table, env);
			err = exec(table, table->data->env);
			if (err == -1)
				return (put_error(NOTFOUNDMSG, table->cmd[0]),
					free_array(env), exit(BINARY_ERROR));
		}
		exit (built);
	}
	exit(0);
}

int	single_cmd(t_cmd_tab *table)
{
	int		status;
	pid_t	pid;
	int		code;

	signal(SIGQUIT, sigquit_handler);
	pid = fork();
	if (pid == -1)
		return (put_error(FORKMSG, NULL), 1);
	else if (pid == 0)
		execute(table);
	else
	{
		close(STDIN_FILENO);
		waitpid(pid, &status, 0);
		if (table->heredoc)
			close(table->fd_heredoc);
		if (WIFEXITED(status))
		{
			code = WEXITSTATUS(status);
			return (exit_code(code, EDIT), code);
		}
	}
	return (0);
}
