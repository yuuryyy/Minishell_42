/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parsing_process.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ychagri <ychagri@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/08/07 23:59:55 by ychagri           #+#    #+#             */
/*   Updated: 2024/08/08 02:13:07 by ychagri          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../minishell.h"

int	process_line(t_args *cmdline)
{
	char	*tmp;

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
	cmdline->table->cmd = ft_split(cmdline->table->arg, '\n');
	free(cmdline->table->arg);
	cmdline->table->arg = NULL;
	return (g_errno = EXIT_SUCCESS);
}

