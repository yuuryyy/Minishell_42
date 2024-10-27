/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pipe_line.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ychagri <ychagri@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/16 21:37:35 by ychagri           #+#    #+#             */
/*   Updated: 2024/10/27 00:49:16 by ychagri          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	forking(t_cmd_tab *tab, int *fd)
{
	pid_t	pid;

	pid = fork();
	if (pid == -1)
		return (put_error(FORKMSG, NULL), 1);
	else if (pid == 0)
	{
		close(fd[0]);
		if (dup2(fd[1], STDOUT_FILENO) == -1)
			return (close (fd[1]), put_error(DUP2SG, NULL), 1);
		close(fd[1]);
		//check bi
		exit(execute(tab));
	}
	else if (pid > 0)
	{
		close(fd[1]);
		if (dup2(fd[0], STDIN_FILENO) == -1)
			return (close (fd[0]), put_error(DUP2SG, NULL), 1);
		close(fd[0]);
		if (tab->heredoc)
			close(tab->fd_heredoc);
	}
	return (0);
}

int	exec_pipes(t_cmd_tab *table)
{
	t_cmd_tab	*tab;
	int			fd[2];
	int			err;

	tab = table;
	err = 0;
	while (tab)
	{
		if (tab->next == NULL)
		{
			err = exec_builtin(table->data, tab, MULTI);
			if (err == NOT_BUITIN)
				g_errno = single_cmd(tab);
			return (0);
		}
		err = exec_builtin(tab->data, tab, MULTI);
		if (err == NOT_BUITIN)
		{
			if (pipe(fd) == -1)
				return (put_error(PIPEMSG, NULL), 1);
			if (forking(tab, fd))
			{
				close(fd[1]);
				close(fd[0]);
				return (1);
			}
		}
		err = 0;
		tab = tab->next;
	}
	return (0);
}
