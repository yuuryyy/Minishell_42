/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parsing_process.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ychagri <ychagri@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/08/07 23:59:55 by ychagri           #+#    #+#             */
/*   Updated: 2024/08/08 00:55:35 by ychagri          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../minishell.h"

int	process_line(t_args *cmdline)
{
	char	*tmp;

	tmp = ft_strdup(cmdline->line);
	if (!words_list(tmp, cmdline))
		return (free(tmp), g_errno);
	free(tmp);
	remove_q(&cmdline->tokens);
	if (!syntax_check(cmdline))
		return (g_errno);
	expand_var(&cmdline);
	command_table(cmdline);
	return (g_errno = EXIT_SUCCESS);
}
