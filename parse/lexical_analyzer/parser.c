/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parser.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ychagri <ychagri@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/25 10:37:33 by ychagri           #+#    #+#             */
/*   Updated: 2024/08/05 07:08:33 by ychagri          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../minishell.h"

t_cmd_tab	*new_tab()
{
	t_cmd_tab	*new;

	new = malloc(sizeof(t_cmd_tab *));
	if (!new)
		return (NULL);
	ft_bzero(new, sizeof(t_cmd_tab *));
	return (new);
}

void	table_add_back(t_cmd_tab **head, t_cmd_tab *new)
{
	t_cmd_tab	*tmp;
	t_cmd_tab	*prev;

	tmp = *head;
	if (!new || !head)
		return ;
	if (tmp == NULL)
	{
		tmp = new;
		return ;
	}
	while (tmp)
	{
		prev = tmp;
		tmp = tmp->next;
	}
	prev->next = new;

}

void	command_table(t_args *cmdline)
{
	t_token	*current;
	t_token	*prev;
	t_token	*next;
	t_cmd_tab	*new;

	current = cmdline->tokens;
	prev = NULL;
	while (current)
	{
		new = new_tab();
		// printf("%p", new);

		while (current && current->type != piipe)
		{
			next = current->next;
			if (current->type == redin)
			{
				new->in = next->content;
				current = next->next;
			}
			else if (current->type == redout)
			{
				new->out = next->content;
				current = next->next;
			}
			else if (current->type == append)
			{
				new->append = ft_strdup(next->content);
				current = next->next;
			}
			else if (current->type == heredoc)
			{
				new->delimiter = next->content;
				new->heredoc = true;
				current = next->next;
			}
			else
			{
					// printf("hereee   %s\n",current->content);
				new->arg = ft_strjoin2(new->arg, current->content);
				current = current->next;
			}
		}
		table_add_back(&cmdline->table, new);
		if (current->type == piipe)
			current = current->next;
		current = current->next;
	}
}
