/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   expand_tools.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ychagri <ychagri@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/21 12:19:01 by ychagri           #+#    #+#             */
/*   Updated: 2024/10/23 17:54:43 by ychagri          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

char	*ft_getenv(char *word, t_list *env)
{
	char	*var;
	char	*expanded_str;
	char	*temp;

	if (!word || !env)
		return (NULL);
	var = ft_strjoin(word + 1, "=");
	expanded_str = NULL;
	while (env)
	{
		if (ft_strncmp(var, env->content, ft_strlen(var)) == 0)
		{
			temp = ft_strchr(env->content, '=') + 1;
			expanded_str = ft_strdup(temp);
			break ;
		}
		env = env->next;
	}
	free(var);
	free(word);
	return (expanded_str);
}

char	*expand_string(char *word, t_list *env)
{
	char	*value;

	if (!ft_strchr(word, '$') || !word || ft_strncmp(word, "$", 2) == 0)
		return (word);
	value = getenv(word + 1);
	if (value)
	{
		free(word);
		word = ft_strdup(value);
	}
	else
		word = ft_getenv(word, env);
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

char	*get_value(char *befor_dolla, char *var, char *after_dolla, t_list *env)
{
	char	*tmp;
	char	*word;

	tmp = NULL;
	if (var && var[1] == '?')
	{
		if (g_errno == -1)
			g_errno = 1;
		var = ft_itoa(g_errno);
		tmp = ft_strjoin(befor_dolla, var);
		word = ft_strjoin(tmp, after_dolla);
	}
	else if (!getenv(var + 1))
	{
		tmp = ft_getenv(var + 1, env);
		if (tmp)
			befor_dolla = ft_strjoin(tmp, befor_dolla);
		word = ft_strjoin(befor_dolla, after_dolla);
	}
	else
	{
		tmp = ft_strjoin(befor_dolla, getenv(var + 1));
		word = ft_strjoin(tmp, after_dolla);
		free(tmp);
	}
	return (word);
}

void	expand_quotes(char **word, int index, t_list *env)
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
	*word = get_value(befor_dolla, var, after_dolla, env);
	free(var);
	free(befor_dolla);
	free(after_dolla);
}
