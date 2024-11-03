/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   expand_tools.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kaafkhar <kaafkhar@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/21 12:19:01 by ychagri           #+#    #+#             */
/*   Updated: 2024/11/03 04:46:09 by kaafkhar         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

char	*expand_string(char *word, t_list *env)
{
	char	*value;

	if (!ft_strchr(word, '$') || !word || ft_strncmp(word, "$", 2) == 0)
		return (word);
	value = envgetter(word + 1, env);
	if (value)
	{
		free(word);
		word = value;
	}
	else
	{
		free(word);
		word = NULL;
	}
	return (word);
}

int	index_ds(char *str)
{
	int	i;

	i = 0;
	while (str[i])
	{
		if (str[i] == '$' && (str[i + 1] && (ft_isalnum(str[i + 1])
					|| str[i + 1] == '_' || str[i + 1] == '?')))
			return (i);
		i++;
	}
	return (-1);
}

char	*get_value(char *befor_dolla, char *key, char *after_dolla, t_list *env)
{
	char	*tmp;
	char	*word;
	char	*val;

	tmp = NULL;
	if (key && key[0] && key[1] == '?')
	{
		val = ft_itoa(exit_code(0, RETRIEVE));
		tmp = ft_strjoin(befor_dolla, val);
		word = ft_strjoin2(tmp, after_dolla);
		free(val);
	}
	else
	{
		tmp = envgetter(key + 1, env);
		if (tmp)
		{
			word = ft_strjoin(befor_dolla, tmp);
			word = ft_strjoin2(word, after_dolla);
			free(tmp);
		}
		else
			word = ft_strjoin(befor_dolla, after_dolla);
	}
	return (word);
}

int	key_len(char *word, int index)
{
	int	i;
	int	len;

	i = index + 1;
	len = 1;
	if (word[i] && word[i] == '?')
		return (2);
	while (word[i] && (ft_isalnum(word[i]) || word[i] == '_'))
	{
		i++;
		len++;
	}
	return (len);
}

void	expand_quotes(char **word, int index, t_list *env)
{
	char	*befor_dolla;
	char	*after_dolla;
	char	*key;
	size_t	len;

	befor_dolla = NULL;
	befor_dolla = ft_strdup(*word);
	befor_dolla[index] = 0;
	len = key_len(*word, index);
	key = ft_substr(*word, index, len);
	after_dolla = ft_strdup(*word + index + len);
	free(*word);
	*word = NULL;
	*word = get_value(befor_dolla, key, after_dolla, env);
	free(key);
	free(befor_dolla);
	free(after_dolla);
}
