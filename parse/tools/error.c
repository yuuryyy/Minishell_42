/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   error.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kaafkhar <kaafkhar@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/25 06:45:51 by ychagri           #+#    #+#             */
/*   Updated: 2024/09/30 02:12:14 by kaafkhar         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../minishell.h"

void	put_error(t_args *cmd_line, char *msg, char *name)
{
	int g_errno = 0;
	ft_putstr_fd("minionshell :"RED, 2);
	ft_putstr_fd(msg, 2);
	if (name)
		ft_putstr_fd(name, 2);
	ft_putstr_fd("\n"RESET, 2);
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
		if (current->type == redout && current->next
			&& current->next->type == piipe && current->space == false)
		{
			current->next = next->next;
			free (next->content);
			free(next);
			next = current->next;
		}
		if ((current->type < 5 && (!next || next->type < string))
			|| (current->type == piipe && (current == cmdline->tokens
					|| !next || next->type < string)))
			return (put_error(cmdline, SYNTAX, NULL), false);
		if (current->type == piipe)
			cmdline->cmd_num++;
		current = current->next;
	}
	return (true);
}

void	free_current_cmdline(t_args *cmdline)
{
	free(cmdline->line);
	cmdline->line = NULL;
	free_table(&cmdline->table);
	cmdline->table = NULL;
	free_tokens(&cmdline->tokens);
	cmdline->tokens = NULL;
}
