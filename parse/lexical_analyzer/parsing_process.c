/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parsing_process.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ychagri <ychagri@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/08/07 23:59:55 by ychagri           #+#    #+#             */
/*   Updated: 2024/08/09 01:38:29 by ychagri          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../minishell.h"

int	process_line(t_args *cmdline)
{
	char		*tmp;
	t_cmd_tab	*tab;

	// if (!tmp)
	// 	return(g_errno = 130);
	tmp = ft_strdup(cmdline->line);
	if (!*tmp)
		return (g_errno = EXIT_SUCCESS);
	if (!words_list(tmp, cmdline))
		return (free(tmp), g_errno);
	free(tmp);
	remove_q(&cmdline->tokens);
	if (!syntax_check(cmdline))
		return (g_errno);
	expand_var(&cmdline);
	command_table(cmdline);
	tab = cmdline->table;
	while (tab)
	{
		tab->cmd = ft_split(tab->arg, '\n');
		free(tab->arg);
		tab->arg = NULL;
		tab = tab->next;
	}
	return (g_errno = EXIT_SUCCESS);
}

