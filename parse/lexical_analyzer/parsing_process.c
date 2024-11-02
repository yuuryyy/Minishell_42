/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parsing_process.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ychagri <ychagri@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/08/07 23:59:55 by ychagri           #+#    #+#             */
/*   Updated: 2024/11/02 22:04:09 by ychagri          ###   ########.fr       */
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

int	process_line(t_args *cmdline)
{
	char		*tmp;
	t_cmd_tab	*tab;

	tmp = ft_strdup(cmdline->line);
	if (!*tmp)
		return (free(tmp), exit_code(EXIT_SUCCESS, EDIT), 1);
	if (!words_list(tmp, cmdline))
		return (free(tmp), 1);
	free(tmp);
	remove_q(&cmdline->tokens);
	if (!syntax_check(cmdline))
	{
		if (heredoc_check(cmdline->tokens))
			return (exit_code(1, EDIT), 1);
		return (put_error(SYNTAX, NULL), 1);
	}
	expand_var(&cmdline);
	command_table(cmdline);
	tab = cmdline->table;
	while (tab)
	{
		tab->cmd = lst_to_array(tab->arg);
		tab = tab->next;
	}
	return (ft_heredoc(&cmdline->table));
}
