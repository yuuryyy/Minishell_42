/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   tokenizer.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ychagri <ychagri@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/20 03:34:14 by ychagri           #+#    #+#             */
/*   Updated: 2024/07/23 05:20:24 by ychagri          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

int is_seperator(char c)
{
	return (c == '|' || c == '<' || c == '>' );
}

t_token	*tokenew(void *content)
{
	t_token	*new;

	new = malloc(sizeof(t_token));
	if (!new)
		return (NULL);
	new->content = content;
	new->token = 0;
	new->next = NULL;
	return (new);
}

void	tokenadd_back(t_token	**token, t_token	*new)
{
	t_token	*ptr;
	t_token	*tmp;

	if (!new || !token)
		return;
	// printf("*******%s\n", new->content);
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

void	token_list(t_args *cmd_line)
{
	char	**split;
	t_token	*token;
	int		i;

	token = NULL;
	split = ft_split(cmd_line->line, ' ');
	i = 0;
	while (split[i])
	{
		// printf("%s\n", split[i]);
		tokenadd_back(&cmd_line->tokens, tokenew(split[i]));
		i++;
	}
	free_array(split);
}