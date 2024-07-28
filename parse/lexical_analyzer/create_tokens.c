/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   create_tokens.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ychagri <ychagri@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/23 06:29:42 by ychagri           #+#    #+#             */
/*   Updated: 2024/07/27 04:08:57 by ychagri          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../minishell.h"

t_token	*new_token(char *content, int type)
{
	t_token	*token;

	if (!content)
		return NULL;
	token = malloc(sizeof(t_token));
	if (!token)
		return (NULL);
	token->content = content;
	token->next = NULL;
	token->type = type;
	return (token);
}

char	*get_word(char **line, t_args *cmd_line)
{
	int		i;
	int		start;
	size_t	len;
	char	*word;
	char	*tmp;

	i = 0;
	if (!*line || !line)
		return(NULL);
	tmp = *line;
	while (tmp[i] && tmp[i] == ' ')
		i++;
	start = i;
	len = word_len(tmp + i);
	if (len == -1)
		return (syntax_error(cmd_line), NULL);
	word = ft_substr(tmp, start, len);
	tmp = *line + len + i;
	*line = tmp;
	return (word);
}

t_type	get_type(char *word)
{
	if (*word == '<' && ft_strlen(word) == 2)
		return (heredoc);
	if (*word == '>' && ft_strlen(word) == 2)
		return (append);
	if (*word == '<' && ft_strlen(word) == 1)
		return (redin);
	if (*word == '>' && ft_strlen(word) == 1)
		return (redout);
	if (*word == '|' && ft_strlen(word) == 1)
		return (piipe);
	if (*word == '\'')
		return (single_quote);
	if (*word == '\"')
		return (double_quote);
	if (is_seperator(*word))
		return (syntax_error(word), errno = EXIT_FAILURE, 0);
	else
		return (string);
}

void	tokenadd_back(t_token	**token, t_token	*new)
{
	t_token	*ptr;
	t_token	*tmp;

	if (!new || !token)
		return;
	if (*token == NULL)
	{
		*token = new;
		return ;
	}
	tmp = *token;
	ptr = tmp;
	while (tmp!= NULL)
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
	t_type type;
	int		i;

	while (1)
	{
		i = 0;
		word = get_word(&line);
		if (!word || !*word)
			break;
		type = get_type(word);
		if (type == 0)
			return (free_tokens(&cmd_line->tokens),free(cmd_line->line), 0);
		lst = new_token(word, type);
		tokenadd_back(&cmd_line->tokens, lst);
		while (line[i] && line[i] == ' ')
			i++;
		lst->space = line[i] && i > 0;
	}
	free (word);
	remove_q(&cmd_line->tokens);
	return (1);
}
