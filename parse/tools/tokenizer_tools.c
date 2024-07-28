/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   tokenizer_tools.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ychagri <ychagri@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/25 06:26:12 by ychagri           #+#    #+#             */
/*   Updated: 2024/07/27 04:01:11 by ychagri          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../minishell.h"

int word_len(t_args *cmd_line)
{
	int		i;
	int		len;
	char	*line;
	char	c;

	i = 0;
	len = 0;
	line = cmd_line->line;
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
			return (-1);
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

void	remove_q(t_token **lst)
{
	t_token	*tmp;
	char	*str;

	tmp = *lst;
	str = NULL;
	if (!tmp || !lst)
		return ;
	while (tmp)
	{
		if (tmp->type == single_quote || tmp->type == double_quote)
		{
			char *str = tmp->content;
			tmp->content = ft_substr(str, 1, ft_strlen(str) - 2);
			free(str);
		}
		tmp = tmp->next;
	}
}