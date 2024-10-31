/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parsing_process.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ychagri <ychagri@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/08/07 23:59:55 by ychagri           #+#    #+#             */
/*   Updated: 2024/10/30 23:35:04 by ychagri          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

t_cmd_tab	*new_tab(void)
{
	t_cmd_tab	*new;

	new = malloc(sizeof(t_cmd_tab));
	if (!new)
		return (NULL);
	ft_bzero(new, sizeof(t_cmd_tab));
	return (new);
}

void	table_add_back(t_cmd_tab **head, t_cmd_tab *new)
{
	t_cmd_tab	*tmp;
	t_cmd_tab	*prev;

	tmp = *head;
	if (*head == NULL)
	{
		*head = new;
		return ;
	}
	while (tmp)
	{
		prev = tmp;
		tmp = tmp->next;
	}
	prev->next = new;
}

int	heredoc_check(t_token *token)
{
	t_token	*temp;
	char	*lim;

	temp = token;
	while (temp && temp->type != piipe)
	{
		if (temp->type == heredoc)
		{
			lim = NULL;
			temp = temp->next;
			while (temp && temp->type >= string)
			{
				lim = ft_strjoin2(lim, temp->content);
				if (temp->space == true)
					break ;
				temp = temp->next;
			}
			if (read_line(lim, NULL, NO_EXW, NULL))
				return (free(lim), 1);
			free(lim);
		}
		else if (temp)
			temp = temp->next;
	}
	return (0);
}

char	*remove_quotes(char *str, int c)
{
	char	*update;
	int		len;
	int		j;
	int		i;

	i = -1;
	len = 0;
	while (str[++i])
		if (str[i] != c)
			len++;
	update = malloc((len + 1) * sizeof(char));
	i = -1;
	j = -1;
	while (str[++i])
	{
		if (str[i] != c)
			update[++j] = str[i];
	}
	update[++j] = '\0';
	free(str);
	return (update);
}

// void ft_list_remove_if(t_token **begin_list)
// {
// 	if (begin_list == NULL || *begin_list == NULL)
// 		return;
// 	t_token *cur = *begin_list;

// 	if (cur->type == string && cur->content == NULL)
// 	{
// 		*begin_list = cur->next;
// 		free(cur);
// 		ft_token_remove_if(begin_list);
// 	}
// 	else 
// 	{ 
// 		cur = *begin_list;
// 		ft_token_remove_if(&cur->next);
// 	}
// }

int	process_line(t_args *cmdline)
{
	char		*tmp;
	t_cmd_tab	*tab;

	tmp = ft_strdup(cmdline->line);
	if (!*tmp)
		return (free(tmp), g_errno = EXIT_SUCCESS, 1);
	if (!words_list(tmp, cmdline))
	{
		heredoc_check(cmdline->tokens);
		free(tmp);
		g_errno = 1;
		return (1);
	}
	free(tmp);
	remove_q(&cmdline->tokens);
	if (!syntax_check(cmdline))
	{
		if (heredoc_check(cmdline->tokens))
			return (g_errno = 1, 1);
		put_error(SYNTAX , NULL);
		return (1);
	}
	expand_var(&cmdline);
	// del_emptystr(&cmdline->tokens);
	command_table(cmdline);
	tab = cmdline->table;
	while (tab)
	{
		if (tab->arg)
		{
			tab->cmd = lst_to_array(tab->arg);
			ft_lstclear(&tab->arg, del);
			tab->arg = NULL;
		}
		tab = tab->next;
	}
	if (ft_heredoc(&cmdline->table))
		return (1);
	return (0);
}
