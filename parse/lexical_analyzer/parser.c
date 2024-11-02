/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parser.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ychagri <ychagri@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/25 10:37:33 by ychagri           #+#    #+#             */
/*   Updated: 2024/11/02 22:11:29 by ychagri          ###   ########.fr       */
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
		handle_red(new, current);
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
