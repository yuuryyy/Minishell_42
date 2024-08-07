/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   error.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ychagri <ychagri@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/25 06:45:51 by ychagri           #+#    #+#             */
/*   Updated: 2024/08/07 23:55:32 by ychagri          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../minishell.h"

void	syntax_error(t_args *cmd_line)
{
	ft_putstr_fd("minionshell: \033[31msyntax error\033[0m\n", 2);
	free(cmd_line->line);
	cmd_line->line = NULL;
	if (cmd_line->tokens)
		free_tokens(&cmd_line->tokens);
	if (cmd_line->table)
		free_table(&cmd_line->table);
	g_errno = EXIT_FAILURE;
}

bool	syntax_check(t_args *cmdline)
{
	t_token	*current;
	t_token	*next;

	current = cmdline->tokens;
	while (current)
	{
		next = current->next;
		if (current->type == redout && next && next->type == piipe && current->space == false)
		{
			current->next = next->next;
			free (next->content);
			free(next);
			next = current->next;
		}
		if ((current->type == redout && (!next || next->type < string))
			|| (current->type == piipe && (current == cmdline->tokens
			|| !next || next ->type == piipe)) ||  ((current->type == redin
			|| current->type == append) && (!next
			|| next ->type < 6)))
				return (syntax_error(cmdline), false);
		if (current->type == piipe)
			cmdline->cmd_num++;
		current = current->next;
	}
	return (true);
}
