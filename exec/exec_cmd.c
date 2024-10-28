/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exec_cmd.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ychagri <ychagri@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/25 18:52:56 by ychagri           #+#    #+#             */
/*   Updated: 2024/10/28 02:24:00 by ychagri          ###   ########.fr       */
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
	int		built;

			// printf("%s>>>>>>\n", table->cmd[0]);
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
			{
				if (execve(table->cmd[0], table->cmd, env) == -1)
					return (put_error(INTROUVABLE_FILE, table->cmd[0]),
						free_array(env), exit(127), 1);
			}
			err = exec(table, env);
			if (err == -1)
				return (put_error(NOTFOUNDMSG, table->cmd[0]),
					free_array(env), exit(127), 1);
		}
		return (built);
	}
	exit(0);
}

int	single_cmd(t_cmd_tab *table)
{
	int		status;
	pid_t	pid;

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
			g_errno = WEXITSTATUS(status);
			return (g_errno);
		}
	}
	return (0);
}
