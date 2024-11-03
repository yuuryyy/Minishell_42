/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   lst_creat_functions.c                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ychagri <ychagri@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/03 02:17:15 by ychagri           #+#    #+#             */
/*   Updated: 2024/11/03 04:16:14 by ychagri          ###   ########.fr       */
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

t_token	*new_token(char *content, int type)
{
	t_token	*token;

	if (!content)
		return (NULL);
	token = malloc(sizeof(t_token));
	if (!token)
		return (NULL);
	token->content = content;
	token->next = NULL;
	token->type = type;
	return (token);
}

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
