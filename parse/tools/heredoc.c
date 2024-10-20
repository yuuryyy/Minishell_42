/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   heredoc.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kaafkhar <kaafkhar@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/08/22 01:42:42 by ychagri           #+#    #+#             */
<<<<<<< HEAD
/*   Updated: 2024/10/20 13:37:58 by kaafkhar         ###   ########.fr       */
=======
/*   Updated: 2024/10/20 14:17:37 by ychagri          ###   ########.fr       */
>>>>>>> 2b6b296cde2daf84b6e579431db3426404e183c7
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


void	read_line(char *limiter, int *fd, int flag, bool quote, t_args *cmdline)
{
	char	*buffer;

	while (1)
	{
		buffer = readline("heredoc> ");
		if (!buffer || ft_strncmp(buffer, limiter, ft_strlen(limiter) + 1) == 0)
			break ;
		if (flag)
		{
			if (quote == false)
				buffer = expand(buffer, double_quote, cmdline->env);
			buffer = ft_strjoin2(buffer, "\n");
			write (fd[1], buffer, ft_strlen(buffer));
		}
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
				if (tmp->next == NULL)
				{
					if (tmp->quoted == true)
						read_line(tmp->content, fd, 1, true, (*cmds)->data);
					else
						read_line(tmp->content, fd, 1, false, (*cmds)->data);
				}
				else
					read_line(tmp->content, fd, 0, false, (*cmds)->data);
				tmp = tmp->next;
			}
			cmdtable->fd_heredoc = fd[0];
			close(fd[1]);
		}
		cmdtable = cmdtable->next;
	}
	return (0);
}
