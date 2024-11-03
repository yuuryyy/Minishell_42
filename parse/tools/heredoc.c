/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   heredoc.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ychagri <ychagri@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/08/22 01:42:42 by ychagri           #+#    #+#             */
/*   Updated: 2024/11/03 04:33:37 by ychagri          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	heredc_sig(int signal)
{
	(void)signal;
	g_errno = -1;
	rl_replace_line("", 0);
	rl_on_new_line();
	close(STDIN_FILENO);
}

int	recieved_sig(t_args *cmdline)
{
	if (g_errno == -1)
	{
		g_errno = 0;
		if (dup2(cmdline->fdin, STDIN_FILENO) == -1)
			return (put_error(DUP2SG, NULL), 1);
		return (free_current_cmdline(cmdline), exit_code(EXIT_FAILURE, EDIT));
	}
	return (0);
}

int	read_line(char *limiter, int *fd, int flag, t_args *cmdline)
{
	char	*buffer;

	signal(SIGINT, heredc_sig);
	signal(SIGQUIT, SIG_IGN);
	buffer = NULL;
	while (1)
	{
		buffer = readline("heredoc> ");
		if (!buffer && recieved_sig(cmdline))
			return (1);
		else if (!buffer)
			break ;
		if (ft_strncmp(buffer, limiter, ft_strlen(limiter) + 1) == 0)
			break ;
		if (flag != NO_EXW)
		{
			if (flag == EXPND_W)
				buffer = expand(buffer, cmdline->env);
			ft_putendl_fd(buffer, fd[1]);
		}
		free(buffer);
	}
	if (buffer)
		free(buffer);
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
