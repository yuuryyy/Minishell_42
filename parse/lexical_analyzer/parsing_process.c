/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parsing_process.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ychagri <ychagri@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/08/07 23:59:55 by ychagri           #+#    #+#             */
/*   Updated: 2024/11/03 23:03:21 by ychagri          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

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

int	check_nd_fill(t_args *cmdline)
{
	t_cmd_tab	*tab;

	remove_q(&cmdline->tokens);
	if (!syntax_check(cmdline))
	{
		put_error(SYNTAX, NULL);
		return (1);
	}
	expand_var(&cmdline);
	command_table(cmdline);
	tab = cmdline->table;
	while (tab)
	{
		if (tab->arg)
			tab->cmd = lst_to_array(tab->arg);
		tab = tab->next;
	}
	return (0);
}

int	process_line(t_args *cmdline)
{
	char		*tmp;

	tmp = ft_strdup(cmdline->line);
	if (!*tmp)
		return (free(tmp), exit_code(EXIT_SUCCESS, EDIT), 1);
	if (!words_list(tmp, cmdline))
	{
		free(tmp);
		return (1);
	}
	free(tmp);
	if (check_nd_fill(cmdline))
		return (1);
	if (ft_heredoc(&cmdline->table))
		return (1);
	return (0);
}
