/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   freeing.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ychagri <ychagri@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/23 05:36:15 by ychagri           #+#    #+#             */
/*   Updated: 2024/10/24 15:23:52 by ychagri          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

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

void	free_del(void *content)
{
	if (content)
	{
		free(content);
		content = NULL;
	}
}

void	free_table(t_cmd_tab **table)
{
	t_cmd_tab	*tmp;

	if (!table || !*table)
		return ;
	tmp = (*table);
	*table = tmp->next;
	if (tmp->arg)
		free(tmp->arg);
	if (tmp->cmd)
		free_array(tmp->cmd);
	if (tmp->delimiter)
		ft_lstclear(&tmp->delimiter, free_del);
	if (tmp->in)
		ft_lstclear(&tmp->in, free_del);
	if (tmp->out)
		ft_lstclear(&tmp->out, free_del);
	if (tmp->append)
		ft_lstclear(&tmp->append, free_del);
	free(tmp);
	tmp = NULL;
	free_table(table);
}

void	free_struct(t_args *cmd_line)
{
	if (!cmd_line)
		return ;
	close(cmd_line->fdin);
	close(cmd_line->fdout);
	if (cmd_line->env)
		ft_lstclear(&cmd_line->env, del);
	if (cmd_line->path)
		free_array(cmd_line->path);
	if (cmd_line->line)
		free(cmd_line->line);
	if (cmd_line->tokens)
		free_tokens(&cmd_line->tokens);
	if (cmd_line->table)
		free_table(&cmd_line->table);
	ft_bzero(cmd_line, sizeof(t_args *));
}
