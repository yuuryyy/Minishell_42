/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   heredoc.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kaafkhar <kaafkhar@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/08/22 01:42:42 by ychagri           #+#    #+#             */
/*   Updated: 2024/09/30 02:16:42 by kaafkhar         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../minishell.h"

t_lim	*new_lim(char *content, bool quote)
{
	t_lim	*new;

	new = malloc(sizeof(t_lim));
	new->content = content;
	new->quoted = quote;
	new->next = NULL;
	return (new);
}

void	ft_limadd_back(t_lim **lst, t_lim *new)
{
	t_lim	*ptr;
	t_lim	*tmp;

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


void	read_line(char *limiter, int *fd, int flag, bool quote)
{
	char	*buffer;

	while (1)
	{
		buffer = readline("heredoc> ");
		if (ft_strncmp(buffer, limiter, ft_strlen(limiter)) == 0)
			break ;
		if (flag)
		{
			if (quote == true)
				buffer = expand(buffer, double_quote);
			write (fd[1], buffer, ft_strlen(buffer));
			close(fd[1]);
		}
		free(buffer);
	}
	free(buffer);
}

int	ft_heredoc(t_cmd_tab **cmds)
{
	t_cmd_tab	*cmdtable;
	t_lim		*tmp;
	int			fd[2];
	int			g_errno = 0;

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
				if (tmp->next == NULL)
				{
					if (tmp->quoted == true)
						read_line(tmp->content, fd, 1, true);
					else
						read_line(tmp->content, fd, 1, false);
				}
				else
					read_line(tmp->content, fd, 0, false);
				tmp = tmp->next;
			}
			cmdtable->fd_heredoc = fd[0];
		}
		cmdtable = cmdtable->next;
	}
	return (0);
}
