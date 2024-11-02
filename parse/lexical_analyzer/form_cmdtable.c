/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   form_cmdtable.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ychagri <ychagri@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/02 21:50:35 by ychagri           #+#    #+#             */
/*   Updated: 2024/11/02 21:56:28 by ychagri          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

t_token	*splitbyspace(t_token *current, t_token *tmp, bool space)
{
	char	**splited;
	int		i;

	splited = ft_split(current->content, ' ');
	free(current->content);
	i = 0;
	tmp->content = splited[i++];
	tmp->type = string;
	tmp->space = true;
	while (splited[i])
	{
		tmp->next = new_token(splited[i++], string);
		tmp->next->space = true;
		tmp = tmp->next;
	}
	free(splited);
	tmp->space = space;
	return (tmp);
}

t_token	*handle_string(t_token *current)
{
	char	*str;
	t_token	*tmp;
	bool	space;
	void	*next;

	if (!current->content || !ft_strchr(current->content, ' '))
		return (current);
	tmp = current;
	next = current->next;
	space = current->space;
	current->next = NULL;
	str = ft_strrchr(current->content, ' ');
	if (str && ft_strncmp(str, " ", 2) == 0)
		space = true;
	tmp = splitbyspace(current, tmp, space);
	tmp->next = next;
	return (current);
}

t_token	*handle_tokens(t_token **current, t_list **list)
{
	t_token	*tmp;
	t_list	*new;
	char	*str;

	tmp = *current;
	str = NULL;
	while (tmp && tmp->type >= 6)
	{
		str = ft_strjoin2(str, tmp->content);
		if (tmp->space)
			break ;
		tmp = tmp->next;
	}
	new = ft_lstnew(str);
	ft_lstadd_back(list, new);
	return (tmp);
}

t_token	*handle_limiters(t_token **current, t_list **limiter)
{
	t_token	*tmp;
	char	*str;
	t_list	*new;
	bool	flag;

	tmp = *current;
	str = NULL;
	flag = false;
	while (tmp && tmp->type >= 6)
	{
		if (tmp->type >= 7)
			flag = true;
		str = ft_strjoin2(str, tmp->content);
		if (tmp->space)
			break ;
		tmp = tmp->next;
	}
	new = new_lim(str, flag);
	ft_limadd_back(limiter, new);
	return (tmp);
}

void	handle_red(t_cmd_tab *new, t_token *current)
{
	if (current->type == redin)
		current = handle_tokens(&current->next, &new->in);
	else if (current->type == redout)
	{
		new->red_out = REDOUT;
		current = handle_tokens(&current->next, &new->out);
	}
	else if (current->type == append)
	{
		new->red_out = APND;
		current = handle_tokens(&current->next, &new->append);
	}
	else if (current->type == heredoc)
	{
		new->heredoc = true;
		current = handle_limiters(&current->next, &new->delimiter);
	}
}
