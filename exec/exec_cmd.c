/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exec_cmd.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ychagri <ychagri@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/25 18:52:56 by ychagri           #+#    #+#             */
/*   Updated: 2024/10/31 00:11:53 by ychagri          ###   ########.fr       */
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
	path = envGetter("PATH", env);
	if (!path)
		return (put_error(INTROUVABLE_FILE, table->cmd[0]), exit (127), 1);
	envp = lst_to_array(env);
	bin = ft_split(path, ':');
	free(path);
	err = 0;
	while (bin[i])
	{
		path = ft_strjoin(bin[i], "/");
		path = ft_strjoin2(path, table->cmd[0]);
		err = execve(path, table->cmd, envp);
		free(path);
		i++;
	}
	return (err);
}

int	execute(t_cmd_tab *table, int flag)
{
	char	**env;
	int		err;
	int		built;
	struct stat status;

	if (infile_opn(table) || outfile_opn(table))
		exit(EXIT_FAILURE);
	if (table->cmd)
	{
		if (flag == SINGLE)
			built = NOT_BUITIN;
		else
			built = exec_builtin(table->data, table, MULTI);
		if (built == NOT_BUITIN)
		{
			env = lst_to_array(table->data->env);
			err = 0;
			if (ft_strchr(table->cmd[0], '/'))
			{
				if (execve(table->cmd[0], table->cmd, env) == -1)
				{
					if (stat(table->cmd[0], &status) == 0)
					{
						if (S_ISDIR(status.st_mode))
							return (put_error(ISDIR, table->cmd[0]),
								free_array(env), exit(EXIT_ESDIR), 1);
					}
					return (put_error(INTROUVABLE_FILE, table->cmd[0]),
							free_array(env), exit(127), 1);
				}
			}
			err = exec(table, table->data->env);
			if (err == -1)
				return (put_error(NOTFOUNDMSG, table->cmd[0]),
					free_array(env), exit(127), 127);
		}
		exit (built);
	}
	exit(0);
}

int	single_cmd(t_cmd_tab *table, int flag)
{
	int		status;
	pid_t	pid;

	pid = fork();
	if (pid == -1)
		return (put_error(FORKMSG, NULL), 1);
	else if (pid == 0)
		execute(table, flag);
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
