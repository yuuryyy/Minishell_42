/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parser.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ychagri <ychagri@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/25 10:37:33 by ychagri           #+#    #+#             */
/*   Updated: 2024/10/30 23:57:35 by ychagri          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

// ->  MinionHell^~^  >$ "$PATH" leaks in double qoutes

t_token	*handle_string(t_token *current) //
{
	char	*str;
	bool 	space = current->space;
	void 	*next = current->next;

	if (!current->content || !ft_strchr(current->content, ' '))
		return (current);

	t_token	*tmp = current;
	current->next = NULL;

	str = ft_strrchr(current->content, ' ');
	if (str && ft_strncmp(str, " ", 2) == 0) 
		space = true;

	char **splited = ft_split(current->content, ' ');
	free(current->content);

	
	int i = 0;
	tmp->content = splited[i++];
	tmp->type = string; 
	tmp->space = true;

	
	while (splited[i])
	{
		tmp->next = new_token(splited[i++], string); // prot
		tmp->next->space = true;
		tmp = tmp->next;
	}
	tmp->space = space;
	tmp->next = next;

	free(splited);
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
