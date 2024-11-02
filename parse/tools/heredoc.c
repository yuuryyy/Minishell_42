/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   heredoc.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ychagri <ychagri@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/08/22 01:42:42 by ychagri           #+#    #+#             */
/*   Updated: 2024/11/02 22:26:36 by ychagri          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	heredoc_process(char *limiter, int *fd, int flag, t_args *cmdline)
{
	char	*buffer;

	buffer = readline("heredoc> ");
	if (!buffer)
	{
		if (g_errno == SIGINT)
		{
			if (dup2(cmdline->fdin, STDIN_FILENO) == -1)
				return (put_error(DUP2SG, NULL), 1);
			return (exit_code(EXIT_FAILURE, EDIT),
				free_current_cmdline(cmdline), 1);
		}
		else
			return (0);
	}
	if (ft_strncmp(buffer, limiter, ft_strlen(limiter) + 1) == 0)
		return (free(buffer), 0);
	if (flag != NO_EXW)
	{
		if (flag == EXPND_W)
			buffer = expand(buffer, cmdline->env);
		buffer = ft_strjoin2(buffer, "\n");
		write (fd[1], buffer, ft_strlen(buffer));
	}
	return (free(buffer), 2);
}

int	read_line(char *limiter, int *fd, int flag, t_args *cmdline)
{
	int		err;

	signal(SIGINT, heredc_sig);
	while (1)
	{
		err = heredoc_process(limiter, fd, flag, cmdline);
		if (err == 1)
			return (1);
		else if (err == 0)
			break ;
		else
			continue ;
	}
	return (0);
}

int	open_heredoc(t_list *tab, int *fd, t_args *data)
{
	int	err;

	err = 0;
	while (tab)
	{
		if (tab->next == NULL)
		{
			if (tab->quoted == true)
				err = read_line(tab->content, fd, WRITE_FD, data);
			else
				err = read_line(tab->content, fd, EXPND_W, data);
		}
		else
			err = read_line(tab->content, fd, NO_EXW, data);
		if (err)
			return (1);
		tab = tab->next;
	}
	return (0);
}

int	ft_heredoc(t_cmd_tab **cmds)
{
	t_cmd_tab	*cmdtable;
	t_list		*tmp;
	int			fd[2];
	int			err;

	err = 0;
	cmdtable = *cmds;
	while (cmdtable)
	{
		if (cmdtable->heredoc)
		{
			if (pipe(fd) == -1)
				return (ft_putstr_fd("pipe has failed", 2),
					exit_code(1, EDIT), 1);
			tmp = cmdtable->delimiter;
			err = open_heredoc(tmp, fd, (*cmds)->data);
			if (err)
				return (close(fd[1]), close(fd[0]), 1);
			cmdtable->fd_heredoc = fd[0];
			close(fd[1]);
		}
		cmdtable = cmdtable->next;
	}
	return (0);
}
