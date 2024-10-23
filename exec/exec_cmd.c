/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exec_cmd.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ychagri <ychagri@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/25 18:52:56 by ychagri           #+#    #+#             */
/*   Updated: 2024/10/23 21:39:06 by ychagri          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	exec(t_cmd_tab *table, char **env)
{
	int		i;
	char	*path;
	int		err;

	i = 0;
	while (table->data->path[i])
	{
		path = ft_strjoin(table->data->path[i], "/");
		path = ft_strjoin2(path, table->cmd[0]);
		err = execve(path, table->cmd, env);
		free(path);
		i++;
	}
	return (err);
}

int	execute(t_cmd_tab *table)
{
	char	**env;
	int		err;

	if (infile_opn(table) || outfile_opn(table))
		exit(EXIT_FAILURE);
	if (table->cmd)
	{
		env = lst_to_array(table->data->env);
		err = 0;
		if (ft_strchr(table->cmd[0], '/'))
		{
			if (execve(table->cmd[0], table->cmd, env) == -1)
				return (put_error(table->data, INTROUVABLE_FILE, table->cmd[0]),
					free_array(env), 127);
		}
		err = exec(table, env);
		if (err == -1)
			return (put_error(table->data, NOTFOUNDMSG, table->cmd[0]),
				free_array(env), 127);
	}
	return (0);
}

int	single_cmd(t_cmd_tab *table)
{
	int		status;
	pid_t	pid;

	pid = fork();
	if (pid == -1)
		return (put_error(table->data, FORKMSG, NULL), 1);
	else if (pid == 0)
	{
		g_errno = execute(table);
		exit(g_errno);
	}
	else
	{
		close(STDIN_FILENO);
		waitpid(pid, &status, 0);
		if (table->heredoc)
			close(table->fd_heredoc);
		if (WIFEXITED(status))
		{
			g_errno = WEXITSTATUS(status);
			return (g_errno);
		}
	}
	return (0);
}
