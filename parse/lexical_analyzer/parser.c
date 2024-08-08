/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parser.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: youssra <youssra@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/25 10:37:33 by ychagri           #+#    #+#             */
/*   Updated: 2024/08/08 17:24:04 by youssra          ###   ########.fr       */
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

char	*handle_string(t_token *current, char *new)
{
	char	*arg;

	arg = ft_strjoin2(new, current->content);
	if (current->space)
		arg = ft_strjoin2(arg, "\n");
	return (arg);
}

void	command_table(t_args *cmdline)
{
	t_token		*current;
	t_token		*next;
	t_cmd_tab	*new;

	current = cmdline->tokens;
	while (current)
	{
		new = new_tab();
		while (current && current->type != piipe)
		{
			next = current->next;
			if (current->type >= 6)
				new->arg = handle_string(current, new->arg);
			else
			{
				if (current->type == redin)
				{
					while (next && next->type >= 6)
					{
						new->in = ft_strjoin2(new->in, next->content);
						if (next->space)
							break ;
						next = next->next;
					}
				}
				else if (current->type == redout)
				{
					while (next && next->type >= 6)
					{
						new->out = ft_strjoin2(new->out, next->content);
						if (next->space)
							break ;
						next = next->next;
					}
				}
				else if (current->type == append)
				{
					while (next && next->type >= 6)
					{
						new->append = ft_strjoin2(new->append, next->content);
						if (next->space)
							break ;
						next = next->next;
					}
				}
				else if (current->type == heredoc)
				{
					while (next && next->type >= 6)
					{
						new->delimiter= ft_strjoin2(new->delimiter, next->content);
						if (next->space)
							break ;
						next = next->next;
					}
					new->heredoc = true;
				}
				if (!current)
					break;
				current = next;
			}
			if (!current)
				break;
			current = current->next;
		}
		table_add_back(&cmdline->table, new);
		if (!current)
			break ;
		current = current->next;
	}
}
