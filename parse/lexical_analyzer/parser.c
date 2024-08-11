/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parser.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ychagri <ychagri@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/25 10:37:33 by ychagri           #+#    #+#             */
/*   Updated: 2024/08/10 23:29:52 by ychagri          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../minishell.h"

char	*handle_string(t_token *current, char *new)
{
	char	*arg;

	arg = ft_strjoin2(new, current->content);
	if (current->space)
		arg = ft_strjoin2(arg, "\n");
	return (arg);
}

t_token	*handle_tokens(t_token **current, char **str)
{
	t_token	*tmp;

	tmp = *current;
	while (tmp && tmp->type >= 6)
	{
		*str = ft_strjoin2(*str, tmp->content);
		if (tmp->space)
			break ;
		tmp = tmp->next;
	}
	return (tmp);
}

t_token	*cmd_tab2(t_cmd_tab *new, t_token *current)
{
	if (current->type >= 6)
		new->arg = handle_string(current, new->arg);
	else
	{
		if (current->type == redin)
		{
			new->heredoc = false;
			current = handle_tokens(&current->next, &new->in);
		}
		else if (current->type == redout)
			current = handle_tokens(&current->next, &new->out);
		else if (current->type == append)
			current = handle_tokens(&current->next, &new->append);
		else if (current->type == heredoc)
		{
			current = handle_tokens(&current->next, &new->delimiter);
			new->heredoc = true;
		}
	}
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
		while (current && current->type != piipe)
		{
			current = cmd_tab2(new, current);
			if (!current)
				break ;
			current = current->next;
		}
		table_add_back(&cmdline->table, new);
		if (!current)
			break ;
		current = current->next;
	}
}
