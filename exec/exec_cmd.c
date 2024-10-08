/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exec_cmd.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: youssra <youssra@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/25 18:52:56 by ychagri           #+#    #+#             */
/*   Updated: 2024/10/08 18:24:25 by youssra          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	infile_opn(t_cmd_tab *cmd)
{
	int		fdin;

	if (cmd->in != NULL)
	{
		if (check_files(cmd->data, cmd->in, INPUT))
			return (1);
		fdin = open(cmd->in, O_RDONLY, 0644);
		if (fdin == -1)
			return (put_error(cmd->data, OPENMSG, NULL), 1);
		if (cmd->heredoc == false)
		{
			if (dup2(fdin, cmd->data->fdin) == -1)
				return (close(fdin), put_error(cmd->data, DUP2SG, NULL), 1);
		}
		close(fdin);
	}
	if (cmd->heredoc == true)
	{
		printf("here %d\n", cmd->data->fdin);
		if (dup2(cmd->fd_heredoc, cmd->data->fdin) == -1)
			return (close(cmd->fd_heredoc), put_error(cmd->data, DUP2SG, NULL), 1);
		close(cmd->fd_heredoc);
	}
	return (0);
}

int	outfile_opn(t_cmd_tab *cmd)
{
	int		fdout;
	int		apnd;

	if (cmd->out != NULL)
	{
		if (check_files(cmd->data, cmd->out, OUTPUT))
			return (1);
		fdout = open(cmd->out, O_CREAT | O_TRUNC | O_RDWR, 0644);
		if (fdout == -1)
			return (put_error(cmd->data, OPENMSG, NULL), 1);
		if (cmd->red_out == REDOUT)
		{
			printf("heeeeeeere  %d\n", cmd->data->fdout);
			if (dup2(fdout, cmd->data->fdout) == -1)
				return (close(fdout), put_error(cmd->data, DUP2SG, NULL), 1);
		}
		close(fdout);
	}
	if (cmd->append != NULL)
	{
		if (check_files(cmd->data, cmd->append, OUTPUT))
			return (1);
		apnd = open(cmd->append, O_CREAT | O_APPEND | O_RDWR, 0644);
		if (apnd == -1)
			return (put_error(cmd->data, OPENMSG, NULL), 1);
		if (cmd->red_out == APND)
		{
			if (dup2(apnd, cmd->data->fdout) == -1)
				return (close(apnd), put_error(cmd->data, DUP2SG, NULL), 1);
		}
		close(apnd);
	}
	return (0);
}


int	single_cmd(t_cmd_tab *table)
{
	int		i;
	char	**env;
	char	*path;
	int		status;
	pid_t	pid;
	int		err;

	// fprintf(stderr, BLUE"heeeeeeeere>>>>>>>\n"RESET);
	pid = fork();
	if (pid == -1)
		return (put_error(table->data, FORKMSG, NULL), 1);
	else if (pid == 0)
	{
		if (infile_opn(table) || outfile_opn(table))
			exit(EXIT_FAILURE);
		if (table->cmd)
		{
			env = lst_to_array(table->data->env);
			err = 0;
			i = 0;
			if (ft_strchr(table->cmd[0], '/'))
			{
				if (execve(table->cmd[0],table->cmd, env) == -1)
					return (put_error(table->data, INTROUVABLE_FILE, table->cmd[0]), free_array(env), exit(127), 1);
			}
			while (table->data->path[i])
			{
				path = ft_strjoin(table->data->path[i], "/");
				path = ft_strjoin2(path, table->cmd[0]);
				err = execve(path, table->cmd, env);
				free(path);
				i++;
			}
			if (err == -1)
				return (put_error(table->data, NOTFOUNDMSG, table->cmd[0]), free_array(env), exit(127), 1);
		}
	}
	else
	{
		waitpid(pid, &status, 0);
		if (WIFEXITED(status))
		{
			g_errno = WEXITSTATUS(status);
			return (0);
		}
	}
	return (0);
}
