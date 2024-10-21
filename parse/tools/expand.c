/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   expand.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ychagri <ychagri@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/27 01:56:16 by ychagri           #+#    #+#             */
/*   Updated: 2024/10/21 12:42:45 by ychagri          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

char	*expand(char *word, t_type type, t_list *env)
{
	int		index;
	t_list	*tmp;

	if (!word || !ft_strchr(word, '$'))
		return (word);
	tmp = env;
	if (word[0] == '$' && word[1] == '?')
	{
		free(word);
		word = ft_itoa(g_errno);
	}
	else if (type == string)
		word = expand_string(word, tmp);
	else
	{
		index = index_ds(word);
		while (index != -1)
		{
			expand_quotes(&word, index, tmp);
			index = index_ds(word);
			tmp = env;
		}
	}
	return (word);
}

char	*replace_sp(char *str)
{
	int	i;

	if (!str)
		return (NULL);
	i = 0;
	while (str[i])
	{
		if (str[i] == ' ')
			str[i] = '\n';
		i++;
	}
	return (str);
}

void	str_exp(t_token *tmp, t_list *env)
{
	char	*old_str;

	if (tmp->type == heredoc)
	{
		tmp = tmp->next;
		while (tmp && tmp->type >= string && tmp->space == 0)
			tmp = tmp->next;
	}
	if (tmp && (tmp->type == string || tmp->type == double_quote))
	{
		if (tmp->type == string && ft_strchr(tmp->content, '$')
			&& ft_strlen(tmp->content) == 1 && tmp->space == 0
			&& tmp->next && tmp->next->type >= 7)
		{
			free(tmp->content);
			tmp->content = NULL;
		}
		old_str = tmp->content;
		tmp->content = expand(tmp->content, tmp->type, env);
		if (ft_strncmp(old_str, tmp->content, ft_strlen(old_str) + 1))
		{
			tmp->content = replace_sp(tmp->content);
			tmp->type = string;
		}
	}
}

void	expand_var(t_args **cmd_line)
{
	t_token	*tmp;

	if (!*cmd_line)
		return ;
	tmp = (*cmd_line)->tokens;
	while (tmp)
	{
		str_exp(tmp, (*cmd_line)->env);
		if (tmp)
			tmp = tmp->next;
	}
}
