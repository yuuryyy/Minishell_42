/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   tokenizer_tools.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ychagri <ychagri@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/25 06:26:12 by ychagri           #+#    #+#             */
/*   Updated: 2024/07/25 12:25:44 by ychagri          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../minishell.h"

int word_len(char *line)
{
	int		i;
	int		len;
	char	c;

	i = 0;
	len = 0;
	if (line[i] == '\'' || line[i] == '\"')
	{
		c = line[i];
		i++;
		len++;
		while(line[i] && line[i] != c)
		{
			i++;
			len++;
		}
		if (!line)
			return (errno = EXIT_FAILURE, syntax_error(line), -1);
		len++;
	}
	if (is_seperator(line[i]))
	{
		len++;
		c = line[i];
		i++;
		while (line[i] == c)
		{
			i++;
			len++;
		}
	}
	else if (line[i] == '$')
	{
		i++;
		len++;
		while (line[i] && (ft_isalnum(line[i]) || line[i] == '_'))
		{
			i++;
			len++;
		}
	}
	else
	{
		while (line[i] && !is_seperator(line[i]) && line[i] != '$'
			&& line[i] != '\"' && line[i] != '\'' && line[i] != ' ')
		{
			i++;
			len++;
		}
	}
	return (len);
}

char	*expand(char *word, t_type type)
{
	int		i;
	char	*var;
	char	*tmp;
	size_t	len;

	if (!word || !ft_strchr(word, '$')
		||ft_strncmp(ft_strchr(word, '$'), "$", 2))
		return (word);
	tmp = ft_strdup(word);
	if (type == string)
	{
		free(word);
		word = getenv(tmp + 1);
	}
	else
	{
		while (ft_strchr(word, '$'))
		{
			i = 0;
			while (word[i] && word[i] != '$')
				i++;
			if (!ft_isalnum(word[i]) || word[i] != '_')
				break;
			word[i] = 0;
			len = word_len(tmp + i);
			var = ft_substr(tmp, i, len);
			var = getenv(var + 1);
			if (!var)
				word = ft_strjoin(word, tmp + i + len);
			else
			{
				word = ft_strjoin(word, var);
				word = ft_strjoin(word, tmp + i + len);
			}
		}
	}
	free(tmp);
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
		if(tmp->type == string || tmp->type == double_quote)
			tmp->content = expand(tmp->content, tmp->type);
		tmp = tmp->next;
	}
}
