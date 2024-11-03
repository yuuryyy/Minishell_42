/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   create_tokens.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ychagri <ychagri@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/23 06:29:42 by ychagri           #+#    #+#             */
/*   Updated: 2024/11/03 02:25:33 by ychagri          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

char	*get_word(char **line)
{
	int		i;
	int		start;
	int		len;
	char	*word;
	char	*tmp;

	i = 0;
	if (!*line || !line || !**line)
		return (NULL);
	tmp = *line;
	while (tmp[i] && (tmp[i] == ' ' || tmp[i] == '\t'))
		i++;
	start = i;
	len = word_len(tmp + i);
	if (len == -1)
		return (put_error(SYNTAX, NULL), ft_strdup("\'"));
	word = ft_substr(tmp, start, (size_t)len);
	*line = *line + len + i;
	return (word);
}

t_type	get_type(char *word)
{
	if (*word == '<' && ft_strlen(word) == 2)
		return (heredoc);
	else if (*word == '>' && ft_strlen(word) == 2)
		return (append);
	else if (*word == '<' && ft_strlen(word) == 1)
		return (redin);
	else if (*word == '>' && ft_strlen(word) == 1)
		return (redout);
	else if (*word == '|' && ft_strlen(word) == 1)
		return (piipe);
	else if (*word == '\'')
		return (single_quote);
	else if (*word == '\"')
		return (double_quote);
	else if (is_seperator(*word))
		return (put_error(SYNTAX, NULL), 0);
	else
		return (string);
}

void	tokenadd_back(t_token	**token, t_token	*new)
{
	t_token	*ptr;
	t_token	*tmp;

	if (!new || !token)
		return ;
	if (*token == NULL)
	{
		*token = new;
		return ;
	}
	tmp = *token;
	ptr = tmp;
	while (tmp != NULL)
	{
		ptr = tmp;
		tmp = (tmp)->next;
	}
	ptr->next = new;
}

int	words_list(char	*line, t_args *cmd_line)
{
	char	*word;
	t_token	*lst;
	t_type	type;
	int		i;

	while (1)
	{
		i = 0;
		word = get_word(&line);
		if (word && ft_strncmp(word, "\'", 2) == 0)
			return (free(word), 0);
		if (!word || !*word)
			break ;
		type = get_type(word);
		if (type == 0)
			return (free(word), 0);
		lst = new_token(word, type);
		tokenadd_back(&cmd_line->tokens, lst);
		while (line[i] && (line[i] == ' ' || line[i] == '\t'))
			i++;
		lst->space = line[i] && i > 0;
	}
	if (word)
		free (word);
	return (1);
}
