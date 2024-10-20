/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parsing_process.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ychagri <ychagri@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/08/07 23:59:55 by ychagri           #+#    #+#             */
/*   Updated: 2024/10/20 12:20:44 by ychagri          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

t_cmd_tab	*new_tab(void)
{
	t_cmd_tab	*new;

	new = malloc(sizeof(t_cmd_tab));
	if (!new)
		return (NULL);
	ft_bzero(new, sizeof(t_cmd_tab));
	return (new);
}

void	table_add_back(t_cmd_tab **head, t_cmd_tab *new)
{
	t_cmd_tab	*tmp;
	t_cmd_tab	*prev;

	tmp = *head;
	if (*head == NULL)
	{
		*head = new;
		return ;
	}
	while (tmp)
	{
		prev = tmp;
		tmp = tmp->next;
	}
	prev->next = new;
}

void	heredoc_check(t_token *token)
{
	t_token	*temp;
	char	*lim;

	temp = token;
	while (temp && temp->type != piipe)
	{
		if (temp->type == heredoc)
		{
			lim = NULL;
			temp = temp->next;
			while (temp && temp->type >= string)
			{
				lim = ft_strjoin2(lim, temp->content);
				if (temp->space == true)
					break ;
				temp = temp->next;
			}
			// printf("%s>>\n", lim);
			read_line(lim, NULL, 0, 0, NULL);
			free(lim);
		}
		else if (temp)
			temp = temp->next;
	}
}

int	process_line(t_args *cmdline)
{
	char		*tmp;
	t_cmd_tab	*tab;

	tmp = ft_strdup(cmdline->line);
	if (!*tmp)
		return (free(tmp), g_errno = EXIT_SUCCESS, 1);
	if (!words_list(tmp, cmdline))
		return (heredoc_check(cmdline->tokens),free(tmp), g_errno);
	free(tmp);
	remove_q(&cmdline->tokens);
	if (!syntax_check(cmdline))
	{
		printf("ypoooooo\n");
		return (heredoc_check(cmdline->tokens), g_errno);
	}
	expand_var(&cmdline);
	// fprintf(stderr, "heeere i am \n");
	command_table(cmdline);
	tab = cmdline->table;
	while (tab)
	{
		tab->cmd = ft_split(tab->arg, '\n');
		free(tab->arg);
		tab->arg = NULL;
		tab = tab->next;
	}
	ft_heredoc(&cmdline->table);
	return (0);
}
