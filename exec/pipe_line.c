/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pipe_line.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ychagri <ychagri@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/16 21:37:35 by ychagri           #+#    #+#             */
/*   Updated: 2024/10/17 02:43:16 by ychagri          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	exec_pipes(t_cmd_tab *table)
{
	t_cmd_tab	*tab;
	pid_t		pid;
	int			fd[2];

	tab = table;
	while (tab)
	{
		printf("<<<<lllllllll>>>>");
		if (tab->next == NULL)
			single_cmd(tab);
		if (pipe(fd) == -1)
			return (put_error(table->data, PIPEMSG, NULL), 1);
		pid = fork();
		if (pid == -1)
			return (put_error(table->data, FORKMSG, NULL), 1);
		else if (pid == 0)
		{
			close(fd[0]);
			if (dup2(fd[1], STDOUT_FILENO) == -1)
				return (close (fd[1]), put_error(table->data, DUP2SG, NULL), 1);
			close(fd[1]);
			execute(tab);
		}
		else
		{
			close(fd[1]);
			if (dup2(fd[0], STDIN_FILENO) == -1)
				return (close (fd[0]), put_error(table->data, DUP2SG, NULL), 1);
			close(fd[0]);
		}
		tab = tab->next;
	}
	return (0);
}
