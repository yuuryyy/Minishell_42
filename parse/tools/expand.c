/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   expand.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ychagri <ychagri@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/27 01:56:16 by ychagri           #+#    #+#             */
/*   Updated: 2024/09/02 22:17:14 by ychagri          ###   ########.fr       */
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

int	index_ds(char *str)
{
	int	i;

	i = 0;
	while (str[i])
	{
		if (str[i] == '$' && (str[i + 1] && (ft_isalnum(str[i + 1]) || str[i + 1] == '_')))
			return (i);
		i++;
	}
	return (-1);
}

void	expand_quotes(char **word, int index)
{
	char	*befor_dolla;
	char	*tmp;
	char	*after_dolla;
	char	*var;
	size_t	len;

	befor_dolla = NULL;
	tmp = NULL;
	befor_dolla = ft_strdup(*word);
	befor_dolla[index] = 0;
	len = word_len(*word + index);
	var = ft_substr(*word, index, len);
	after_dolla = ft_strdup(*word + index + len);
	free(*word);
	if (!getenv(var + 1))
		*word = ft_strjoin(befor_dolla, after_dolla);
	else
	{
		tmp = ft_strjoin(befor_dolla, getenv(var + 1));
		*word = ft_strjoin(tmp, after_dolla);
		free(tmp);
	}
	free(var);
	free(befor_dolla);
	free(after_dolla);
}

char	*expand(char *word, t_type type)
{
	int 	index;

	if (!word || !ft_strchr(word, '$'))
		return (word);
	if (type == string)
		word = expand_string(word);
	else
	{
		index = index_ds(word);
			printf("%d\n", index);
		while (index != -1)
		{
			expand_quotes(&word, index);
			index = index_ds(word);
		}
	}
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
