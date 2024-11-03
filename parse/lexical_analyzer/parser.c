/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parser.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ychagri <ychagri@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/25 10:37:33 by ychagri           #+#    #+#             */
/*   Updated: 2024/11/03 04:11:18 by ychagri          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

t_token	*cmd_tab2(t_cmd_tab *new, t_token *current)
{
	if (current->type == string)
	{
		current = handle_string(current);
		while (current && current->type == string
			&& (current->content == NULL || *current->content == '\0'))
			current = current->next;
	}
	if (current && current->type >= 6)
	{
		current = handle_tokens(&current, &new->arg);
	}
	else if (current)
		current = handle_red(new, current);
	return (current);
}

void	command_table(t_args *cmdline)
{
	t_token		*current;
	t_cmd_tab	*new;

	current = cmdline->tokens;
	while (current)
	{
		new = new_tab();
		new->data = cmdline;
		while (current && current->type != piipe)
		{
			current = cmd_tab2(new, current);
			if (!current || current->type == piipe)
				break ;
			current = current->next;
		}
		table_add_back(&cmdline->table, new);
		if (!current)
			break ;
		current = current->next;
	}
}
