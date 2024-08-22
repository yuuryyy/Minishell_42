/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   heredoc.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ychagri <ychagri@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/08/22 01:42:42 by ychagri           #+#    #+#             */
/*   Updated: 2024/08/22 03:39:49 by ychagri          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../minishell.h"

void	read_line(char *limiter, int *fd)
{
	char	*buffer;

	while (1)
	{
		buffer = readline("heredoc> ");
		if (ft_strncmp(buffer, limiter, ft_strlen(limiter)) == 0)
			break ;
		write (fd[1], buffer, ft_strlen(buffer));
		free(buffer);
	}
	free(buffer);
}

int	ft_heredoc(t_cmd_tab **cmds)
{
	t_cmd_tab	*cmdtable;
	t_list		*tmp;
	int			fd[2];

	cmdtable = *cmds;
	while (cmdtable)
	{
		if (cmdtable->heredoc)
		{
			if (pipe(fd) == -1)
				return (ft_putstr_fd("pipe has failed", 2),
					g_errno = EXIT_FAILURE, 1);
			tmp = cmdtable->delimiter;
			while (tmp)
			{
				read_line(tmp->content, fd);
				tmp = tmp->next;
			}
			close(fd[1]);
			cmdtable->fd_heredoc = fd[0];
		}
		cmdtable = cmdtable->next;
	}
	return (0);
}
