/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   expand.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: youssra <youssra@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/27 01:56:16 by ychagri           #+#    #+#             */
/*   Updated: 2024/08/03 16:58:37 by youssra          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../minishell.h"

char	*expand_string(char *word)
{
	char	*value;
	char	*tmp;

	if (!ft_strchr(word, '$') || !word || strncmp(word, "$", 2) == 0)
		return (word);
	value = getenv(word + 1);
	free(word);
	if (value)
		word = ft_strdup(value);
	else
		word = NULL;
	return (word);
}


char	*expand(char *word, t_type type)
{
	int		i;
	char	*var;
	char	*befor_dolla;
	char	*final;
	size_t	len;
	char	*tmp;

	if (!word || !ft_strchr(word, '$'))
		return (word);
	if (type == string)
		word= expand_string(word);
	else
	{
		i = 0;
		befor_dolla = ft_strdup(word);
		printf("%s\n", befor_dolla);
		while (befor_dolla[i] && befor_dolla[i] != '$')
			i++;
		befor_dolla[i] = 0;
		len = word_len(word + i);
		tmp = ft_substr(word, i, len);
		var = getenv(tmp + 1);
		free(tmp);
		if (!var)
			final = ft_strjoin(befor_dolla, word + i + len);
		else
		{
			final = ft_strjoin(befor_dolla, var);
			word = ft_strjoin(final, word + i + len);
		}
		free(befor_dolla);
		free(final);
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
		if(tmp->type == string || tmp->type == double_quote)
			tmp->content = expand(tmp->content, tmp->type);
		tmp = tmp->next;
	}
}
