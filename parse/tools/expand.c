/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   expand.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ychagri <ychagri@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/27 01:56:16 by ychagri           #+#    #+#             */
/*   Updated: 2024/11/04 03:03:42 by ychagri          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

char	*expand(char *word, t_list *env)
{
	int		index;
	t_list	*tmp;

	if (!word || !ft_strchr(word, '$'))
		return (word);
	tmp = env;
	index = index_ds(word);
	while (index != -1)
	{
		expand_quotes(&word, index, tmp);
		index = index_ds(word);
		tmp = env;
	}
	return (word);
}

void	str_exp(t_token *tmp, t_list *env)
{
	if (tmp && (tmp->type == string || tmp->type == double_quote))
	{
		if (tmp->type == string && ft_strchr(tmp->content, '$')
			&& ft_strlen(tmp->content) == 1 && tmp->space == 0
			&& tmp->next && tmp->next->type >= 7)
		{
			free(tmp->content);
			tmp->content = NULL;
		}
		tmp->content = expand(tmp->content, env);
	}
}

void	expand_var(t_args **cmd_line)
{
	t_token	*tmp;

	if (!cmd_line)
		return ;
	tmp = (*cmd_line)->tokens;
	while (tmp)
	{
		if (tmp->type == heredoc)
		{
			tmp = tmp->next;
			while (tmp && tmp->type >= string)
			{
				if (tmp->space)
				{
					tmp = tmp->next;
					break ;
				}
				tmp = tmp->next;
			}
		}
		str_exp(tmp, (*cmd_line)->env);
		if (tmp)
			tmp = tmp->next;
	}
}
