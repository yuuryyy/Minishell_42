/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   expand.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ychagri <ychagri@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/27 01:56:16 by ychagri           #+#    #+#             */
/*   Updated: 2024/08/11 01:17:51 by ychagri          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../minishell.h"

char	*expand_string(char *word)
{
	char	*value;

	if (!ft_strchr(word, '$') || !word || ft_strncmp(word, "$", 2) == 0)
		return (word);
	value = getenv(word + 1);
	free(word);
	if (value)
		word = ft_strdup(value);
	else
		word = NULL;
	return (word);
}

void	norm(char **word)
{
	char	*befor_dolla;
	char	*final;
	char	*tmp;
	size_t	len;
	int		i;

	i = 0;
	befor_dolla = ft_strdup(*word);
	while (befor_dolla[i] && befor_dolla[i] != '$')
		i++;
	befor_dolla[i] = 0;
	len = word_len(*word + i);
	tmp = ft_substr(*word, i, len);
	if (!getenv(tmp + 1))
		final = ft_strjoin(befor_dolla, *word + i + len);
	else
	{
		final = ft_strjoin(befor_dolla, getenv(tmp + 1));
		*word = ft_strjoin(final, *word + i + len);
	}
	free(tmp);
	free(befor_dolla);
	free(final);
}

char	*expand(char *word, t_type type)
{
	if (!word || !ft_strchr(word, '$'))
		return (word);
	if (type == string)
		word = expand_string(word);
	else
		norm(&word);
	return (word);
}

void	expand_var(t_args **cmd_line)
{
	t_token	*tmp;

	if (!*cmd_line)
		return ;
	tmp = (*cmd_line)->tokens;
	while (tmp)
	{
		if (tmp->type == string || tmp->type == double_quote)
		{
			if (tmp->type == string && ft_strchr(tmp->content, '$')
				&& ft_strlen(tmp->content) == 1 && tmp->space == 0
				&& tmp->next && tmp->next->type >= 7)
			{
				free(tmp->content);
				tmp->content = NULL;
			}
			tmp->content = expand(tmp->content, tmp->type);
		}
		tmp = tmp->next;
	}
}
