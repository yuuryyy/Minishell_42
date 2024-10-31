/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   tokenizer_tools.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ychagri <ychagri@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/25 06:26:12 by ychagri           #+#    #+#             */
/*   Updated: 2024/10/30 22:27:07 by ychagri          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	quote_len(char *line)
{
	int		i;
	char	c;
	int		len;

	i = 0;
	len = 0;
	c = line[i];
	i++;
	len++;
	while (line[i] && line[i] != c)
	{
		i++;
		len++;
	}
	if (!line[i])
		return (-1);
	len++;
	return (len);
}

int	strin_len(char *line)
{
	int	i;
	int	len;

	i = 0;
	len = 0;
	while (line[i] && !is_seperator(line[i])
		&& line[i] != '\"' && line[i] != '\'' && line[i] != ' ')
	{
		i++;
		len++;
	}
	return (len);
}

int	word_len(char *line)
{
	int		i;
	int		len;
	char	c;

	i = 0;
	len = 0;
	if (line[i] == '\'' || line[i] == '\"')
		return (quote_len(line));
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
	else
		return (strin_len(line));
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
			str = tmp->content;
			tmp->content = ft_substr(str, 1, ft_strlen(str) - 2);
			free(str);
		}
		tmp = tmp->next;
	}
}
