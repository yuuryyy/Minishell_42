/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   tokenizer_tools.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kaafkhar <kaafkhar@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/25 06:26:12 by ychagri           #+#    #+#             */
/*   Updated: 2024/11/04 06:11:22 by kaafkhar         ###   ########.fr       */
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
		&& line[i] != '\"' && line[i] != '\''
		&& line[i] != ' ' && line[i] != '\t')
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

void	add_env_node(t_list **env, char *new_content)
{
	t_list	*new_node;

	new_node = malloc(sizeof(t_list));
	if (!new_node)
		return ;
	new_node->content = new_content;
	new_node->next = *env;
	*env = new_node;
}
