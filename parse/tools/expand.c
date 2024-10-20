/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   expand.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ychagri <ychagri@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/27 01:56:16 by ychagri           #+#    #+#             */
/*   Updated: 2024/10/20 19:32:25 by ychagri          ###   ########.fr       */
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
	{
		word = ft_getenv(word , env);
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
	if (var && var[1] == '?')
	{
		var = ft_itoa(g_errno);
		tmp = ft_strjoin(befor_dolla, var);
		*word = ft_strjoin(tmp, after_dolla);
	}
	else if (!getenv(var + 1))
	{
		tmp = ft_getenv(var + 1, env);
		if (tmp)
			befor_dolla = ft_strjoin(tmp, befor_dolla);
		*word = ft_strjoin(befor_dolla, after_dolla);
	}
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

char	*expand(char *word, t_type type, t_list *env)
{
	int 	index;
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

void	expand_var(t_args **cmd_line)
{
	t_token	*tmp;
	char	*old_str;

	if (!*cmd_line)
		return ;
	tmp = (*cmd_line)->tokens;
	while (tmp)
	{
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
			tmp->content = expand(tmp->content, tmp->type, (*cmd_line)->env);
			if (ft_strncmp(old_str, tmp->content, ft_strlen(old_str) + 1))
			{
				tmp->content = replace_sp(tmp->content);
				tmp->type = string;
			}
		}
		if (tmp)
			tmp = tmp->next;
	}
}
