/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parsing_process.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kaafkhar <kaafkhar@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/08/07 23:59:55 by ychagri           #+#    #+#             */
/*   Updated: 2024/09/30 02:17:45 by kaafkhar         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../minishell.h"

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

int	process_line(t_args *cmdline)
{
	char		*tmp;
	t_cmd_tab	*tab;
	int g_errno = 0;

	tmp = ft_strdup(cmdline->line);
	if (!*tmp)
		return (g_errno = EXIT_SUCCESS, 1);
	if (!words_list(tmp, cmdline))
		return (free(tmp), g_errno);
	free(tmp);
	remove_q(&cmdline->tokens);
	if (!syntax_check(cmdline))
		return (g_errno);
	expand_var(&cmdline);
	// fprintf(stderr, "heeere i am \n");
	command_table(cmdline);
	// printf("heere\n");
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
