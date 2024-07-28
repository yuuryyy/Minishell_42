/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   freeing.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ychagri <ychagri@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/23 05:36:15 by ychagri           #+#    #+#             */
/*   Updated: 2024/07/27 01:36:24 by ychagri          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../minishell.h"

void	free_array(char	**str)
{
	int	i;

	i = 0;
	while (str[i])
	{
		free(str[i]);
		i++;
	}
	free(str);
}

void	free_tokens(t_token **lst)
{
	t_token	*tmp;

	if (!lst || !*lst)
		return ;
	tmp = (*lst);
	*lst = tmp->next;
	if ((tmp)->content)
		free((tmp)->content);
	free(tmp);
	free_tokens(lst);
}

void	del(void *content)
{
	content = NULL;
}

void	free_table(t_cmd_tab **table)
{
	t_cmd_tab	*tmp;

	if (!table || !*table)
		return ;
	tmp = (*table);
	*table = tmp->next;
	if (tmp->cmd)
		free(tmp->cmd);
	if (tmp->argv && (*tmp->argv))
		free_array(tmp->argv);
	if (tmp->delimiter)
		free(tmp->delimiter);
	if (tmp->in)
		free(tmp->in);
	if (tmp->out)
		free(tmp->out);
	free(tmp);
	free_table(table);
}

void	free_struct(t_args *cmd_line)
{
	if (cmd_line->line)
		free(cmd_line->line);
	if (cmd_line->tokens)
		free_tokens(&cmd_line->tokens);
	if (cmd_line->env)
		ft_lstclear(&cmd_line->env, del);
	if (cmd_line->path)
		free_array(cmd_line->path);
	if (cmd_line->table)
		free_table(&cmd_line->table);
}