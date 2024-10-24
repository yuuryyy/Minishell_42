/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   heredoc.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ychagri <ychagri@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/08/22 01:42:42 by ychagri           #+#    #+#             */
/*   Updated: 2024/10/24 19:06:19 by ychagri          ###   ########.fr       */
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
	rl_replace_line("", 0); // Clear the current line
	write(STDOUT_FILENO, "\n", 1);
    rl_on_new_line(); // Move to the next line
    // rl_redisplay(); //
	close(STDIN_FILENO);
}

int	read_line(char *limiter, int *fd, int flag, t_args *cmdline)
{
	char	*buffer;

	signal(SIGINT, heredc_sig);
	while (1)
	{
		buffer = readline("heredoc> ");
		if (!buffer)
		{
			if (g_errno == -1)
			{
				free_current_cmdline(cmdline);
				g_errno = 1;
				return (1);
			}
			else
				break ;
		}
		if (ft_strncmp(buffer, limiter, ft_strlen(limiter) + 1) == 0)
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
					g_errno = EXIT_FAILURE, 1);
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
