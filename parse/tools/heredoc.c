/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   heredoc.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ychagri <ychagri@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/08/22 01:42:42 by ychagri           #+#    #+#             */
/*   Updated: 2024/10/23 17:47:01 by ychagri          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

t_list	*new_lim(char *content, bool quote)
{
	t_list	*new;

	new = ft_lstnew(content);
	new->next = NULL;
	new->quoted = quote;
	return (new);
}

void	ft_limadd_back(t_list **lst, t_list *new)
{
	t_list	*ptr;
	t_list	*tmp;

	if (!lst || !new)
		return ;
	if (*lst == NULL)
	{
		*lst = new;
		return ;
	}
	tmp = *lst;
	while (tmp)
	{
		if (tmp->next == NULL)
			ptr = tmp;
		tmp = tmp->next;
	}
	ptr->next = new;
}

void	heredc_sig(int signal)
{
	(void)signal;
	g_errno = -1;
	close(STDIN_FILENO);
}

void	read_line(char *limiter, int *fd, int flag, t_args *cmdline)
{
	char	*buffer;

	signal(SIGINT, heredc_sig);
	while (1)
	{
		buffer = readline("heredoc> ");
		if (!buffer || ft_strncmp(buffer, limiter, ft_strlen(limiter) + 1) == 0)
			break ;
		if (flag != NO_EXW)
		{
			if (flag == EXPND_W)
				buffer = expand(buffer, double_quote, cmdline->env);
			buffer = ft_strjoin2(buffer, "\n");
			write (fd[1], buffer, ft_strlen(buffer));
		}
		free(buffer);
	}
	if (buffer)
		free(buffer);
}

void	open_heredoc(t_list *tab, int *fd, t_args *data)
{
	while (tab)
	{
		if (tab->next == NULL)
		{
			if (tab->quoted == true)
				read_line(tab->content, fd, WRITE_FD, data);
			else
				read_line(tab->content, fd, EXPND_W, data);
		}
		else
			read_line(tab->content, fd, NO_EXW, data);
		tab = tab->next;
	}
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
			open_heredoc(tmp, fd, (*cmds)->data);
			cmdtable->fd_heredoc = fd[0];
			close(fd[1]);
		}
		cmdtable = cmdtable->next;
	}
	return (0);
}
